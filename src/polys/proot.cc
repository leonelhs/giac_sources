// -*- mode:C++; compile-command: "g++ -g proot.cc -o proot && g++ -g proot.cc -DPM -o mproot -lgiac" -*-
// Polynomial roots for small degrees (<= about 30)
#include <fstream>
#include <iostream>
#include <vector>
#include <complex>
#include <algorithm>
#include <iomanip>
#include <cmath>

int nbits=100; // default multi-precision, change with e.g. export GIAC_N=200
double cluster_step=1e-4; // if step>cluster_step, no cluster analysis, export GIAC_STEP=1e-3
double cluster_dp=0.2; // if step*sum_{j!=i}(inv(approx_root[i]-approx_root[j])>cluster_dp, then do cluster analysis, export GIAC_DP=.1
int debug_info=0; // export GIAC_DEBUG=1 or 2

#include <giac/config.h>
#include <giac/giac.h>
using namespace giac;
using namespace std;


// single precision

typedef complex<long double> fdbl;
//typedef complex<float> fdbl;
inline double absdbl(const fdbl & x){
  return abs(x);
}
inline fdbl re(const fdbl & x){
  return fdbl(x.real(),0);
}
inline double redbl(const fdbl & x){
  return x.real();
}
inline double imdbl(const fdbl & x){
  return x.imag();
}
inline bool is_exactly_zero(const fdbl & x){
  return x.real()==0 && x.imag()==0;
}
fdbl inv(const fdbl z){
  return fdbl(1.0)/z;
}

bool fdbl_less(const fdbl & x,const fdbl & y){
  if (x.real()!=y.real())
    return x.real()<y.real();
  return x.imag()<y.imag();
}



typedef vector<fdbl> vfdbl;
ostream & operator << (ostream & os,const vfdbl & P){
  for (int i=0;i<P.size();++i)
    os << P[i] << " ";
  return os;
}

fdbl horner_rem(const vfdbl & P,fdbl x,vfdbl * Q){
  if (Q)
    Q->clear(); 
  if (P.empty())
    return 0.0;
  size_t s=P.size();
  if (Q)
    Q->reserve(s-1);
  fdbl r=0;
  if (Q){
    for (size_t i=0;;){
      r=r*x+P[i];
      ++i;
      if (i==s)
	break;
      Q->push_back(r);
    }
  }
  else {
    for (size_t i=0;i<s;++i){
      r=r*x+P[i];
    }
  }
  return r;
}

double l1(const vfdbl & P,const fdbl & z){
  double r=absdbl(z),rn=1,res=0;
  for (size_t i=1;i<=P.size();++i){
    double anrn=absdbl(P[P.size()-i])*rn;
    rn *= r;
    if (anrn<=res)
      continue;
    res=anrn;
  }
  return res;
}

// shift roots such that sum of roots=0
fdbl find_shift(const vfdbl & R){
  int n=R.size()-1;
  if (n==0)
    return 0;
  return R[1]/fdbl(n)/R[0];
}

vfdbl shift(const vfdbl & P0,fdbl d){
  vfdbl P(P0),Q,R;
  int n=P.size();
  for (int i=0;i<n;++i){
    fdbl Pz=horner_rem(P,d,&Q);
    R.push_back(Pz);
    P.swap(Q);
  }
  reverse(R.begin(),R.end());
  return R;
}

fdbl sum(const vfdbl & P){
  fdbl r(0.0);
  for (size_t i=0;i<P.size();++i)
    r += P[i];
  return r;
}

double sumabs(const vfdbl & P){
  double r(0.0);
  for (size_t i=0;i<P.size();++i)
    r += absdbl(P[i]);
  return r;
}

bool linreg(const vector<double> & x,const vector<double> & y,double & a,double &b,double & r){
  size_t n=x.size();
  if (n!=y.size())
    return false;
  double X=0,Y=0,XY=0,X2=0,Y2=0;
  for (size_t i=0;i<n;++i){
    X += x[i];
    Y += y[i];
  }
  X /= n; Y /= n;
  for (size_t i=0;i<n;++i){
    double xx=x[i]-X,yy=y[i]-Y;
    XY += xx*yy;
    X2 += xx*xx;
    Y2 += yy*yy;
  }
  if (X2==0)
    return false;
  XY /= n; X2 /= n; Y2 /= n;
  a=XY/X2;
  b=Y-a*X;
  r=Y2==0?1:XY/sqrt(X2)/sqrt(Y2);
  return true;
}

double find_scale(const vfdbl & P){
  int n=P.size()-1;
  vector<double> x,y;
  for (int i=0;i<=n;++i){
    double a=absdbl(P[i]);
    if (a==0)
      continue;
    x.push_back(n-i);
    y.push_back(log(a));
  }
  if (x.empty())
    return 1;
  double a,b,r;
  linreg(x,y,a,b,r);
  return exp(-a);
}

void rescale(vfdbl & P, fdbl l){
  if (l==fdbl(1)) return;
  fdbl ll=l;
  for (int i=P.size()-2;i>=0;--i){
    P[i] = ll*P[i];
    ll = ll*l;
  }
  fdbl c=P[0];
  for (size_t i=0;i<P.size();++i)
    P[i] = P[i]/c;
}


bool dkw(const vfdbl & P0,int N,double eps,vfdbl & R){
  bool real=true;
  for (size_t i=0;real && i<P0.size();++i){
    if (imdbl(P0[i])!=0)
      real=false;
  }
  fdbl dr=find_shift(P0);
  vfdbl P=shift(P0,-dr);
  double l=find_scale(P);
  rescale(P,l);
  int deg=P0.size()-1;
  // init R if not already done
  if (R.size()!=deg){
    fdbl w(0.0,2.0*M_PI/deg);
    w=exp(w);
    R.push_back(fdbl(1.0));
    fdbl wk=w;
    for (int i=1;i<deg;++i){
      R.push_back(wk);
      wk = wk*w;
    }
  }
  vfdbl newR(deg);
  int ok=0;
  N *= P.size();
  double delta=0;
  for (int k=0;k<N;++k){
    delta=0;
    for (int i=0;i<deg;++i){
      fdbl & zi=R[i];
      fdbl d=horner_rem(P,zi,0);
      fdbl p(1.0);
      for (int j=0;j<deg;++j){
	if (j==i) continue;
	p = p*(zi-R[j]);
      }
      if (absdbl(p)==0)
	return false;
      d = d/p;
      delta += absdbl(d);
      newR[i]=zi-d;
    }
    newR.swap(R);
    if (debug_info>0)
      cout << k << ": " << delta << "\n";
    if (delta<eps*sumabs(R))
      ++ok;
    else
      ok=0;
    if (ok==2){
      // rescale and translate
      for (size_t j=0;j<R.size();++j){
        R[j] = fdbl(l)*R[j]-dr;
      }
      sort(R.begin(),R.end(),fdbl_less);
      return true;
    }
  }
  cout << "Durand-Kerner-Weierstrass: too many iterations " << N << " delta " << delta << "\n";
  return false;
}

struct int_2double {
  int i;
  double theta,norm;
};

double norm(double dx,double dy){
  if (dx==0 && dy==0)
    return 0;
  if (dx<0) dx=-dx;
  if (dy<0) dy=-dy;
  if (dx>dy){
    double z=dy/dx;
    return dx*sqrt(1+z*z);
  }
  else {
    double z=dx/dy;
    return dy*sqrt(1+z*z);
  }
}

bool graham_sort_function(const int_2double & a,const int_2double & b){
  if (a.theta==b.theta)
    return b.norm>a.norm;
  return b.theta>a.theta;
}

double cross_prod(const vfdbl & v,int a,int b,int c){
  fdbl ab=v[b]-v[a],ac=v[c]-v[a];
  double A=redbl(ab),B=imdbl(ab),C=redbl(ac),D=imdbl(ac);
  return A*D-B*C;
}

vector<int> convexhull(const vfdbl & v){
  int s=v.size(),imin=0;
  // find origin
  double ymin=imdbl(v[0]),ycur,xmin=redbl(v[0]),xcur;
  for (int i=1;i<s;++i){
    ycur=imdbl(v[i]);xcur=redbl(v[i]);
    if (ymin>ycur || (ymin==ycur && xmin>xcur) ){
      imin=i; ymin=ycur; xmin=xcur;
    }
  }
  vector<int_2double> ls;
  for (int j=0;j<s;++j){
    if (j!=imin){
      double dx=redbl(v[j])-xmin,dy=imdbl(v[j])-ymin;
      int_2double s={j,atan2(dx,dy),norm(dx,dy)};
      ls.push_back(s);
    }
  }
  sort(ls.begin(),ls.end(),graham_sort_function);
  vector<int> res; res.push_back(imin); res.push_back(ls[0].i);
  int ress=2;
  for (int j=1;j<s-1;++j){
    int icur=ls[j].i;
    double o=cross_prod(v,res[ress-2],res[ress-1],icur);
    if (o==0)
      res[ress-1]=icur;
    else {
      if (o>0){
        res.push_back(icur);
        ++ress;
      }
      else {
        while (ress>2 && o<0){
          res.pop_back();
          ress--;
          o=cross_prod(v,res[ress-2],res[ress-1],icur);
        }
        res.push_back(icur);
        ++ress;
      }
    }
  }
  return res;
}

double init_R(const vfdbl & P,vfdbl & R){
  R.clear();
  int n=P.size()-1;
  vfdbl l;
  vector<int> lpos;
  double M=0;
  for (int i=0;i<=n;++i){
    double ai=absdbl(P[n-i]);
    if (ai==0)
      continue;
    l.push_back(fdbl(double(i),log(ai)));
    lpos.push_back(i);
  }
  vector<int> pos=convexhull(l);
  // find real positions (since coeffs==0 were removed)
  for (int i=0;i<pos.size();++i){
    pos[i]=lpos[pos[i]];
  }
  sort(pos.begin(),pos.end());
  if (pos[0]!=0)
    pos.insert(pos.begin(),0);
  if (pos.back()!=n)
    pos.push_back(n);
  int count=0;
  for (int i=1;i<pos.size();++i){
    int dk=pos[i]-pos[i-1];
    double uk=pow(absdbl(P[n-pos[i]]/P[n-pos[i-1]]),-1.0/dk);
    if (uk>M)
      M=uk;
    double sigma=0.7;
    for (int j=0;j<dk;++j){
      double theta=sigma+2*M_PI*i/n+2*M_PI*j/dk;
      fdbl z(uk*cos(theta),uk*sin(theta));
      R.push_back(z);
    }
  }
  return M;
}

// find r=P(x) and r1=diff(P)(x)
// if |x|>1 this may overflow
void horner2(const vfdbl & P,fdbl x,fdbl & r,fdbl & r1){
  r=r1=0;
  if (P.empty())
    return ;
  size_t s=P.size()-1;
  for (size_t i=0;i<s;++i){
    r=r*x+P[i];
    r1=r1*x+r;
  }
  r=r*x+P[s];
}

double l1norm(const vfdbl & v){
  double r=0;
  for (int i=0;i<v.size();++i)
    r += absdbl(v[i]);
  return r;
}

void div(vfdbl & v,double r){
  for (int i=0;i<v.size();++i)
    v[i] /= r;
}

// approx largest root in norm, using a few iterations of power method
double largest(const vfdbl & fP,int maxiter=100,double eps=1e-6){
  int deg=fP.size()-1;
  if (debug_info)
    cout << "power method " << fP << "\n";
  vfdbl v(deg);
  for (int i=0;i<deg;++i)
    v[i]=fdbl(rand()/(1.0+RAND_MAX),rand()/(1.0+RAND_MAX));
  div(v,l1norm(v));
  vfdbl w(deg);
  double oldR(0.0);
  for (int j=0;j<maxiter;++j){
    for (int i=0;i<deg-1;++i){
      w[i+1]=v[i];
    }
    fdbl r(0,0);
    for (int i=0;i<deg;++i){
      r += fP[i+1]*v[i];
    }
    w[0]= -r/fP[0];
    double R=l1norm(w);
    if (debug_info)
      cout << "power method " << j << " " << R << "\n";
    div(w,R);
    if (j>5 && abs(1-R/oldR)<eps)
      return R;
    v.swap(w);
    oldR=R;
  }
  return oldR;
}

#define REV 1

bool aberth(const vfdbl & P0,int N,double eps,vfdbl & R,bool allow_recursion){
  bool real=true;
  for (size_t i=0;real && i<P0.size();++i){
    if (imdbl(P0[i])!=0)
      real=false;
  }
  int deg=P0.size()-1;
  vfdbl P(P0);
  // init R if not already done
  fdbl dr(0);
  fdbl l(1);
  if (R.size()!=deg){
    dr=find_shift(P);
    P=shift(P,-dr);
    l=find_scale(P);
    rescale(P,l);
    init_R(P,R);
  }
  vfdbl Prev(P);
  reverse(Prev.begin(),Prev.end());
  vfdbl newR(deg);
  vector<bool> zi_done(deg,false);
  int ok=0; double delta;
  for (int k=0;k<N;++k){
    delta=0;
    for (int i=0;i<deg;++i){
      if (!ok && zi_done[i]){ // always do the last iteration for accuracy
        newR[i]=R[i];
        continue;
      }
      fdbl & zi=R[i];
      fdbl d,d1;
      if (absdbl(zi)>1){
        fdbl gamma(inv(zi));
        horner2(Prev,gamma,d,d1);
        if (!is_exactly_zero(d)){
          d=gamma*(fdbl(deg)-gamma*d1/d);
          if (is_exactly_zero(d))
            return false;
          d=inv(d);
        }
      }
      else {
        horner2(P,zi,d,d1);
        if (is_exactly_zero(d1))
          return false;
        d=d/d1;
      }
      fdbl p(0);
      for (int j=0;j<deg;++j){
	if (j==i) continue;
        fdbl dz=(zi-R[j]);
        if (is_exactly_zero(dz))
          return false;
	p += inv(dz);
      }
      double dd=absdbl(d),pp=absdbl(p);
      if (!ok && allow_recursion && dd<cluster_step && dd*pp>cluster_dp){
        // if (ok) continue;
        // cluster of roots, find all roots in this cluster
        int cend=i+1;
        fdbl sumR=zi;
        for (int k=cend;k<deg;++k){
          if (abs(zi-R[k])<deg/pp){
            swap(R[cend],R[k]);
            swap(zi_done[cend],zi_done[k]);
            sumR+=R[cend];
            ++cend;
          }
        }
        // cluster is from i to cend-1 included
        fdbl z=sumR/fdbl(cend-i); // center of gravity of cluster
        // shift P and reverse (roots become inverse of roots)
        vfdbl Pcluster(shift(P,z)),Rcluster(deg);
#ifdef REV
        reverse(Pcluster.begin(),Pcluster.end());
        fdbl D=fdbl(cend-i)/d; // d=sum P/P' = 1/sum 1/(z-zj) = approx (root-z)/multiplicity of root
        // assign the largest value to k in i..cend
        for (int k=0;k<deg;++k){
          Rcluster[k]=inv(R[k]-z);
          if (k>=i && k<cend){
            fdbl a(0.0,0.7+(k-i)*2*M_PI/(cend-i));
            Rcluster[k]=fdbl(D)*exp(a);
          }
        }            
#else
        for (int k=0;k<deg;++k)
          Rcluster[k]=R[k]-z;
#endif
        // recursive call of aberth
        bool b=aberth(Pcluster,N,eps,Rcluster,false);
        if (b){
#ifdef REV
          for (int k=0;k<deg;++k)
            R[k]=l*(inv(Rcluster[k])+z)-dr;
#else
          for (int k=0;k<deg;++k)
            R[k]=l*(Rcluster[k]+z)-dr;
#endif
          return true;
        }
      }
      d=d/(fdbl(1)-d*p);
      double abszi=absdbl(zi);
      double absdz=abszi==0?absdbl(d):absdbl(d)/abszi;
      if (absdz<eps/deg)
        zi_done[i]=true;
      delta += absdz;
      newR[i]=zi-d;
    }
    newR.swap(R);
    if (debug_info>0){
      cout << "Aberth single " << (allow_recursion?"":" rec") << k << ": " << delta << " time " << clock()*1e-6 << "\n";
      if (debug_info>1){
        cout << "Current approx roots " << R << "\n";
      }
    }
    if (delta<eps*deg)
      ++ok;
    else
      ok=0;
    if (ok==2){
      // rescale and translate
      for (size_t j=0;j<R.size();++j){
        R[j] = l*R[j] - dr;
      }
      sort(R.begin(),R.end(),fdbl_less);
      return true;
    }
  }
  cout << "Aberth single precision: too many iterations " << N << " delta " << delta << "\n";
  return false;  
}

bool read_poly(const string & filename,vfdbl & P){
  P.clear();
  ifstream i(filename.c_str());
  while (1){
    fdbl z;
    i >> z;
    if (i.eof())
      break;
    P.push_back(z);
  }
  return true;
}

vfdbl p_coeff(const vfdbl & R){
  vfdbl P;
  P.reserve(R.size()+1);
  P.push_back(fdbl(1));
  for (size_t i=0;i<R.size();++i){
    fdbl z=R[i];
    // P*(x-z)
    P.push_back(-z*P.back());
    for (size_t j=P.size()-2;j>=1;--j){
      P[j] -= z*P[j-1];
    }
  }
  return P;
}

// max distance between 2 elements of R
double ecart(const vfdbl & R){
  int n=R.size();
  double d=1e307;
  for (int i=0;i<n;++i){
    const fdbl & Ri=R[i];
    for (int j=0;j<n;++j){
      if (j==i) continue;
      double dd=absdbl(Ri-R[j]);
      if (dd<d)
        d=dd;
    }
  }
  return d;
}

// multi-precision
typedef gen dbl;
inline double absdbl(const dbl & x){
  dbl g=evalf_double(abs(x),1,context0);
  return g.type==_DOUBLE_?g._DOUBLE_val:0;
}
inline double redbl(const dbl & x){
  return evalf_double(re(x,context0),1,context0)._DOUBLE_val;
}
inline double imdbl(const dbl & x){
  return evalf_double(im(x,context0),1,context0)._DOUBLE_val;
}
inline dbl conj(const dbl & x){
  return conj(x,context0);
}
inline dbl re(const dbl & x){
  return re(x,context0);
}
inline dbl im(const dbl & x){
  return im(x,context0);
}
inline dbl exp(const dbl & x){
  return exp(x,context0);
}
inline dbl inv(const dbl & x){
  return inv(x,context0);
}
bool dbl_less(const dbl & x,const dbl & y){
  return islesscomplexthanf(x,y);
}

typedef vecteur vdbl;
ostream & operator << (ostream & os,const vdbl & P){
  for (int i=0;i<P.size();++i)
    os << P[i] << " ";
  return os;
}

void accurate_evalf(vdbl & P,int nbits){
  for (int i=0;i<P.size();++i)
    P[i]=accurate_evalf(P[i],nbits);
}

dbl horner_rem(const vdbl & P,dbl x,vdbl * Q){
  if (Q)
    Q->clear(); 
  if (P.empty())
    return 0.0;
  size_t s=P.size();
  if (Q)
    Q->reserve(s-1);
  dbl r=0;
  if (Q){
    for (size_t i=0;;){
      r=r*x+P[i];
      ++i;
      if (i==s)
	break;
      Q->push_back(r);
    }
  }
  else {
    for (size_t i=0;i<s;++i){
      r=r*x+P[i];
    }
  }
  return r;
}

double l1(const vdbl & P,const dbl & z){
  double r=absdbl(z),rn=1,res=0;
  for (size_t i=1;i<=P.size();++i){
    double anrn=absdbl(P[P.size()-i])*rn;
    rn *= r;
    if (anrn<=res)
      continue;
    res=anrn;
  }
  return res;
}

// shift roots such that sum of roots=0
dbl find_shift(const vdbl & R){
  int n=R.size()-1;
  if (n==0)
    return 0;
  return R[1]/dbl(n)/R[0];
}

vdbl shift(const vdbl & P0,dbl d){
  vdbl P(P0),Q,R;
  int n=P.size();
  for (int i=0;i<n;++i){
    dbl Pz=horner_rem(P,d,&Q);
    R.push_back(Pz);
    P.swap(Q);
  }
  reverse(R.begin(),R.end());
  return R;
}

dbl sum(const vdbl & P){
  dbl r(0.0);
  for (size_t i=0;i<P.size();++i)
    r += P[i];
  return r;
}

double sumabs(const vdbl & P){
  double r(0.0);
  for (size_t i=0;i<P.size();++i)
    r += absdbl(P[i]);
  return r;
}

double find_scale(const vdbl & P){
  int n=P.size()-1;
  vector<double> x,y;
  for (int i=0;i<=n;++i){
    double a=absdbl(P[i]);
    if (a==0)
      continue;
    x.push_back(n-i);
    y.push_back(log(a));
  }
  if (x.empty())
    return 1;
  double a,b,r;
  linreg(x,y,a,b,r);
  return exp(-a);
}

void rescale(vdbl & P, dbl l){
  if (l==dbl(1)) return;
  dbl ll=l;
  for (int i=P.size()-2;i>=0;--i){
    P[i] = ll*P[i];
    ll = ll*l;
  }
  dbl c=P[0];
  for (size_t i=0;i<P.size();++i)
    P[i] = P[i]/c;
}

bool dkw(const vdbl & P0,int N,double eps,vdbl & R){
  bool real=true;
  for (size_t i=0;real && i<P0.size();++i){
    if (imdbl(P0[i])!=0)
      real=false;
  }
  dbl dr=find_shift(P0);
  vdbl P=shift(P0,-dr);
  double l=find_scale(P);
  rescale(P,l);
  int deg=P0.size()-1;
  // init R if not already done
  if (R.size()!=deg){
    dbl w(0.0,2.0*M_PI/deg);
    w=exp(w);
    R.push_back(dbl(1.0));
    dbl wk=w;
    for (int i=1;i<deg;++i){
      R.push_back(wk);
      wk = wk*w;
    }
  }
  vdbl newR(deg);
  int ok=0;
  N *= P.size();
  double delta=0;
  for (int k=0;k<N;++k){
    delta=0;
    for (int i=0;i<deg;++i){
      dbl & zi=R[i];
      dbl d=horner_rem(P,zi,0);
      dbl p(1.0);
      for (int j=0;j<deg;++j){
	if (j==i) continue;
	p = p*(zi-R[j]);
      }
      if (absdbl(p)==0)
	return false;
      d = d/p;
      delta += absdbl(d);
      newR[i]=zi-d;
    }
    newR.swap(R);
    if (debug_info>0)
      cout << k << ": " << delta << "\n";
    if (delta<eps*sumabs(R))
      ++ok;
    else
      ok=0;
    if (ok==2){
      // rescale and translate
      for (size_t j=0;j<R.size();++j){
        R[j] = dbl(l)*R[j]-dr;
      }
      sort(R.begin(),R.end(),dbl_less);
      return true;
    }
  }
  cout << "Durand-Kerner-Weierstrass: too many iterations " << N << " delta " << delta << "\n";
  return false;
}

// find r=P(x) and r1=diff(P)(x)
// if |x|>1 this may overflow
void horner2(const vdbl & P,dbl x,dbl & r,dbl & r1){
  r=r1=0;
  if (P.empty())
    return ;
  size_t s=P.size()-1;
  for (size_t i=0;i<s;++i){
    r=r*x+P[i];
    r1=r1*x+r;
  }
  r=r*x+P[s];
}

void convert(const vdbl & P,vfdbl & fP){
  int s=P.size();
  fP.clear(); fP.reserve(s);
  for (int i=0;i<s;++i){
    dbl real,imag;
    reim(P[i],real,imag,context0);
    fP.push_back(fdbl(evalf_double(real,1,context0)._DOUBLE_val,evalf_double(imag,1,context0)._DOUBLE_val));
  }
}

void convert(const vfdbl & fP,vdbl & P){
  int s=fP.size();
  P.clear(); P.reserve(s);
  for (int i=0;i<s;++i){
    P.push_back(dbl(double(fP[i].real()),double(fP[i].imag())));
  }
}

double l1norm(const vdbl & v){
  double r=0;
  for (int i=0;i<v.size();++i)
    r += absdbl(v[i]);
  return r;
}

void div(vdbl & v,double r){
  r=1/r;
  for (int i=0;i<v.size();++i)
    v[i] = r*v[i];
}

#if 0
// approx largest root in norm, using a few iterations of power method
double largest(const vdbl & fP,int maxiter=100,double eps=1e-6){
  int deg=fP.size()-1;
  vdbl v(deg);
  for (int i=0;i<deg;++i)
    v[i]=dbl(rand()/(1.0+RAND_MAX),rand()/(1.0+RAND_MAX));
  div(v,l1norm(v));
  vdbl w(deg);
  double oldR(0.0);
  for (int j=0;j<maxiter;++j){
    for (int i=0;i<deg-1;++i){
      w[i+1]=v[i];
    }
    dbl r(0);
    for (int i=0;i<deg;++i){
      r += fP[i+1]*v[i];
    }
    w[0]= -r/fP[0];
    double R=l1norm(w);
    if (debug_info)
      cout << "power method " << j << " " << R << "\n";
    div(w,R);
    if (j>5 && abs(1-R/oldR)<eps)
      return R;
    v.swap(w);
    oldR=R;
  }
  return oldR;
}

#else
double largest(const vdbl & P,int maxiter=100,double eps=1e-6){
  vfdbl fP; convert(P,fP);
  return largest(fP,maxiter,eps);
}
#endif

bool aberth(const vdbl & P0,int nbits,int N,double eps,vdbl & R,bool allow_recursion){
  bool real=true;
  for (size_t i=0;real && i<P0.size();++i){
    if (imdbl(P0[i])!=0)
      real=false;
  }
  int deg=P0.size()-1;
  vdbl P(P0);
  dbl dr(0);
  dbl l(1);
  if (R.size()!=deg){
    // init R if not already done, using single precision Aberth
    vfdbl fP,fR;
    convert(P,fP);
    aberth(fP,N,1e-4,fR,true);
    convert(fR,R);
  }
  accurate_evalf(P,nbits);
  accurate_evalf(R,nbits);
  vdbl Prev(P);
  reverse(Prev.begin(),Prev.end());
  vdbl newR(deg);
  vector<bool> zi_done(deg,false);
  int ok=0; double delta;
  for (int k=0;k<N;++k){
    delta=0;
    for (int i=0;i<deg;++i){
      if (!ok && zi_done[i]){ // always do the last iteration for accuracy
        newR[i]=R[i];
        continue;
      }
      dbl & zi=R[i];
      dbl d,d1;
      if (absdbl(zi)>1){
        dbl gamma(inv(zi));
        horner2(Prev,gamma,d,d1);
        if (!is_exactly_zero(d)){
          d=gamma*(dbl(deg)-gamma*d1/d);
          if (is_exactly_zero(d))
            return false;
          d=inv(d);
        }
      }
      else {
        horner2(P,zi,d,d1);
        if (is_exactly_zero(d1))
          return false;
        d=d/d1;
      }
      dbl p(0);
      for (int j=0;j<deg;++j){
	if (j==i) continue;
        dbl dz=(zi-R[j]);
        if (is_exactly_zero(dz))
          return false;
	p += inv(dz);
      }
      double dd=absdbl(d),pp=absdbl(p);
      if (!ok && allow_recursion && dd<cluster_step && dd*pp>cluster_dp){
        // cluster of roots, find all roots in this cluster
        int cend=i+1;
        dbl sumR=zi;
        for (int k=cend;k<deg;++k){
          if (absdbl(zi-R[k])<deg/pp){
            swap(R[cend],R[k]);
            swap(zi_done[cend],zi_done[k]);
            sumR+=R[cend];
            ++cend;
          }
        }
        // cluster is from i to cend-1 included
        dbl z=sumR/dbl(cend-i); // center of gravity of cluster
        // shift P and reverse (roots become inverse of roots)
        vdbl Pcluster(shift(P,z)),Rcluster(deg);
#ifdef REV
        reverse(Pcluster.begin(),Pcluster.end());
        dbl D(dbl(cend-i)/d);
        for (int k=0;k<deg;++k){
          Rcluster[k]=inv(R[k]-z);
          if (k>=i && k<cend){
            dbl a(0.0,0.7+(k-i)*2*M_PI/(cend-i));
            Rcluster[k]=D*exp(a);
          }
        }
#else
        for (int k=0;k<deg;++k)
          Rcluster[k]=R[k]-z;
#endif          
        // recursive call of aberth
        if (aberth(Pcluster,nbits,N,eps,Rcluster,false)){
#ifdef REV
          for (int k=0;k<deg;++k)
            R[k]=l*(inv(Rcluster[k])+z)-dr;
#else
          for (int k=0;k<deg;++k)
            R[k]=l*(Rcluster[k]+z)-dr;
#endif
          return true;
        }
      }
      d=d/(dbl(1)-d*p);
      double abszi=absdbl(zi);
      double absdz=abszi==0?absdbl(d):absdbl(d)/abszi;
      if (absdz<eps/deg)
        zi_done[i]=true;
      delta += absdz;
      newR[i]=zi-d;
    }
    newR.swap(R);
    if (debug_info>0){
      cout << "Aberth multi "<< (allow_recursion?"":" rec") << k  << ": " << delta << " time " << clock()*1e-6 << "\n";
      if (debug_info>1){
        vdbl RR(R);
        accurate_evalf(RR,45);
        cout << "Current approx roots " << RR << "\n";
      }
    }
    if (delta<eps*deg)
      ++ok;
    else
      ok=0;
    if (ok==2){
      // rescale and translate
      for (size_t j=0;j<R.size();++j){
        R[j] = l*R[j] - dr;
      }
      sort(R.begin(),R.end(),dbl_less);
      return true;
    }
  }
  cout << "Aberth: too many iterations " << N << " delta " << delta << "\n";
  return false;  
}

bool read_poly(const string & filename,vdbl & P){
  P.clear();
  ifstream i(filename.c_str());
  while (1){
    dbl z;
    i >> z;
    if (i.eof())
      break;
    P.push_back(z);
  }
  return true;
}

vdbl p_coeff(const vdbl & R){
  vdbl P;
  P.reserve(R.size()+1);
  P.push_back(dbl(1));
  for (size_t i=0;i<R.size();++i){
    dbl z=R[i];
    // P*(x-z)
    P.push_back(-z*P.back());
    for (size_t j=P.size()-2;j>=1;--j){
      P[j] -= z*P[j-1];
    }
  }
  return P;
}

// max distance between 2 elements of R
double ecart(const vdbl & R){
  int n=R.size();
  double d=1e307;
  for (int i=0;i<n;++i){
    const dbl & Ri=R[i];
    for (int j=0;j<n;++j){
      if (j==i) continue;
      double dd=absdbl(Ri-R[j]);
      if (dd<d)
        d=dd;
    }
  }
  return d;
}

// Random check with a.out eps n, eps>0 (Aberth) and n<0 (random coeff) or n>0 (random roots)
int main(int argc,char ** argv){
  //srand(time(NULL));
  if (getenv("GIAC_DEBUG")){
    debug_info=atoi(getenv("GIAC_DEBUG"));
  }
  if (getenv("GIAC_N")){
    nbits=atoi(getenv("GIAC_N"));
  }
  if (getenv("GIAC_STEP")){
    cluster_step=atof(getenv("GIAC_STEP"));
  }
  if (getenv("GIAC_DP")){
    cluster_dp=atof(getenv("GIAC_DP"));
  }
  cout << setprecision(16)
       << "Bits precision: " << nbits
       << "\n";
  if (argc<3){
    cout << "Syntax " << argv[0] << " eps filename\n";
    return 1;
  }
  double eps=1;
  vdbl P,R;
  eps=atof(argv[1]);
  if (eps>1e-4){
    cout << "Syntax " << argv[0] << " eps filename (replace filename with N or with root1 ... rootn to check)\n";
    return 1;
  }
  if (argc==3){
    int n=0;
    if (argv[1][0]=='-' || (argv[1][0]>'0' && argv[1][0]<='9') )
      n=atoi(argv[2]);
    if (n==0){
      if (!read_poly(argv[2],P))
	return 1;
    }
    else {
      int N=n<0?-n:n;
      dbl M(1/(RAND_MAX+1.0));
      if (n<0)
        R.push_back(dbl(1.0));
      for (int i=0;i<N;++i){
	dbl z(rand(),rand());
	z=M*z;
	R.push_back(z);
      }
      if (n<0)
	P=R;
      else {
	sort(R.begin(),R.end(),dbl_less);
	cout << "Random roots ecart " << ecart(R) << "\nRoots: " << R << "\n";
	accurate_evalf(R,nbits);
	P=p_coeff(R);
      }
    }
  }
  else { // check: polynom given by (real) roots
    for (int i=2;i<argc;++i){
      R.push_back(atof(argv[i]));
    }
    accurate_evalf(R,nbits);
    P=p_coeff(R);
  }
  accurate_evalf(P,nbits);
  vdbl PP(P);
  accurate_evalf(PP,45);
  cout << "Polynom "  << PP << "\n";
  R.clear();
  if (!aberth(P,nbits,50,eps,R,true)){
    cout << "Unable to find roots\n";
    return 2;
  }
  vdbl RR(R);
  accurate_evalf(RR,45);
  cout << "Result roots " << RR << "\n";
  vdbl PR(p_coeff(R));
  cout << "Precision ";
  double prec=0;
  for (size_t i=1;i<PR.size();++i){
    double a=absdbl(P[0]*PR[i]-P[i]),b=absdbl(P[i]);
    double c=(b==0?a:a/b);
    if (c>prec)
      prec=c;
    cout << c << " " ;
  }
  cout << "\nMax. precision : " << prec << "\n";
}
