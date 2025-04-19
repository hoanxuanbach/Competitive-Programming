// Judges with GCC >= 12 only needs Ofast
// #pragma GCC optimize("O3,no-stack-protector,fast-math,unroll-loops,tree-vectorize")
// MLE optimization
// #pragma GCC optimize("conserve-stack")
// Old judges
// #pragma GCC target("sse4.2,popcnt,lzcnt,abm,mmx,fma,bmi,bmi2")
// New judges. Test with assert(__builtin_cpu_supports("avx2"));
// #pragma GCC target("avx2,popcnt,lzcnt,abm,bmi,bmi2,fma,tune=native")
// Atcoder
// #pragma GCC target("avx2,popcnt,lzcnt,abm,bmi,bmi2,fma")
/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;
- insert(x),erase(x)
- find_by_order(k): return iterator to the k-th smallest element
- order_of_key(x): the number of elements that are strictly smaller
*/

#include<bits/stdc++.h>
using namespace std;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_real_distribution<> pp(0.0,1.0);
#define int long long
#define ld long double
#define pii pair<int,int>
#define piii pair<int,pii>
#define mpp make_pair
#define fi first
#define se second
const int inf=1e9;
const int mod=998244353;
const int maxn=115;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=25;
const int maxa=1000000;
const int root=3;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
const int iroot=power(3,mod-2);
const int base=131;

const double eps = 1e-9;

int n,S,X[2*maxn],Y[2*maxn];
double dd[2*maxn][2*maxn];

double dot(double x0,double y0,double x1,double y1,double x2,double y2){
    return (x1-x0)*(x2-x0)+(y1-y0)*(y2-y0);
}

double cross(double x0,double y0,double x1,double y1){
    return x0*y1-x1*y0;
}

double cross(double x0,double y0,double x1,double y1,double x2,double y2){
    return cross(x1-x0,y1-y0,x2-x0,y2-y0);
}

int isect(double x0,double y0,double x1,double y1,double x2,double y2,double x3,double y3){
    if(abs(cross(x1-x0,y1-y0,x3-x2,y3-y2))<eps) return 0;
    double a = cross(x0,y0,x2,y2,x3,y3)*cross(x1,y1,x2,y2,x3,y3);
    double b = cross(x2,y2,x0,y0,x1,y1)*cross(x3,y3,x0,y0,x1,y1);
    return (a<eps && b<-eps) || (a<-eps && b<eps);
}

int cut(double x0,double y0,double x1,double y1){
    if(y0<y1) swap(y0,y1),swap(x0,x1);
    return y0>0 && y1<=0 && cross(x0,y0,x1,y1)<0;
}

void add(int i,int j,int x0,int y0,int x1,int y1,int x2,int y2){
    double t=(x1==x2 && y1==y2?0:min(max(dot(x1,y1,x0,y0,x2,y2)/dot(x1,y1,x2,y2,x2,y2),0.0),1.0));
    double x3=x1+(x2-x1)*t,y3=y1+(y2-y1)*t;
    //cout << x0 << ' ' << y0 << ' ' << x1 << ' ' << y1 << ' ' << x2 << ' ' << y2 << ' ' << x3 << ' ' << y3 << '\n';
    if(isect(x0,y0,x3,y3,S,S,S,-S)) return;
    if(isect(x0,y0,x3,y3,S,-S,-S,-S)) return;
    if(isect(x0,y0,x3,y3,-S,-S,-S,S)) return;
    if(isect(x0,y0,x3,y3,-S,S,S,S)) return;
    if(abs((x0+x3)/2)<=S-eps && abs((y0+y3)/2)<=S-eps) return;
    int i0=i<<1,i1=i0|1,j0=j<<1,j1=j0|1;
    double d = sqrtl(dot(x0,y0,x3,y3,x3,y3));
    //cout << i << ' ' << j << ' ' << d << '\n';
    int c = cut(X[i0],Y[i0],x0,y0)^cut(x0,y0,x3,y3)^cut(x3,y3,X[j0],Y[j0]);
    if(c){
        dd[i0][j1]=dd[j1][i0]=min(dd[i0][j1],d);
        dd[i1][j0]=dd[j0][i1]=min(dd[i1][j0],d);
    }
    else{
        dd[i0][j0]=dd[j0][i0]=min(dd[i0][j0],d);
        dd[i1][j1]=dd[j1][i1]=min(dd[i1][j1],d);
    }
}

void solve(){
    cin >> n >> S;n+=4;
    X[0]=X[1]=X[4]=X[5]=Y[0]=Y[1]=Y[6]=Y[7]=S;
    X[2]=X[3]=X[6]=X[7]=Y[2]=Y[3]=Y[4]=Y[5]=-S;
    for(int i=8;i<2*n;i++) cin >> X[i] >> Y[i];
    for(int i=0;i<2*n;i++) for(int j=0;j<2*n;j++) dd[i][j]=(i==j?0:inf);
    for(int i=0;i<n;i++) for(int j=0;j<n;j++) if(i!=j){
        add(i,j,X[i<<1],Y[i<<1],X[j<<1],Y[j<<1],X[j<<1|1],Y[j<<1|1]);
        add(i,j,X[i<<1|1],Y[i<<1|1],X[j<<1],Y[j<<1],X[j<<1|1],Y[j<<1|1]);
    }
    for(int k=0;k<2*n;k++) for(int i=0;i<2*n;i++) for(int j=0;j<2*n;j++){
        dd[i][j]=min(dd[i][j],dd[i][k]+dd[k][j]);
    }
    double ans = inf;
    for(int i=0;i<n;i++) ans=min(ans,dd[i<<1][i<<1|1]);
    cout << setprecision(10) << fixed << ans << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
