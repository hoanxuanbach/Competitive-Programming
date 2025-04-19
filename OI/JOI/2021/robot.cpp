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
#define mtp make_tuple
#define fi first
#define se second
const int inf=1e18;
const int mod=1e9+7;
const int maxn=100005;
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

void solve(){
    int n,m;cin >> n >> m;
    int cur=n;
    map<pii,int> mp;
    map<int,int> sum;
    vector<tuple<int,int,int,int>> e;
    for(int i=0;i<m;i++){
        int u,v,c,p;cin >> u >> v >> c >> p;
        e.push_back({u,v,c,p});
        if(mp[{u,c}]==0) mp[{u,c}]=++cur;
        if(mp[{v,c}]==0) mp[{v,c}]=++cur;
        int cu=mp[{u,c}],cv=mp[{v,c}];
        sum[cu]+=p;sum[cv]+=p;
    }
    vector<vector<pii>> edge(cur+1,vector<pii>());
    vector<int> dist(cur+1,inf);
    auto add = [&](int u,int v,int w){
        //cout << u << ' ' << v << ' ' << w << '\n';
        edge[u].emplace_back(v,w);
    };
    for(auto &[u,v,c,p]:e){
        int cu=mp[{u,c}],cv=mp[{v,c}];
        int su=sum[cu],sv=sum[cv];
        //cout << u << ' ' << v << ' ' << c << ' ' << p << ' ' << cu << ' ' << cv << ' ' << su << ' ' << sv << '\n';
        add(u,v,min(p,su-p));
        add(v,u,min(p,sv-p));
        add(u,cv,0);add(v,cu,0);
        add(cu,v,su-p);add(cv,u,sv-p);
    }
    //cout << cur << '\n';
    priority_queue<pii,vector<pii>,greater<pii>> pq;
    dist[1]=0;pq.push({0,1});
    while(!pq.empty()){
        auto [d,u]=pq.top();pq.pop();
        if(dist[u]!=d) continue;
        //cout << u << ' ' << d << '\n';
        if(u==n){
            cout << d << '\n';
            return;
        }
        for(auto &[v,w]:edge[u]){
            //cout << v << ' ' << d+w << ' ' << dist[v] << '\n';
            if(d+w<dist[v]){
                dist[v]=d+w;
                pq.push({d+w,v});
            }
        }
    }
    cout << -1 << '\n';
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}

