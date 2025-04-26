#include<bits/stdc++.h>
using namespace std;
#define int long long
#define maxl 60
#define maxn 100005
#define maxm 400005
struct node{
    int pos=-1,nxt[2];
    node(){memset(nxt,0,sizeof(nxt));}
};
struct flowedge{
    int u,v,cap,flow=0;
    flowedge(int u=-1,int v=-1,int cap=-1):u(u),v(v),cap(cap){}
};
namespace Trie{
    vector<node> T;
    void build(){
        T.clear();
        T.push_back(node());
    }
    void update(int x,int p){
        int u=0;
        for(int i=maxl;i>=0;i--){
            int b=(x>>i)&1;
            if(T[u].nxt[b]==0){
                T[u].nxt[b]=(int)T.size();
                T.push_back(node());
            }
            u=T[u].nxt[b];
        }
        T[u].pos=p;
    }
    int query(int x){
        int u=0;
        for(int i=maxl;i>=0;i--){
            int b=(x>>i)&1;
            if(T[u].nxt[b^1]!=0) u=T[u].nxt[b^1];
            else u=T[u].nxt[b];
        }
        return T[u].pos;
    }
}
namespace Maxflow{
    int n,m=0,s,t,flow_inf=1e18;
    vector<int> adj[maxn];
    int level[maxn],ptr[maxn];
    flowedge edge[maxm];
    void add_edge(int u,int v,int cap){
        edge[m]=flowedge(u,v,cap);
        edge[m+1]=flowedge(v,u,0);
        adj[u].push_back(m);
        adj[v].push_back(m+1);
        m+=2;
    }
    bool bfs(){
        for(int i=0;i<=n;i++) level[i]=-1;
        queue<int> q;q.push(s);level[s]=0;
        while(!q.empty()){
            int u=q.front();q.pop();
            for(int id:adj[u]){
                int v=edge[id].v;
                if(level[v]!=-1 || edge[id].cap-edge[id].flow<=0) continue;
                level[v]=level[u]+1;
                q.push(v);
            }
        }
        return level[t]!=-1;
    }
    int dfs(int u,int pushed){
        if(u==t || pushed==0) return pushed;
        for(int &cit=ptr[u];cit<(int)adj[u].size();cit++){
            int id=adj[u][cit];
            int v=edge[id].v;
            if(level[v]!=level[u]+1 || edge[id].cap-edge[id].flow<=0) continue;
            int fl=dfs(v,min(pushed,edge[id].cap-edge[id].flow));
            if(fl==0) continue;
            edge[id].flow+=fl;
            edge[id^1].flow-=fl;
            return fl;
        }
        return 0;
    }
    int flow(){
        int fl=0;
        while(bfs()){
            for(int i=0;i<=n;i++) ptr[i]=0;
            while(int pushed=dfs(s,flow_inf)) fl+=pushed;
        }
        return fl;
    }
}
int n,a[maxn],b[maxn],res[maxn];
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n;
    Maxflow::s=0;Maxflow::n=Maxflow::t=2*n+1;
    Trie::build();
    for(int i=1;i<=n;i++) cin >> a[i];
    for(int i=1;i<=n;i++){cin >> b[i];Trie::update(b[i],i);}
    for(int i=1;i<=n;i++){
        Maxflow::add_edge(0,i,1);
        int p=Trie::query(a[i]);
        Maxflow::add_edge(i,p+n,1);
    }
    Trie::build();
    for(int i=1;i<=n;i++) Trie::update(a[i],i);
    for(int i=1;i<=n;i++){
        Maxflow::add_edge(i+n,2*n+1,1);
        int p=Trie::query(b[i]);
        Maxflow::add_edge(p,i+n,1);
    }
    if(Maxflow::flow()!=n) cout << "NIE\n";
    else{
        cout << "TAK\n";
        for(int i=0;i<Maxflow::m;i++){
            flowedge ed=Maxflow::edge[i];
            if(ed.flow==1 && ed.cap==1 && ed.u!=0 && ed.v!=2*n+1) res[ed.u]=ed.v-n;
        }
        for(int i=1;i<=n;i++) cout << res[i] << ' ';
        cout << '\n';
    }
}
