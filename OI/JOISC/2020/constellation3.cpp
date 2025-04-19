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
#define piii pair<pii,int>
#define mpp make_pair
#define fi first
#define se second
const int inf=1e18;
const int mod=1e9+7;
const int maxn=100005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=500005;
const int maxl=18;
const int maxa=250000;
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
namespace BIT{
    int n;
    vector<int> bit;
    void init(int N){
        n=N;
        bit.assign(n+1,0);
    }
    int query(int x){
        int res=0;
        for(int i=x;i>=1;i-=(i&(-i))) res+=bit[i];
        return res;
    }
    void update(int x,int val){
        for(int i=x;i<=n;i+=(i&(-i))) bit[i]+=val;
    }
    void update_range(int l,int r,int val){
        update(l,val);update(r+1,-val);
    }
}
void solve(){
    int n;cin >> n;
    vector<vector<int>> edge(n+1),par(n+1,vector<int>(maxl,0));
    vector<int> dep(n+1,0),L(n+1),R(n+1);
    int pos=0;
    vector<int> a(n+1),v;
    for(int i=1;i<=n;i++){
        int lst=-1;cin >> a[i];
        while(!v.empty() && a[v.back()]<a[i]) lst=v.back(),v.pop_back();
        if(!v.empty()) par[i][0]=v.back();
        if(lst!=-1) par[lst][0]=i;
        v.push_back(i);
    }
    int rt=-1;
    for(int i=1;i<=n;i++){
        if(par[i][0]==0) rt=i;
        else edge[par[i][0]].push_back(i);
    }
    function<void(int)> dfs = [&](int u){
        dep[u]=dep[par[u][0]]+1;L[u]=++pos;
        for(int i=1;i<maxl;i++) par[u][i]=par[par[u][i-1]][i-1];
        for(int v:edge[u]) dfs(v);
        R[u]=pos;
    };
    dfs(rt);
    BIT::init(n);
    auto jmp = [=](int x,int y){
        for(int i=maxl-1;i>=0;i--){
            int p=par[x][i];
            if(p==0) continue;
            else if(y>a[p]) x=p;
        }
        return x;
    };
    int m,sum=0;cin >> m;
    vector<vector<pii>> star(n+1);
    for(int i=1;i<=m;i++){
        int x,y,c;cin >> x >> y >> c;y=jmp(x,y);
        star[y].push_back({x,c});sum+=c;
        //cout << x << ' ' << y << ' ' << c << '\n';
    }
    vector<int> dp(n+1,0);
    function<void(int)> dfs2 = [&](int u){
        int xx=0;
        for(int v:edge[u]) xx^=v,dfs2(v),dp[u]+=dp[v];
        for(int v:edge[u]) if(xx!=v) BIT::update_range(L[v],R[v],dp[xx^v]);
        for(auto &[v,c]:star[u]){
            int cur=c+BIT::query(L[v]);
            for(int w:edge[v]) cur+=dp[w];
            dp[u]=max(dp[u],cur);
        }
    };
    dfs2(rt);
    cout << sum-dp[rt] << '\n';
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
