#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 998244353;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
 
const int maxn = 2e5+5;
const int inf = 1e18;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}

double h(double x,double y){
    return (5000-0.005*(x*x+y*y+x*y)+12.5*(x+y))*exp(-abs(0.000001*(x*x+y*y)-0.0015*(x+y)+0.7));
}
double dh(double x,double y){
    return -0.005*(2.0*x+y)+12.5-(5000-0.005*(x*x+y*y+x*y)+12.5*(x+y))*(0.000002*x-0.0015);
}
double dist(double ax,double ay,double bx,double by){
    ax-=bx;
    ay-=by;
    return sqrtl(ax*ax+ay*ay);
}

const int M = 5e6;
const double eps = 1e-7;
const double S = 1;

double get(double H,double y,double l,double r){
    double hl=h(l,y)-H,hr=h(r,y)-H;
    if(hl==0) return l;
    if(hr==0) return r;
    if(hl*hr>0) return (abs(hl)<abs(hr)?l:r);

    while(abs(r-l)>eps){
        double x=(l+r)/2;
        double hx=h(x,y)-H;
        if(hx*hl<=0) r=x,hr=hx; 
        else l=x,hl=hx;
    }
    return (l+r)/2;
}

double cal(double tx,double ty,double x,double H){
    double y=0,ret=0;
    for(int _=0;_<M;_++){
        double dx=dh(x,y),dy=dh(y,x);
        if(dx*(tx-x)+dy*(ty-y)<=0) return ret+dist(tx,ty,x,y);

        double nx=x,ny=y;
        if(abs(dx)<abs(dy)){
            nx=x+(x<tx?S:-S);
            ny=get(H,nx,y-S,y+S);
        }
        else{
            ny=y+(y<ty?S:-S);
            nx=get(H,ny,x-S,x+S);
        }
        ret+=dist(x,y,nx,ny);
        x=nx,y=ny;
    }
    return ret;
}

void solve(){
    double X=0,H=0;
    {
        double l=0,r=1600;
        while(abs(l-r)>eps){
            double x=(l+r)/2;
            if(dh(x,0)>0) l=x;
            else r=x;
        }
        X=l;
        H=h(X,0);
    }
    
    double res=cal(200,200,X,H)+cal(1400,1400,X,H);
    cout << setprecision(3) << fixed << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
