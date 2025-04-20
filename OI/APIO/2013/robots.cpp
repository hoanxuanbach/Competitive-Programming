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
const long long inf=1e18;
const int mod=998244353;
const int maxn=505;
const int B=650;
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
const int base=101;

int n,W,H,dp[10][10][maxn*maxn];
vector<int> g[maxn*maxn];
bool cn[maxn*maxn];
int nxt[maxn][maxn][4],pos[10];
char c[maxn][maxn];
int dx[]={0,1,0,-1},
    dy[]={1,0,-1,0};

bool check(int x,int y){
    return (x<0 || x>=H || y<0 || y>=W || c[x][y]=='x');
}

int dfs(int x,int y,int t){
    if(nxt[x][y][t]) return nxt[x][y][t];
    nxt[x][y][t]=-1;
    int T=t;
    if(c[x][y]=='A') t=(t+3)%4;
    else if(c[x][y]=='C') t=(t+1)%4;
    int xt=x+dx[t],yt=y+dy[t];
    if(check(xt,yt)) return nxt[x][y][T]=x*W+y+1;
    else return nxt[x][y][T]=dfs(xt,yt,t);
}

void solve(){
    cin >> n >> W >> H;
    for(int i=0;i<H;i++) for(int j=0;j<W;j++){
        cin >> c[i][j];
        if(c[i][j]>='1' && c[i][j]<='9') pos[c[i][j]-'0']=i*W+j+1;

    }
    for(int i=0;i<H;i++) for(int j=0;j<W;j++) for(int t=0;t<4;t++) if(!check(i,j)){
        int x=dfs(i,j,t);
        if(x!=-1){
            g[i*W+j+1].push_back(x);
            //cout << i << ' ' << j << ' ' << t << ' ' << (x-1)/W << ' ' << (x-1)%W << '\n';
        }
    }
    int S=H*W;
    for(int l=1;l<=n;l++) for(int r=l;r<=n;r++) for(int i=1;i<=S;i++) dp[l][r][i]=inf;
    for(int i=1;i<=n;i++) dp[i][i][pos[i]]=0;
    for(int len=1;len<=n;len++) for(int l=1;l<=n-len+1;l++){
        int r=l+len-1;
        for(int i=1;i<=S;i++) cn[i]=false;
        for(int i=1;i<=S;i++) for(int x=l;x<r;x++) dp[l][r][i]=min(dp[l][r][i],dp[l][x][i]+dp[x+1][r][i]);
        priority_queue<pii,vector<pii>,greater<pii>> pq;
        for(int i=1;i<=S;i++) if(dp[l][r][i]!=inf) pq.push({dp[l][r][i],i});
        while(!pq.empty()){
            auto [d,u]=pq.top();pq.pop();
            if(dp[l][r][u]!=d) continue;
            for(int v:g[u]) if(dp[l][r][v]>dp[l][r][u]+1) pq.push({dp[l][r][v]=dp[l][r][u]+1,v});
        }
    }
    int res=inf;
    for(int i=1;i<=S;i++) res=min(res,dp[1][n][i]);
    cout << (res==inf?-1:res) << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
