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
#define ld long double
#define pii pair<int,int>
#define piii pair<int,pii>
#define mpp make_pair
#define fi first
#define se second
const int mod=998244353;
const int maxn=3005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=20;
const int maxa=1000000;
const int root=3;
const int base=101;

vector<pii> edge[maxn];
int n,k,q,rt[maxn],a[maxn],dist[maxn];
int res[maxn][maxn];


void solve(){
    cin >> n >> k >> q;
    for(int i=1;i<=n;i++) cin >> a[i];
    rt[n]=n+1;
    for(int i=n-1;i>=1;i--){
        if(i&1) edge[a[i]].push_back({a[i+1],i});
        else edge[a[i+1]].push_back({a[i],i});
        priority_queue<pii,vector<pii>,greater<pii>> pq;
        for(int u=1;u<=k;u++) dist[u]=n;
        rt[i]=n+1;dist[a[i]]=0;pq.push({0,a[i]});
        while(!pq.empty()){
            auto [d,u]=pq.top();pq.pop();
            if(d>rt[i]) break;
            if(d!=dist[u]) continue;
            for(auto [v,w]:edge[u]){
                int nxt=max(d,w);
                if(nxt<dist[v]){
                    dist[v]=nxt;
                    pq.push({nxt,v});
                }
                else if(v==a[i]) rt[i]=min(rt[i],nxt+1);
            }
        }
    }
    for(int i=1;i<=n;i++){
        res[i][i]=rt[i];
        for(int j=i+1;j<=n;j++) res[i][j]=min(res[i][j-1],rt[j]);
    }
    for(int i=1;i<=q;i++){
        int x,y;cin >> x >> y;
        cout << (res[x][y]<=y?"NO\n":"YES\n");
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}