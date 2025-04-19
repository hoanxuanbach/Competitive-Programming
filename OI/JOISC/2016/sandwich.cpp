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
const int inf=1e18;
const int mod=998244353;
const int maxn=405;
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

int n,m,cnt;
int c[maxn][maxn],vis[maxn][maxn],check[maxn][maxn],ans[maxn][maxn];

int dx[]={0,0,1,-1},
    dy[]={-1,1,0,0};

bool dfs(int x,int y,int t){
    cnt++;
    vis[x][y]=t;
    for(int i=0;i<2;i++){
        int k=(i?(1<<i)+(t^c[x][y]):t);
        int xt=x+dx[k],yt=y+dy[k];
        if(xt<=0 || yt<=0 || xt>n || yt>m) continue;
        int nt=(i?(c[x][y]^c[xt][yt]^t):t);
        if(vis[xt][yt]==nt){
            if(check[xt][yt]) continue;
            return false;
        }
        if(vis[xt][yt]==(nt^1)) return false;
        if(!dfs(xt,yt,nt)) return false;
    }
    check[x][y]=1;
    return true;
}

void solve(){
    cin >> n >> m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            char cc;cin >> cc;
            c[i][j]=(cc=='Z');
        }
    }
    memset(ans,-1,sizeof(ans));
    for(int i=1;i<=n;i++){
        cnt=0;
        memset(vis,-1,sizeof(vis));
        memset(check,0,sizeof(check));
        for(int j=1;j<=m;j++){
            if(dfs(i,j,0)) ans[i][j]=(ans[i][j]==-1?2*cnt:min(ans[i][j],2*cnt));
            else break;
        }
    }
    for(int i=1;i<=n;i++){
        cnt=0;
        memset(vis,-1,sizeof(vis));
        memset(check,0,sizeof(check));
        for(int j=m;j>=1;j--){
            if(dfs(i,j,1)) ans[i][j]=(ans[i][j]==-1?2*cnt:min(ans[i][j],2*cnt));
            else break;
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++) cout << ans[i][j] << " \n"[j==m];
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
