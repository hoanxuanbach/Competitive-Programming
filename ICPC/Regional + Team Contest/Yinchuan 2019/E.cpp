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
#include<bits/stdc++.h>
using namespace std;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_real_distribution<> pp(0.0,1.0);
#define ld long double
#define pii pair<int,int>
#define piii pair<int,pii>
#define fi first
#define se second
typedef unsigned long long ull;
typedef long long ll;
const int inf=1e9;
const int mod=998244353;
const int mod2=1e9+7;
const int maxn=100005;
const int maxq=500005;
const int maxl=20;
const int maxa=1000005;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
ull ans[maxn],num[maxn][4];
int n,k,a[maxn],par[maxn][maxl],c1,c2;
vector<int> edge[maxn],child[maxn];
void dfs1(int u){
    num[u][0]=num[u][1]=0;
    num[u][(a[u]>>c1)&1]++;
    for(int v:edge[u]){
        dfs1(v);
        for(int j=0;j<=1;j++) num[u][j]+=num[v][j];
    }
    for(int x:child[u]) num[u][(a[x]>>c1)&1]--;
    ans[u]+=(num[u][0]*num[u][1])*(1ULL<<c1)*(1ULL<<c1);
}
void dfs2(int u){
    num[u][0]=num[u][1]=num[u][2]=num[u][3]=0;
    num[u][((a[u]>>c1)&1)<<1|((a[u]>>c2)&1)]++;
    for(int v:edge[u]){
        dfs2(v);
        for(int j=0;j<=3;j++) num[u][j]+=num[v][j];
    }
    for(int x:child[u]) num[u][((a[x]>>c1)&1)<<1|((a[x]>>c2)&1)]--;
    ans[u]+=(num[u][1]*num[u][2]+num[u][3]*num[u][0])*(1ULL<<c1)*(1ULL<<c2)*2ULL;
}
void solve(){
    cin >> n >> k;
    for(int i=1;i<=n;i++) cin >> a[i];
    for(int i=2;i<=n;i++){
        int p;cin >> p;
        par[i][0]=p;edge[p].push_back(i);
    }
    for(int i=1;i<=18;i++){
        for(int j=1;j<=n;j++) par[j][i]=par[par[j][i-1]][i-1];
    }
    for(int i=1;i<=n;i++){
        int u=i;
        for(int j=0;j<=18;j++){
            if((k+1)&(1<<j)) u=par[u][j];
        }
        if(u!=0) child[u].push_back(i);
    }
    for(c1=0;c1<=29;c1++) dfs1(1);
    for(c1=0;c1<=29;c1++){
        for(c2=c1+1;c2<=29;c2++) dfs2(1);
    }
    for(int i=1;i<=n;i++) cout << ans[i] << '\n';
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}