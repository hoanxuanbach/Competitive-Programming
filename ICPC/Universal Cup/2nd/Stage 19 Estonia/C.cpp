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
const int maxn=500005;
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
const int base=101;

/*
2
7 7
5 5 6 6 7 7
5 6 5 6 7 7
5 4
4 4 5 5
4 4 4
*/

bool check[maxn],vis[maxn];
vector<pii> edge[maxn];
char col[maxn];
int n,m,k,sz[maxn];

void dfs(int u){
    vis[u]=true;
    while(!edge[u].empty()){
        if(check[edge[u].back().se]) edge[u].pop_back();
        else{
            auto [v,id]=edge[u].back();
            edge[u].pop_back();check[id]=true;
            if(v<=k) col[v]=(u<=n?'R':'B');
            dfs(v);
        }
    }
}

void solve(){
    cin >> n >> m;k=n;
    for(int i=1;i<=n+m;i++) edge[i].clear();
    int pos=0;
    for(int i=1;i<=n;i++) sz[i]=0;
    for(int i=1;i<n;i++){
        int p;cin >> p;k=min(k,p-1);
        sz[i]^=(i<=k);sz[p]^=sz[i];
        if(sz[i]&1){
            edge[i].push_back({p,pos});
            edge[p].push_back({i,pos++});
        }
    }
    for(int i=1;i<=m;i++) sz[i]=0;
    for(int i=1;i<m;i++){
        int p;cin >> p;
        sz[i]^=(i<=k);sz[p]^=sz[i];
        int v=i+(i>k)*(n-k);p+=n-k;
        if(sz[i]&1){
            edge[v].push_back({p,pos});
            edge[p].push_back({v,pos++});
        }
    }
    int N=n+m-k;
    if(k&1){
        edge[n].push_back({N,pos});
        edge[N].push_back({n,pos++});
    }
    for(int i=1;i<=N;i++) vis[i]=false;
    for(int i=1;i<=N;i++) if(!vis[i]) dfs(i);
    for(int i=1;i<=k;i++) cout << col[i];
    cout << '\n';
    for(int i=0;i<pos;i++) check[i]=false;
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}
