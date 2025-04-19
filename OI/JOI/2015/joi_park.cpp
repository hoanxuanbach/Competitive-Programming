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
const int maxn=200005;
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

int n,m,C,sum=0;
vector<pii> edge[maxn];
int dist[maxn];
bool vis[maxn];

void solve(){
    cin >> n >> m >> C;
    vector<piii> d;
    for(int i=1;i<=m;i++){
        int u,v,w;cin >> u >> v >> w;sum+=w;
        edge[u].push_back({v,w});
        edge[v].push_back({u,w});
    }

    for(int i=1;i<=n;i++) dist[i]=inf;
    priority_queue<pii,vector<pii>,greater<pii>> pq;
    pq.push({0,1});dist[1]=0;
    while(!pq.empty()){
        auto [d,u]=pq.top();pq.pop();
        if(dist[u]!=d) continue;
        for(auto [v,w]:edge[u]){
            if(dist[v]>d+w){
                dist[v]=d+w;
                pq.push({d+w,v});
            }
        }
    }
    vector<pii> X;
    for(int i=1;i<=n;i++) X.push_back({dist[i],i});
    sort(X.begin(),X.end());

    int res=inf;
    for(auto [d,u]:X){
        vis[u]=true;
        for(auto [v,w]:edge[u]) if(vis[v]) sum-=w;
        //cout << d << ' ' << u << ' ' << sum << '\n';
        res=min(res,d*C+sum);
    }
    cout << res << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
