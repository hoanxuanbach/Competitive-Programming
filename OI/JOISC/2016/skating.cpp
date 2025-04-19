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
//#define int long long
#define ld long double
#define pii pair<int,int>
#define piii pair<int,pii>
#define mpp make_pair
#define fi first
#define se second
//const int inf=1e18;
const int mod=1e9+7;
const int maxn=1005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=500005;
const int maxl=20;
const int maxa=250000;
const int root=3;
/*
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
const int iroot=power(3,mod-2);
*/
const int base=101;
int dx[]={0,0,-1,1},
    dy[]={-1,1,0,0};
char c[maxn][maxn];
int d[maxn][maxn];
pii f[maxn][maxn][4];
void solve(){
    int n,m;cin >> n >> m;
    for(int i=1;i<=n;i++){
        int cur=0;
        for(int j=1;j<=m;j++){
            cin >> c[i][j];
            f[i][j][0]={i,cur+1};
            if(c[i][j]=='#') cur=j;
        }
        cur=m+1;
        for(int j=m;j>=1;j--){
            f[i][j][1]={i,cur-1};
            if(c[i][j]=='#') cur=j;
        }
    }
    for(int i=1;i<=m;i++){
        int cur=0;
        for(int j=1;j<=n;j++){
            f[j][i][2]={cur+1,i};
            if(c[j][i]=='#') cur=j;
        }
        cur=n+1;
        for(int j=n;j>=1;j--){
            f[j][i][3]={cur-1,i};
            if(c[j][i]=='#') cur=j;
        }
    }
    memset(d,-1,sizeof(d));
    priority_queue<piii,vector<piii>,greater<piii>> pq;
    auto update = [&](int x,int y,int val){
        if(d[x][y]==-1 || d[x][y]>val){
            d[x][y]=val;
            pq.push({val,{x,y}});
        }
    };
    int sx,sy,tx,ty;cin >> sx >> sy >> tx >> ty;
    d[sx][sy]=0;pq.push({0,{sx,sy}});
    while(!pq.empty()){
        auto [dd,p]=pq.top();pq.pop();
        int x=p.fi,y=p.se;
        if(dd!=d[x][y]) continue;
        for(int t=0;t<4;t++){
            auto [nx,ny]=f[x][y][t];
            update(nx,ny,dd+1);
            int xt=x+dx[t],yt=y+dy[t];
            if(xt<=0 || yt<=0 || xt>n || yt>m || c[xt][yt]=='#') continue;
            update(xt,yt,dd+2);
        }
    }
    cout << d[tx][ty] << '\n';
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
