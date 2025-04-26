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
const int maxn=200005;
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

int n,m;
vector<pii> construct(vector<pii> e){
    vector<vector<int>> edge(n+1);
    set<pii> ss;
    for(auto [u,v]:e){
        edge[u].push_back(v);
        edge[v].push_back(u);
        if(u>v) swap(u,v);
        ss.insert({u,v});
    }
    vector<pii> ans;
    vector<bool> vis(n+1);
    function<void(int,int)> dfs = [&](int u,int p){
        vis[u]=true;
        if(p>1){
            if(ss.find({1,u})==ss.end()){
                ans.push_back({1,u});
                ss.insert({1,u});
            }
            ans.push_back({-u,-p});
            ss.erase({min(u,p),max(u,p)});
        }
        for(int v:edge[u]) if(!vis[v]) dfs(v,u);
    };
    dfs(1,0);
    for(auto [x,y]:ss) if(x>1) ans.push_back({-x,-y});
    return ans;
}

void solve(){
    cin >> n >> m;
    vector<pii> e(m);
    for(int i=0;i<m;i++) cin >> e[i].fi >> e[i].se;
    vector<pii> ans=construct(e);
    cin >> m;
    e.assign(m,{0,0});
    for(int i=0;i<m;i++) cin >> e[i].fi >> e[i].se;
    vector<pii> ans2=construct(e);
    reverse(ans2.begin(),ans2.end());
    for(auto [x,y]:ans2) ans.push_back({-x,-y});
    cout << (int)ans.size() << '\n';
    for(auto [x,y]:ans){
        cout << (x<0?'-':'+') << ' ' << abs(x) << ' ' << abs(y) << '\n';
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}

