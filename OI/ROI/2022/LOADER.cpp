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
#define piii pair<pii,int>
#define mpp make_pair
#define fi first
#define se second
const int mod=998244353;
const int maxn=500005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=20;
const int maxa=1000000;
const int root=3;
const int base=101;

int cnt;
vector<int> adj[2*maxn];
bool vis[2*maxn];
vector<pii> st,nedge[maxn];
map<int,int> mp[maxn];

void add_edge(int u,int v,int w){
    nedge[u].push_back({v,w});
    nedge[v].push_back({u,w});
}

int dist[maxn];
int n,m,low[maxn],num[maxn],pos;
vector<int> edge[maxn];

void init(){
    pos=cnt=0;st.clear();
    for(int i=1;i<=n;i++){
        mp[i].clear();
        nedge[i].clear();
        edge[i].clear();
        low[i]=num[i]=0;
        dist[i]=-1;
    }
    for(int i=1;i<=n+m;i++){
        vis[i]=false;
        adj[i].clear();
    }
}

void dfs(int u,int par){
    low[u]=num[u]=++pos;
    for(int v:edge[u]){
        if(v==par) continue;
        if(!num[v]){
            st.push_back({u,v});
            dfs(v,u);
            low[u]=min(low[u],low[v]);
            if(low[v]>=num[u]){
                cnt++;
                while(st.back().fi!=u || st.back().se!=v){
                    add_edge(st.back().fi,st.back().se,cnt);
                    st.pop_back();
                }
                add_edge(st.back().fi,st.back().se,cnt);
                st.pop_back();
            }
        }
        else{
            low[u]=min(low[u],num[v]);
            if(num[v]<num[u]) st.push_back({u,v});
        }
    }
}

void solve(){
    cin >> n >> m;
    init();
    for(int i=1;i<=m;i++){
        int u,v;cin >> u >> v;
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    dfs(1,0);
    cnt=0;
    for(int i=1;i<=n;i++){
        for(auto [v,w]:nedge[i]){
            if(mp[i].find(w)==mp[i].end()) mp[i][w]=++cnt;
            int id=mp[i][w];
            adj[id].push_back(v);
        }
    }
    for(int i=1;i<=n;i++){
        for(auto &[v,w]:nedge[i]) w=mp[v][w];
    }

    queue<int> q;
    q.push(1);dist[1]=0;
    while(!q.empty()){
        int u=q.front();q.pop();
        for(auto [x,id]:nedge[u]){
            if(vis[id]) continue;
            vis[id]=true;
            for(int v:adj[id]){
                if(dist[v]==-1){
                    dist[v]=dist[u]+2;
                    q.push(v);
                }
            }
        }
    }
    for(int i=2;i<=n;i++) cout << dist[i] << ' ';
    cout << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}
