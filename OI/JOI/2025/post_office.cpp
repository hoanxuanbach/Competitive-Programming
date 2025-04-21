#include<bits/stdc++.h>
using namespace std;
const int inf = 1e9;
const int maxn = 2e5+5;
#define pii pair<int,int>

int n,m,P[maxn];
int cnt,vis[maxn];
bool root[maxn],cycle[maxn];
vector<int> edge[maxn],add[maxn];

int T,L[maxn],R[maxn],dep[maxn];

struct node{
    int s,t;
    node(int _s=0,int _t=0):s(_s),t(_t){}
};


node tree[40*maxn];
int lc[40*maxn],rc[40*maxn],f[maxn];

int merge(int l,int r,int x,int y){
    if(!x || !y) return x+y;
    if(l==r){
        tree[x].s+=tree[y].s;
        tree[x].t=(tree[x].s?tree[x].s:-inf);
        return x;
    }
    int mid=(l+r)>>1;
    int lt=merge(l,mid,lc[x],lc[y]);
    int rt=merge(mid+1,r,rc[x],rc[y]);
    lc[x]=lt,rc[x]=rt;

    tree[x].s=tree[lc[x]].s+tree[rc[x]].s;
    tree[x].t=max(tree[lc[x]].t+tree[rc[x]].s,tree[rc[x]].t+(mid-l+1));
    return x;
}

void update(int l,int r,int id,int x,int val){
    //if(l==1 && r==2*n) cout << "add " << x << ' ' << val << '\n';
    if(l==r){
        tree[id].s+=val;
        tree[id].t=(tree[id].s?tree[id].s:-inf);
        return;
    }
    int mid=(l+r)>>1;
    if(x<=mid){
        if(!lc[id]) lc[id]=++T;
        update(l,mid,lc[id],x,val);
    }
    else{
        if(!rc[id]) rc[id]=++T;
        update(mid+1,r,rc[id],x,val);
    }
    tree[id].s=tree[lc[id]].s+tree[rc[id]].s;
    tree[id].t=max(tree[lc[id]].t+tree[rc[id]].s,tree[rc[id]].t+(mid-l+1));
    //cout << "update " << l << ' ' << r << ' ' << id << ' ' << x << ' ' << val << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n;
    for(int i=1;i<=n;i++) cin >> P[i];

    vector<int> rt;
    for(int i=1;i<=n;i++){
        if(!vis[i]){
            vector<int> path;
            int u=i;
            while(!vis[u]){
                vis[u]=-1;
                path.push_back(u);
                u=P[u];
            }
            if(vis[u]==-1){
                rt.push_back(u);
                vis[u]=++cnt,root[u]=true;
                bool cur=false;
                for(int v:path){
                    if(v==u) cur=true;
                    cycle[v]=cur;
                }
            }
            for(int v:path) vis[v]=vis[u];
        }
    }
    //for(int i=1;i<=n;i++) cout << i << ' ' << vis[i] << ' ' << root[i] << ' ' << cycle[i] << '\n';
    for(int i=1;i<=n;i++) if(!root[i]) edge[P[i]].push_back(i);
    {
        function<void(int)> dfs = [&](int u){
            L[u]=++T;
            for(int v:edge[u]) dep[v]=dep[u]+1,dfs(v);
            R[u]=T;
        };
        for(int x:rt) dep[x]=1,dfs(x);
    }

    cin >> m;
    for(int i=1;i<=m;i++){
        int a,b;cin >> a >> b;
        if(vis[a]!=vis[b]){
            cout << -1 << '\n';
            return 0;
        }
        if(!cycle[b] && (L[a]<L[b] || R[b]<L[a])){
            cout << -1 << '\n';
            return 0;
        }
        if(L[b]<=L[a] && L[a]<=R[b]){
            add[a].push_back(dep[a]);
            add[b].push_back(-dep[a]);
            //out << "first " << a << ' ' << b << '\n';
        }
        else{
            add[a].push_back(dep[a]);
            int x=P[rt[vis[a]-1]];
            add[x].push_back(dep[a]+dep[x]);
            add[b].push_back(-(dep[a]+dep[x]));
            //cout << "second " << a << ' ' << b << '\n';
        }
    }

    int res=0;
    function<void(int)> dfs = [&](int u){
        f[u]=++T;tree[T]=tree[0];
        for(int v:edge[u]) dfs(v),f[u]=merge(1,2*n,f[u],f[v]);
        for(int d:add[u]) update(1,2*n,f[u],abs(d),(d>0?1:-1));
        //cout << '*' << u << ' ' << tree[f[u]].t << '\n';
        res=max(res,tree[f[u]].t-dep[u]+1);
    };
    
    T=0;
    tree[0]=node(0,-inf);
    for(int x:rt) dfs(x);
    cout << res << '\n';
}