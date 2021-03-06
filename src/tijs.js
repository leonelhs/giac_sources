/* some JS initializations for the TI Nspire */
var rectf=graphic.fillRect;
var pixon=graphic.setPixel;
var pi=Expression("pi");
var n = Expression("n");
var x = Expression("x");
var y = Expression("y");
var z = Expression("z");
var t = Expression("t");
var inf=Expression("inf");
var oo=Expression("oo");
var xcas=e=>Expression(cas.caseval(e));
var tran=transpose;
var input=cas.prompt;
var min=Math.min;
var max=Math.max;
var sign=Math.sign;

function solve(f,x){
    if (!x)
	x='x';
    return xcas('solve('+f+','+x+')');
}

function fsolve(f,x){
    if (!x)
	x='x';
    return xcas('fsolve('+f+','+x+')');
}

function linsolve(f,x){
    return xcas('linsolve('+f+','+x+')');
}

function csolve(f,x){
    if (!x)
	x='x';
    return xcas('csolve('+f+','+x+')');
}

function integrate(f,n,a,b){
    if (f instanceof Polynomial || f instanceof Series)
	return f.integ();
    if (f instanceof Fraction){
	n='X';
    }
    if (!n)
	n='x';
    if (a && b)
	return xcas('integrate('+f+','+n+','+a+','+b+')');
    return xcas('integrate('+f+','+n+')');
}

function diff(f){
    if (f instanceof Polynomial || f instanceof Series || f instanceof Fraction)
	return f.deriv();
    return xcas('diff('+f+')');
}

function limit(f,v,a,pos){ 
    if (a===undefined)
	return "Beware that variable=value will affect variable. Correct syntax limit(expression,variable,limit_point).";
    let s=f+','+v+','+a;
    if (pos)
	s += ','+pos;
    return xcas('limit('+s+')');
}

function series(f,v,a,n){ 
    if (a===undefined || n===undefined)
	return "Beware that variable=value will affect variable. Correct syntax limit(expression,variable,limit_point).";
    let s=f+','+v+','+a+','+n;
    return xcas('series('+s+')');
}

function sum(f,n,a,b){
    if (!n)
	n='n';
    if (a && b)
	return xcas('sum('+f+','+n+','+a+','+b+')');
    return xcas('sum('+f+','+n+')');
}

function product(f,n,a,b){
    return xcas('product('+f+','+n+','+a+','+b+')');
}

function ifactor(n){
    return xcas('ifactor('+n+')');
}

function irem(p,q){
    return xcas('irem('+p+','+q+')');
}

function iquo(p,q){
    return xcas('iquo('+p+','+q+')');
}

function round(p){
    return xcas('round('+p+')');
}

function ceil(p){
    return xcas('ceil('+p+')');
}

function floor(p){
    return xcas('floor('+p+')');
}

function exact(p){
    return xcas('exact('+p+')');
}

function factor(p){
    if (Integer.isInteger(p))
	return xcas('ifactor('+p+')');
    return xcas('factor('+p+')');
}

var proot = Polynomial.roots;

function pcoeff(p){
    return xcas('pcoeff('+p+')');
}

function partfrac(n){
    return xcas('partfrac('+n+')');
}

function cpartfrac(n){
    return xcas('cpartfrac('+n+')');
}

function cfactor(n){
    return xcas('cfactor('+n+')');
}

function resultant(p,q,x){
    if (!x) x='x';
    return xcas('resultant('+p+','+q+','+x+')');
}

function quo(p,q,x){
    if (!x) x='x';
    return xcas('quo('+p+','+q+','+x+')');
}

function rem(p,q,x){
    if (!x) x='x';
    return xcas('rem('+p+','+q+','+x+')');
}

function quorem(p,q,x){
    if (!x) x='x';
    return xcas('quorem('+p+','+q+','+x+')');
}

function egcd(p,q,x){
    if (!x) x='x';
    return xcas('egcd('+p+','+q+','+x+')');
}

function abcuv(a,b,c,x){
    if (!x) x='x';
    return xcas('abcuv('+a+','+b+','+c+','+x+')');
}

function simplify(p){
    return xcas('simplify('+p+')');
}

function regroup(p){
    return xcas('regroup('+p+')');
}

function normal(p){
    return xcas('normal('+p+')');
}

function texpand(p){
    return xcas('texpand('+p+')');
}

function tlin(p){
    return xcas('tlin('+p+')');
}

function tcollect(p){
    return xcas('tcollect('+p+')');
}

function evalf(p,prec){
    if (prec)
	return cas.caseval('evalf('+p+','+prec+')');
    return xcas('evalf('+p+')');
}

function ranm(m,n,loi){
    if (!n) n=m;
    if (!loi)
	return xcas('ranm('+m+','+n+')');
    return xcas('ranm('+m+','+n+','+loi+')');    
}

function ranv(m,loi){
    if (!loi)
	return xcas('ranv('+m+')');
    return xcas('ranv('+m+','+loi+')');    
}

function plot(f,x,xmin,xmax){
    if (!x)
	x='x';
    if (!xmin)
	return xcas('plot('+f+','+x+')');
    return xcas('plot('+f+','+x+','+xmin+','+xmax+')');
}

function plotfunc(f,x){
    if (!x)
	x='x';
    return xcas('plotfunc('+f+','+x+')');
}

function plotparam(f,x,xmin,xmax){
    if (!x)
	x='t';
    if (!xmin)
	return xcas('plotparam('+f+','+x+')');
    return xcas('plotparam('+f+','+x+','+xmin+','+xmax+')');
}

function plotpolar(f,x,xmin,xmax){
    if (!x)
	x='x';
    if (!xmin)
	return xcas('plotpolar('+f+','+x+')');
    return xcas('plotpolar('+f+','+x+','+xmin+','+xmax+')');
}

function barplot(f){
    return xcas('barplot('+f+')');
}

function plotlist(f){
    return xcas('plotlist('+f+')');
}

function plotfield(f,v){
    return xcas('plotfield('+f+','+v+')');
}

function plotseq(f,u0,N){
    return xcas('plotseq('+f+','+u0+','+N+')');
}

function linear_regression_plot(lx,ly){
    return xcas('linear_regression_plot('+lx+','+ly+')');
}

function exponential_regression_plot(lx,ly){
    return xcas('exponential_regression_plot('+lx+','+ly+')');
}

function logarithmic_regression_plot(lx,ly){
    return xcas('logarithmic_regression_plot('+lx+','+ly+')');
}

function sin_regression_plot(lx,ly){
    return xcas('sin_regression_plot('+lx+','+ly+')');
}

function power_regression_plot(lx,ly){
    return xcas('power_regression_plot('+lx+','+ly+')');
}

function scatterplot(lx,ly){
    return xcas('scatterplot('+lx+','+ly+')');
}

function histogram(f,cmin=0,csize=1){
    return xcas('histogram('+f+','+cmin+','+csize+')');
}

function egv(p){
    return xcas('egv('+p+')');
}

function egvl(p){
    return xcas('egvl('+p+')');
}

function rref(p){
    return xcas('rref('+p+')');
}

function matpow(p,n){
    return xcas('matpow('+p+','+n+')');
}

function rgb(a,b,c){
    if (a>=0 && a<=1 && b>=0 && b<=1 && c>=0 && c<=1){
	a=Math.floor(255*a+.5); b=Math.floor(255*b+.5); c=Math.floor(255*c+.5);
    }
    if (a<0 || a>255 || b<0 || b>255 || c<0 || c>255)
	return undefined;
    return ( Math.floor(a*32/256)<<11 ) | (Math.floor(b*64/256)<<5) | (Math.floor(c*32/256)); 
}

var red=rgb(255,0,0),green=rgb(0,255,0),blue=rgb(0,0,255),
    cyan=rgb(0,255,255),magenta=rgb(255,0,255),yellow=rgb(255,255,0),
    white=65535,black=0,filled=1073741824; // 2^30

function draw_circle(x,y,r,c=0){
    return cas.caseval('draw_circle('+x+','+y+','+r+','+c+')');
}

function draw_arc(x,y,rx,ry,t1=0,t2=2*Math.PI,c=0){
    return cas.caseval('draw_arc('+x+','+y+','+rx+','+ry+','+t1+','+t2+','+c+')');
}

function draw_line(x1,y1,x2,y2,c=0){
    return cas.caseval('draw_line('+x1+','+y1+','+x2+','+y2+','+c+')');
}

function draw_polygon(xy,c=0){
    return cas.caseval('draw_polygon('+xy+','+c+')');
}

function draw_string(x,y,r,c=0){
    return cas.caseval('draw_string('+x+','+y+',"'+r+'",'+c+')');
}

/* Mandelbrot fractal with reals */
function fra(x_,y_,Nmax){
    var x,y,zx,zy,zt,cx,cy,j,w,h;
    w=2.7/x_;
    h=-1.87/y_;
    for(y=0;2*y<y_;++y){
	cx=-2.1;cy=(h*y+0.935);
	for (x=0;x<x_;++x){
	    zx=0;zy=0;
	    for (j=0;j<Nmax;++j){
		zt=zx*zx-zy*zy+cx;
		zy=2*zx*zy+cy;
		zx=zt;
		if (zx*zx+zy*zy>4) break;
	    }
	    pixon(x,y,126*j+2079);
	    pixon(x,y_-y,126*j+2079);
	    cx += w;
	}
	if (y%4==3) pixon();
    }
}
// !!! End char must remain, obtained with Ctrl-Q Ctrl-@ 
