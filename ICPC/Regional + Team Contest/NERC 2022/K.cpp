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
const int maxn=2005;
const int bl=650;
const int maxs=655;
const int maxm=20005;
const int maxq=1000005;
const int maxl=20;
const int maxa=1000000;
const int root=3;
const int base=101;

struct flowedge{
    int u,v,cap,flow=0;
    flowedge(int u=-1,int v=-1,int cap=-1):u(u),v(v),cap(cap){}
};
struct Maxflow{
    int n,s,t,m=0;
    flowedge edge[maxm];
    int level[maxn],ptr[maxn];
    vector<int> adj[maxn];
    queue<int> q;
    Maxflow(){n=s=t=-1;}
    Maxflow(int n,int s,int t):n(n),s(s),t(t){}
    void add_edge(int u,int v,int cap){
        adj[u].push_back(m);
        adj[v].push_back(m+1);
        edge[m]=flowedge(u,v,cap);
        edge[m+1]=flowedge(v,u,0);
        m+=2;
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
            while(int pushed=dfs(s,inf)) f+=pushed;
        }
        return f;
    }
}fl;

void solve(){
    int n,m;cin >> n >> m;
    int a,b;cin >> a >> b;
    fl.n=fl.t=2*n+1;fl.s=0;
    fl.add_edge(0,a,inf);
    fl.add_edge(a+n,2*n+1,inf);
    fl.add_edge(0,b+n,inf);
    fl.add_edge(b,2*n+1,inf);
    for(int i=1;i<=m;i++){
        int u,v,w;cin >> u >> v >> w;
        fl.add_edge(u,v+n,w);
        fl.add_edge(u+n,v,w);
        fl.add_edge(v,u+n,w);
        fl.add_edge(v+n,u,w);
    }
    int ans=fl.flow();
    string res;
    for(int i=1;i<=n;i++){
        int u1=fl.level[i]!=-1,u2=fl.level[i+n]!=-1;
        if(u1==u2) res+='C';
        else if(u1==1) res+='A';
        else res+='B';
    }
    cout << ans << '\n' << res << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
