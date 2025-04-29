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
const int mod=998244353;
const int maxn=200005;
const int bl=650;
const int maxs=655;
const int maxm=1000005;
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

struct flowedge{
    int u,v,cap,flow=0;
    flowedge(int u=-1,int v=-1,int cap=-1):u(u),v(v),cap(cap){}
};
namespace Maxflow{
    int flow_inf=1e9;
    int n,s,t,m=0;
    flowedge edge[maxm];
    int level[maxn],ptr[maxn];
    vector<int> adj[maxn];
    queue<int> q;
    void add_edge(int u,int v,int cap){
        adj[u].push_back(m);
        adj[v].push_back(m+1);
        edge[m]=flowedge(u,v,cap);
        edge[m+1]=flowedge(v,u,0);
        m+=2;
    }
    void reset(){
        m=0;
        for(int i=0;i<=n;i++) adj[i].clear();
    }
    bool bfs(){
        for(int i=0;i<=n;i++) level[i]=-1;
        level[s]=0;q.push(s);
        while(!q.empty()){
            int u=q.front();q.pop();
            for(int id:adj[u]){
                int v=edge[id].v;
                if((edge[id].cap-edge[id].flow)<1) continue;
                if(level[v]==-1){
                    level[v]=level[u]+1;q.push(v);
                }
            }
        }
        return level[t]!=-1;
    }
    int dfs(int u,int pushed){
        if(pushed==0) return 0;
        if(u==t) return pushed;
        for(int& tid=ptr[u];tid<(int)adj[u].size();tid++){
            int id=adj[u][tid];
            int v=edge[id].v;
            if(level[v]!=(level[u]+1)) continue;
            if((edge[id].cap-edge[id].flow)<1) continue;
            int cur=dfs(v,min(pushed,edge[id].cap-edge[id].flow));
            if(cur==0) continue;
            edge[id].flow+=cur;
            edge[id^1].flow-=cur;
            return cur;
        }
        return 0;
    }
    int flow(){
        int f=0;
        while(bfs()){
            for(int i=0;i<=n;i++) ptr[i]=0;
            while(int pushed=dfs(s,flow_inf)) f+=pushed;
        }
        return f;
    }
};

int par[maxn],lst[maxn];

int findpar(int u){
    if(u!=par[u]) return par[u]=findpar(par[u]);
    return u;
}

void unions(int u,int v){
    u=findpar(u);v=findpar(v);
    if(u==v) return;
    par[v]=u;lst[u]=lst[v];
}

vector<int> edge[maxn],adj[maxn];
bool vis[maxn];

void solve(){
    int n;cin >> n;
    Maxflow::s=0;Maxflow::t=Maxflow::n=2*n+1;
    for(int i=1;i<=n;i++){
        par[i]=lst[i]=i;
        Maxflow::add_edge(0,i,1);
        Maxflow::add_edge(n+i,2*n+1,1);
    }
    for(int i=1;i<n;i++){
        int u,v;cin >> u >> v;
        Maxflow::add_edge(u,v+n,1);
        edge[u].push_back(v);
    }
    Maxflow::flow();
    for(int i=0;i<Maxflow::m;i++){
        flowedge e=Maxflow::edge[i];
        if(e.u>0 && e.u<=n && e.v>n && e.v<=2*n && e.cap==1 && e.flow==1) unions(e.u,e.v-n);
    }
    for(int i=1;i<=n;i++) for(int v:edge[i]){
        if(findpar(i)!=findpar(v)) adj[findpar(i)].push_back(findpar(v));
    }
    vector<pii> ans;
    vector<int> order;
    function<void(int)> dfs = [&](int u){
        vis[u]=true;
        for(int v:adj[u]) if(!vis[v]) dfs(v);
        order.push_back(u);
    };
    for(int i=1;i<=n;i++) if(findpar(i)==i && !vis[i]) dfs(i);
    reverse(order.begin(),order.end());
    for(int i=0;i<(int)order.size()-1;i++) ans.push_back({lst[order[i]],par[order[i+1]]});
    cout << (int)ans.size() << '\n';
    for(pii x:ans) cout << x.fi << ' ' << x.se << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
