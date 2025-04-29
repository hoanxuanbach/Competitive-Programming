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
const int maxn=1005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=20;
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

struct flowedge{
    int u,v,cap,flow=0;
    flowedge(int u=-1,int v=-1,int cap=-1):u(u),v(v),cap(cap){}
};
namespace Maxflow{
    int flow_inf=1e9;
    int n,s,t,m=0;
    flowedge edge[maxm];
    int level[4*maxn],ptr[4*maxn];
    vector<int> adj[4*maxn];
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

int dx[]={0,0,1,-1},
    dy[]={1,-1,0,0};

char c[maxn][maxn];
int num[maxn][maxn],cnt,p[2*maxn],Max=1000000;
vector<pii> edge[2*maxn];
bool check[2*maxn][2*maxn];
int vis[2*maxn][2],col[2*maxn];

void dfs(int u,int a,int t){
    vis[u][t]=1;
    if(!t) check[a][u]=true;
    for(auto [v,w]:edge[u]){
        if(!(w^t)) continue;
        if(!vis[v][w]) dfs(v,a,w);
    }
}

void solve(){
    int n,m;cin>> n >> m;
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++){
        cin >> c[i][j];
        if(c[i][j]=='.'){
            num[i][j]=++cnt;
            col[cnt]=(i+j)&1;
        }
    }
    int res=cnt/2*(cnt/2-1);
    if(res>=Max){
        cout << Max << '\n';
        return;
    }
    Maxflow::n=Maxflow::t=cnt+1;Maxflow::s=0;
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++){
        if(!num[i][j]) continue;
        if((i+j)&1){
            Maxflow::add_edge(0,num[i][j],1);
            for(int t=0;t<4;t++){
                int xt=i+dx[t],yt=j+dy[t];
                if(xt<=0 || yt<=0 || xt>n || yt>m || !num[xt][yt]) continue;
                Maxflow::add_edge(num[i][j],num[xt][yt],1);
            }
        }
        else{
            Maxflow::add_edge(num[i][j],cnt+1,1);
        }
    }
    Maxflow::flow();
    for(int i=1;i<=cnt;i++){
        for(int id:Maxflow::adj[i]){
            flowedge e=Maxflow::edge[id];
            if(e.v<=cnt && e.v>=1 && e.cap==1){
                edge[e.u].push_back({e.v,e.flow});
                edge[e.v].push_back({e.u,e.flow});
                if(e.flow){
                    p[e.u]=e.v;
                    p[e.v]=e.u;
                }
                //cout << e.u << ' ' << e.v << ' ' << e.flow << '\n';
            }
        }
    }
    for(int i=1;i<=cnt;i++){
        memset(vis,0,sizeof(vis));
        dfs(i,i,1);
    }
    for(int i=1;i<=cnt;i++){
        for(int j=i+1;j<=cnt;j++){
            if(p[i]==j || col[i]==col[j]) continue;
            //cout << i << ' ' << j << ' ' << p[i] << ' ' << p[j] << ' ' << check[p[i]][p[j]] << '\n';
            res+=!check[p[i]][p[j]];
        }
    }
    cout << min(res,Max) << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
