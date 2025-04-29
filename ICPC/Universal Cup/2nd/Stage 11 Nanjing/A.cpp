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
const int maxn=1005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=25;
const int maxa=1000;
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

int n,m;
bitset<maxn> bs[2*maxn][2*maxn];
char c[maxn][maxn];
bitset<maxn> cur;
bool vis[maxn][maxn];

int dx[]={0,0,1,-1},
    dy[]={1,-1,0,0};

void dfs(int x,int y,int i,int j){
    vis[x][y]=true;
    int a=maxa+x-i,b=maxa+y-j;
    cur|=bs[a][b];
    for(int t=0;t<4;t++){
        int xt=x+dx[t],yt=y+dy[t];
        if(xt<0 || yt<0 || xt>=n || yt>=m || c[xt][yt]=='O' || vis[xt][yt]) continue;
        dfs(xt,yt,i,j);
    }
}

void solve(){
    cin >> n >> m;
    for(int i=maxa-n;i<=maxa+n;i++) for(int j=maxa-m;j<=maxa+m;j++) bs[i][j].reset();
    for(int i=0;i<n;i++) for(int j=0;j<m;j++) cin >> c[i][j];
    int res=0;
    for(int i=0;i<n;i++) for(int j=0;j<m;j++){
        for(int p=-i-1;p<=n-i;p++) for(int q=-j-1;q<=m-j;q++){
            int x=i+p,y=j+q;
            if(x<0 || y<0 || x>=n || y>=m || c[x][y]=='O') bs[maxa+p][maxa+q].set(i*m+j);
        }
    }
    for(int i=0;i<n;i++) for(int j=0;j<m;j++){
        if(c[i][j]=='O') continue;
        for(int p=0;p<n;p++) for(int q=0;q<m;q++) vis[p][q]=false;
        cur.reset();
        dfs(i,j,i,j);
        if(cur.count()==n*m-1) res++;
    }
    cout << res << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}
