// -*- mode:C++; compile-command: "g++ -g proot.cc -o proot && g++ -g proot.cc -DPM -o mproot -lgiac" -*-
// Polynomial roots for small degrees (<= about 30)
#include <fstream>
#include <iostream>
#include <vector>
#include <complex>
#include <algorithm>
#include <iomanip>
#include <cmath>
//#define MP 1
int nbits=100;
#ifdef MP
#include <giac/config.h>
#include <giac/giac.h>
using namespace giac;
#endif
using namespace std;

int debug_info=0;

#ifdef MP
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
dbl precise_evalf(double d,int nbits){
  return accurate_evalf(gen(d),nbits);
}
#else
typedef complex<long double> dbl;
//typedef complex<float> dbl;
inline double absdbl(const dbl & x){
  return abs(x);
}
inline dbl re(const dbl & x){
  return dbl(x.real(),0);
}
inline double redbl(const dbl & x){
  return x.real();
}
inline double imdbl(const dbl & x){
  return x.imag();
}
inline bool is_exactly_zero(const dbl & x){
  return x.real()==0 && x.imag()==0;
}
dbl inv(const dbl z){
  return dbl(1.0)/z;
}

bool dbl_less(const dbl & x,const dbl & y){
  if (x.real()!=y.real())
    return x.real()<y.real();
  return x.imag()<y.imag();
}
dbl precise_evalf(double d,int nbits){
  return d;
}
#endif


typedef vector<dbl> vdbl;
ostream & operator << (ostream & os,const vdbl & P){
  for (int i=0;i<P.size();++i)
    os << P[i] << " ";
  return os;
}

void accurate_evalf(vdbl & P,int nbits){
#ifdef MP
  for (int i=0;i<P.size();++i)
    P[i]=accurate_evalf(P[i],nbits);
#endif
}

dbl horner(const vdbl & P,dbl x,vdbl * Q){
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

// find 1 complex root of P, not in roots, starting at z, max iter N, prec eps
bool newt1(const vdbl & P,const vdbl & roots,int N,double eps,dbl & z){
  vdbl Q;
  int ok=0;
  for (int i=0;i<N;++i){
    dbl Pz=horner(P,z,&Q);
    dbl P1z=horner(Q,z,0);
    if (absdbl(P1z)<eps*l1(Q,z))
      return false;
    dbl delta;
    if (roots.empty())
      delta = Pz/P1z;
    else {
      dbl r=P1z/Pz;
      for (size_t j=0;j<roots.size();++j){
        dbl delta=z-roots[j];
        if (absdbl(delta)<eps)
          return false;
        r -= dbl(1)/delta;
      }
      delta = dbl(1)/r;
    }
    z -= delta;
    double absdz=absdbl(delta),absz=absdbl(z);
    if (absdbl(Pz)<eps*l1(P,z) && (absdz<eps*absz || (absz<eps && absdz<eps)) )
      ++ok;
    else
      ok=0;
    if (ok==2)
      return true;
  }
  return false;
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
    dbl Pz=horner(P,d,&Q);
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

bool proot(const vdbl & P0,int N,double eps,vdbl & R){
  bool real=true;
  for (size_t i=0;real && i<P0.size();++i){
    if (imdbl(P0[i])!=0)
      real=false;
  }
  dbl dr=find_shift(P0);
  vdbl P=shift(P0,-dr);
  double l=find_scale(P);
  rescale(P,l);
#if 0
  if (P.back()==dbl(0)){
    P.pop_back();
    if (!proot(P,N,eps,R))
      return false;
    R.push_back(-dr);
    return true;
  }
#endif
  R.clear();
  vdbl Q; // auxiliary 
  dbl z=0; double M=.5/RAND_MAX;
  for (size_t i=0;i<N*P.size();++i){
    if (R.size()==P.size()-2)
      R.push_back(-P[1]/P[0]-sum(R));
    if (R.size()==P.size()-1){
      for (size_t j=0;j<R.size();++j){
        R[j] = dbl(l)*R[i]-dr;
      }
      sort(R.begin(),R.end(),dbl_less);
      return true;
    }
    if (newt1(P,R,N,eps,z)){
      R.push_back(z);
      if (real){
	if (abs(imdbl(z))>eps) // non real root, add conjugate
	  R.push_back(conj(z));
	else // clear imaginary part
	  R.back()=re(R.back());
	z=dbl(rand());
      }
      else
	z=dbl(rand(),rand());
      z=dbl(M)*z;
      continue;
    }
    M *= 2;
    z=dbl(rand(),rand());
    z=dbl(M)*z;
  }
  cout << "Newton: too many iterations " << N*P.size() << "\n";
  return false;
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
      dbl d=horner(P,zi,0);
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

double cross_prod(const vdbl & v,int a,int b,int c){
  dbl ab=v[b]-v[a],ac=v[c]-v[a];
  double A=redbl(ab),B=imdbl(ab),C=redbl(ac),D=imdbl(ac);
  return A*D-B*C;
}

vector<int> convexhull(const vdbl & v){
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

void init_R(const vdbl & P,vdbl & R){
  R.clear();
  int n=P.size()-1;
  vdbl l;
  vector<int> lpos;
  for (int i=0;i<=n;++i){
    double ai=absdbl(P[n-i]);
    if (ai==0)
      continue;
    l.push_back(dbl(double(i),log(ai)));
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
    double sigma=0.7;
    for (int j=0;j<dk;++j){
      double theta=sigma+2*M_PI*i/n+2*M_PI*j/dk;
      dbl z(uk*cos(theta),uk*sin(theta));
      R.push_back(z);
    }
  }
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

bool aberth(const vdbl & P0,int nbits,int N,double eps,vdbl & R){
  bool real=true;
  for (size_t i=0;real && i<P0.size();++i){
    if (imdbl(P0[i])!=0)
      real=false;
  }
  int deg=P0.size()-1;
  vdbl P(P0);
  // init R if not already done
  dbl dr(0);
  dbl l(1);
#ifdef MP
  if (R.size()!=deg)
    init_R(P,R);
  accurate_evalf(P,nbits);
  accurate_evalf(R,nbits);
#else
  if (R.size()!=deg){
    dr=find_shift(P);
    P=shift(P,-dr);
    l=precise_evalf(find_scale(P),nbits);
    rescale(P,l);
    init_R(P,R);
  }
#endif
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
      cout << k << ": " << delta << "\n";
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

vdbl pcoeff(const vdbl & R){
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
  cout << setprecision(16)
#ifdef MP
       << "Bits precision: " << nbits
#endif
       << "\n";
  if (argc<3){
    cout << "Syntax " << argv[0] << " eps filename\n";
    return 1;
  }
  double eps=1;
  vdbl P,R;
  eps=atof(argv[1]);
  bool runaberth=eps>0;
  if (!runaberth)
    eps=-eps;
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
	P=pcoeff(R);
      }
    }
  }
  else { // check: polynom given by (real) roots
    for (int i=2;i<argc;++i){
      R.push_back(atof(argv[i]));
    }
    accurate_evalf(R,nbits);
    P=pcoeff(R);
  }
  accurate_evalf(P,nbits);
  vdbl PP(P);
  accurate_evalf(PP,45);
  cout << "Polynom "  << PP << "\n";
  if (runaberth){
    R.clear();
    if (!aberth(P,nbits,50,eps,R)){
      cout << "Unable to find roots\n";
      return 2;
    }
  }
  else {
    if (!proot(P,50,eps,R)){
      cout << "Unable to find roots\n";
      return 2;
    }
  }
  vdbl RR(R);
  accurate_evalf(RR,45);
  cout << "Result roots " << RR << "\n";
  vdbl PR(pcoeff(R));
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
