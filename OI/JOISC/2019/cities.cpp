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
const int maxn=200005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=500005;
const int maxl=20;
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
struct ed{
    int u,c,d;
};
vector<ed> edge[maxn];
pii mx[maxn];
int dd[maxn],ans[maxn];
void solve(){
    int n;cin >> n;
    for(int i=1;i<n;i++){
        int u,v,c,d;cin >> u >> v >> c >> d;
        edge[u].push_back({v,c,d});
        edge[v].push_back({u,d,c});
    }
    int sum=0,Max=0,su=-1,sv=-1;
    function<void(int,int)> dfs = [&](int u,int p){
        ans[1]=max(ans[1],dd[u]);
        pii cur={0,u};
        for(auto &[v,c,d]:edge[u]){
            if(v==p) continue;
            dd[v]=dd[u]+c-d,sum+=c;dfs(v,u);
            if(cur.fi+c+mx[v].fi+dd[u]>Max){
                Max=cur.fi+c+mx[v].fi+dd[u];
                su=cur.se;sv=mx[v].se;
            }
            cur=max(cur,{mx[v].fi+c,mx[v].se});
        }
        mx[u]=cur;
    };
    dfs(1,0);
    ans[1]=sum-ans[1];sum=0;
    vector<vector<int>> w(n+1);
    function<void(int,int)> dfs2 = [&](int u,int p){
        w[u].push_back(0);
        for(auto &[v,c,d]:edge[u]){
            if(v==p) continue;
            dfs2(v,u);w[v].back()+=c;sum+=c;
            if((int)w[v].size()>(int)w[u].size()) swap(w[u],w[v]);
            if(w[u].back()>w[v].back()) swap(w[u].back(),w[v].back());
            for(int x:w[v]) w[u].push_back(x);
        }
    };
    dfs2(su,0);
    sort(w[su].begin(),w[su].end(),greater<int>());
    for(int i=2;i<=n;i++) ans[i]=(i==2?sum:ans[i-1])-w[su][i-2];
    int q;cin >> q;
    for(int i=1;i<=q;i++){
        int x;cin >> x;
        cout << ans[x] << '\n';
    }
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
