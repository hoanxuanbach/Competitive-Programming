#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = array<ll,2>;
const ll inf = 1e18;
const int maxn = 2e5+5;
const int maxT = 520005;

struct path{
    int v[2];
    ll d[2];
};

struct node{
    vector<int> V;
    vector<path> P;
    vector<array<ll,3>> Tree;
    vector<ll> dist;
}T[maxT];

int n,m,q;
vector<array<ll,3>> S;

int f[maxn],par[maxn];
bool vis[maxn],use[maxn];
vector<pii> edge[maxn];
pii dp[maxn],dp2[maxn],g[maxn];
ll val[maxn];

vector<array<ll,3>> nTree;
pii dfs(int u,int p){
    vis[u]=1,par[u]=p;
    dp[u]={inf,0};

    vector<pii> cur;
    for(auto &[v,w]:edge[u]){
        if(v==p) continue;
        pii cc=dfs(v,u);
        if(cc[0]) cur.push_back({cc[0],cc[1]+w});
        dp[u]=min(dp[u],{dp[v][0]+w,dp[v][1]});
    }
    if(use[u] || (int)cur.size()>1){
        //cout << "dfs " << u << '\n';
        use[u]=true;
        for(auto &[v,w]:cur) nTree.push_back({u,v,w});
        dp[u]={0,u};
        cur={{u,0}};
    }
    if(cur.empty()) return {0,inf};
    else return cur[0];
}
void dfs2(int u,int p){
    vis[u]=false;
    if(use[u]) dp2[u]={0,u};
    //cout << "dfs2 " << u << ' ' << p << ' ' << dp2[u][0] << ' ' << dp2[u][1] << '\n';
    vector<array<ll,3>> cur;
    for(auto [v,w]:edge[u]) if(v!=p) cur.push_back({dp[v][0]+w,dp[v][1],v});
    sort(cur.begin(),cur.end());
    if((int)cur.size()>2) cur.resize(2);

    for(auto &[v,w]:edge[u]) if(v!=p){
        dp2[v]=min(dp2[v],{dp2[u][0]+w,dp2[u][1]});
        for(auto &[d,f,x]:cur) if(x!=v) dp2[v]=min(dp2[v],{d+w,f});
        dfs2(v,u);
    }
}
void dfs3(int u,int p){
    for(auto &[v,w]:edge[u]) if(v!=p && !g[v][0]){
        g[v]={g[u][0],g[u][1]+w};
        dfs3(v,u);
    }
}
void dfs4(int u,int p){
    vis[u]=1;
    for(auto &[v,w]:edge[u]) if(v!=p){
        dfs4(v,u);
        val[u]=max(val[u],val[v]-w);
    }
}
void dfs5(int u,int p){
    for(auto &[v,w]:edge[u]) if(v!=p){
        val[v]=max(val[v],val[u]-w);
        dfs5(v,u);
    }
}

void build(int l,int r,int id,vector<array<int,5>> E){

    vector<int> nV;nTree.clear();
    {
        for(auto &[u,v,w]:T[id].Tree){
            edge[u].push_back({v,w});
            edge[v].push_back({u,w});
        }
        for(auto &x:E) use[x[2]]=use[x[3]]=true;
        for(int i=l;i<r;i++) use[S[i][0]]=true;
        for(int &u:T[id].V) if(!vis[u]) dfs(u,0);
        for(int &u:T[id].V){
            dp2[u]={inf,0};
            if(use[u]) g[u]={u,0};
            else g[u]={0,inf};
        }
        for(auto &[u,v,w]:nTree) for(int j=v;j!=u;j=par[j]) g[j]={j,0};
        for(int &u:T[id].V) if(vis[u]) dfs2(u,0);
        for(int &u:T[id].V) if(g[u][0]) dfs3(u,0);
        for(int &u:T[id].V){
            if(use[u]) nV.push_back(u);
            if(!g[u][0]) T[id].P.push_back({{0,0},{inf,inf}});
            else{
                int x=g[u][0];
                ll d=g[u][1];
                T[id].P.push_back({{(int)dp[x][1],(int)dp2[x][1]},{d+dp[x][0],d+dp2[x][0]}});
            }
        }
        /*
        cout << "start " << l << ' ' << r << ' ' << id << '\n';
        cout << "nTree\n";
        for(auto &[u,v,w]:nTree) cout << u << ' ' << v << ' ' << w << '\n';
        cout << "end\n";
        */
        for(int &u:T[id].V){
            //cout << u << ' ' << g[u][0] << ' ' << g[u][1] << ' ' << dp[u][0] << ' ' << dp[u][1] << ' ' << dp2[u][0] << ' ' << dp2[u][1] << '\n';
            vis[u]=use[u]=false;
            dp[u]=dp2[u]={inf,0};
            g[u]={0,inf};
            edge[u].clear();
        }
    }
    vector<ll> mx;
    int sz=(int)nV.size();
    if(l+1==r) mx.push_back(S[l][1]);
    else{
        int m=(l+r)>>1;
        T[id<<1].V=T[id<<1|1].V=nV;
        T[id<<1].Tree=T[id<<1|1].Tree=nTree;
        vector<array<int,5>> lt,rt;
        for(auto &[L,R,u,v,w]:E){
            if(L<=l && m<=R) T[id<<1].Tree.push_back({u,v,w});
            else if(L<m) lt.push_back({L,R,u,v,w});
            if(L<=m && r<=R) T[id<<1|1].Tree.push_back({u,v,w});
            else if(m<R) rt.push_back({L,R,u,v,w});
        }
        build(l,m,id<<1,lt);
        build(m,r,id<<1|1,rt);
        mx.assign(sz,0);
        for(int i=0;i<sz;i++) mx[i]=max(T[id<<1].dist[i],T[id<<1|1].dist[i]);
    }
    for(int i=0;i<sz;i++) f[nV[i]]=i;
    for(int &u:T[id].V) val[u]=-inf;
    for(int i=0;i<(int)T[id].V.size();i++){
        int u=T[id].V[i];
        if(f[u]!=-1){
            val[u]=mx[f[u]];
            //cout << "val " << u << ' ' << mx[f[u]] << '\n';
        }
        else{
            for(int t=0;t<2;t++){
                int v=T[id].P[i].v[t];
                ll d=T[id].P[i].d[t];
                if(!v || d>=inf) continue;
                val[u]=max(val[u],mx[f[v]]-d);
                //cout << "val " << u << ' ' << v << ' ' << mx[v] << ' ' << d << '\n';
            }
        }
    }
    for(int i=0;i<sz;i++) f[nV[i]]=-1;
    for(auto &[u,v,w]:T[id].Tree){
        edge[u].push_back({v,w});
        edge[v].push_back({u,w});
    }
    for(int &u:T[id].V){
        if(!vis[u]){
            dfs4(u,0);
            dfs5(u,0);
        }
    }
    for(int &u:T[id].V){
        T[id].dist.push_back(val[u]);
        edge[u].clear();vis[u]=false;
    }
    /*
    cout << '*' << l << ' ' << r << ' ' << id << '\n';
    cout << "cur E:\n";
    for(auto [L,R,u,v,w]:E) cout << u << ' ' << v << ' ' << w << '\n';
    cout << "mx\n";
    for(int i=0;i<sz;i++) cout << mx[i] << ' ';
    cout << '\n';
    cout << "Vertices set:\n";
    for(int u:T[id].V) cout << u << ' ';
    cout << '\n';
    cout << "Dist\n";
    for(int d:T[id].dist) cout << d << ' ';
    cout << '\n';
    cout << "Edge\n";
    for(auto [u,v,w]:T[id].Tree) cout << u << ' ' << v << ' ' << w << '\n';
    cout << "Path\n";
    for(auto x:T[id].P) cout << x.v[0] << ' ' << x.d[0] << ' ' << x.v[1] << ' ' << x.d[1] << '\n';
    */
}

int query(int l,int r,int id,int x,map<int,ll> cc){
    if(x<=l) return 0;
    if(r<=x){
        bool ok=false;
        for(auto &[u,d]:cc){
            int p=lower_bound(T[id].V.begin(),T[id].V.end(),u)-T[id].V.begin();
            if(T[id].dist[p]>=d) ok=true;
        }
        //cout << "query " << l << ' ' << r << ' ' << ok << '\n';
        if(!ok) return 0;
        else if(l+1==r) return r;
    }
    int m=(l+r)>>1;
    map<int,ll> nc;
    for(auto &[u,d]:cc){
        int p=lower_bound(T[id].V.begin(),T[id].V.end(),u)-T[id].V.begin();
        auto A=T[id].P[p];
        for(int t=0;t<2;t++){
            if(!A.v[t] || A.d[t]>=inf) continue;
            int v=A.v[t];
            ll nd=d+A.d[t];
            //cout << "query " << x << ' ' << v << ' ' << nd << '\n';
            if(nc.find(v)!=nc.end()) nc[v]=min(nc[v],nd);
            else nc[v]=nd;
        }
    }
    int res=query(m,r,id<<1|1,x,nc);
    //cout << "query " << l << ' ' << r << '*' << res << '\n';
    return (res?res:query(l,m,id<<1,x,nc));
}

signed main(){
    //freopen("KOL.INP","r",stdin);
    //freopen("KOL.OUT","w",stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> m >> q;
    map<pii,pii> mp;
    for(int i=0;i<m;i++){
        int u,v,w;cin >> u >> v >> w;
        if(u>v) swap(u,v);
        mp[{u,v}]={0,w};
    }

    vector<array<int,5>> E;
    vector<pii> qq;

    for(int i=0;i<q;i++){
        int op;cin >> op;
        if(op==1){
            int u,v,w;cin >> u >> v >> w;
            if(u>v) swap(u,v);
            mp[{u,v}]={(int)S.size(),w};
        }
        else if(op==2){
            int u,v;cin >> u >> v;
            if(u>v) swap(u,v);
            auto it=mp.find({u,v});
            if(it->second[0]<(int)S.size()) E.push_back({(int)it->second[0],(int)S.size(),u,v,(int)it->second[1]});
            mp.erase(it);
        }
        else if(op==3){
            ll u,z,k;cin >> u >> z >> k;
            S.push_back({u,z,k});
        }
        else if(op==4){
            int u;cin >> u;
            qq.push_back({u,(int)S.size()});
        }
    }
    for(auto [p,x]:mp) if(x[0]<(int)S.size()) E.push_back({(int)x[0],(int)S.size(),(int)p[0],(int)p[1],(int)x[1]});
    T[1].V.assign(n,0);
    iota(T[1].V.begin(),T[1].V.end(),1);
    vector<array<int,5>> nE;
    for(auto [l,r,u,v,w]:E){
        //cout << l << ' ' << r << ' ' << u << ' ' << v << ' ' << w << '\n';
        if(l==0 && r==(int)S.size()) T[1].Tree.push_back({u,v,w});
        else nE.push_back({l,r,u,v,w});
    }
    memset(f,-1,sizeof(f));
    build(0,(int)S.size(),1,nE);

    for(auto [u,x]:qq){
        map<int,ll> cc;cc[u]=0;
        int p=query(0,(int)S.size(),1,x,cc);
        cout << (p?S[p-1][2]:0) << '\n';
    }
}
