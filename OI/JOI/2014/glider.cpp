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
const int maxn=100005;
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

int n,m,h[maxn],X;
vector<pii> edge[maxn];
int dist[maxn][3];

void solve(){
    cin >> n >> m >> X;
    for(int i=1;i<=n;i++) cin >> h[i];
    for(int i=1;i<=m;i++){
        int u,v,w;cin >> u >> v >> w;
        if(h[u]>=w) edge[u].push_back({v,w});
        if(h[v]>=w) edge[v].push_back({u,w});
    }
    for(int i=1;i<=n;i++) dist[i][0]=dist[i][1]=inf;
    dist[1][1]=0;
    priority_queue<piii,vector<piii>,greater<piii>> pq;
    pq.push({0,{1,1}});
    while(!pq.empty()){
        auto [d,u]=pq.top();pq.pop();
        auto [x,t]=u;
        if(dist[x][t]!=d) continue;
        int cur=(t?X-d:0);
        for(auto [v,w]:edge[x]){
            int nxt=cur-w;
            if(nxt<0){
                if(dist[v][0]>d+w-nxt) pq.push({dist[v][0]=d+w-nxt,{v,0}});
            }
            else{
                nxt=min(nxt,h[v]);
                if(dist[v][1]>d+cur-nxt) pq.push({dist[v][1]=d+cur-nxt,{v,1}});
            }
        }
    }
    int res=min({dist[n][0]+h[n],2*dist[n][1]+h[n]-X});
    cout << (res>=inf?-1:res) << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
