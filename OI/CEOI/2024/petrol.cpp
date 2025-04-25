#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int,int>
#define fi first
#define se second
const int maxn = 70005;

int n,K,T[maxn];
vector<pii> edge[maxn];

bool used[maxn];
int child[maxn],sz;
void dfs_sz(int u,int p){
    child[u]=1;
    for(auto [v,w]:edge[u]){
        if(v==p || used[v]) continue;
        dfs_sz(v,u);child[u]+=child[v];
    }
}
int findcen(int u,int p){
    for(auto [v,w]:edge[u]){
        if(v==p || used[v]) continue;
        if(child[v]>sz/2) return findcen(v,u);
    }
    return u;
}

int cnt[maxn],dd[maxn],f[maxn];
vector<int> cc,S;
void dfs(int u,int p,int a){
    cc.push_back(u);
    S.push_back(u);
    cnt[u]=0,f[u]=a;
    for(auto [v,w]:edge[u]){
        if(v==p || used[v]) continue;
        dd[v]=dd[u]+w;
        dfs(v,u,a);
    }
    if(dd[u]>K){
        int l=0,r=(int)cc.size()-1;
        while(l<r){
            int m=(l+r)>>1;
            if(dd[u]-dd[cc[m]]<=K) r=m;
            else l=m+1;
        }
        cnt[cc[l]]+=cnt[u]+1;
    }
    cc.pop_back();
}

int pre[maxn];
vector<pii> g[maxn],cur;

int query(vector<pii> &cur,int d){
    int pos=lower_bound(cur.begin(),cur.end(),make_pair(d,0LL))-cur.begin();
    return (pos?cur[pos-1].se:0);
}
void dfs2(int u,int p,int a,int val){
    cnt[u]=query(g[a],dd[u])-query(g[a],dd[p])+query(cur,dd[u]-K)-query(cur,dd[p]-K);
    //cout << u << ' ' << cnt[u] << ' ' << val << '\n';
    T[p]+=cnt[u]*child[u]*val;
    pre[u]=pre[p]+cnt[u];
    cur.push_back({dd[p],pre[u]});
    for(auto [v,w]:edge[u]){
        if(v==p || used[v]) continue;
        dfs2(v,u,a,val);
    }
    cur.pop_back();
}

void get(int u,int X){
    //cout << "get " << u << ' ' << X << '\n';
    sort(g[u].begin(),g[u].end());
    for(int i=1;i<(int)g[u].size();i++) g[u][i].se+=g[u][i-1].se;
    pre[X]=cnt[X]=0;
    if(u!=X) dfs2(u,X,u,-1);
    else{
        for(auto [v,w]:edge[u]){
            if(used[v]) continue;
            dfs2(v,X,u,1);
        }
    }
}

void decompose(int u){
    dfs_sz(u,0);sz=child[u];
    u=findcen(u,0);dfs_sz(u,0);
    //cout << '*' << u << '\n';
    S.clear();g[u].clear();
    dd[u]=cnt[u]=0;f[u]=u;
    for(auto [v,w]:edge[u]){
        if(used[v]) continue;
        dd[v]=dd[u]+w;
        g[v].clear();
        dfs(v,u,v);
    }
    g[u].push_back({K,1});
    for(int v:S){
        T[v]+=cnt[v]*(sz-child[f[v]]);
        //cout << v << ' ' << cnt[v] << ' ' << sz-child[f[v]] << '\n';
        if(dd[v]<=K){
            g[u].push_back({K-dd[v],cnt[v]+1});
            g[f[v]].push_back({K-dd[v],cnt[v]+1});
        }
    }
    get(u,u);
    for(auto [v,w]:edge[u]){
        if(used[v]) continue;
        get(v,u);
    }
    used[u]=true;
    for(auto [v,w]:edge[u]) if(!used[v]) decompose(v);
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> K;
    for(int i=1;i<n;i++){
        int u,v,w;cin >> u >> v >> w;
        u++;v++;
        edge[u].push_back({v,w});
        edge[v].push_back({u,w});
    }
    decompose(1);
    for(int i=1;i<=n;i++) cout << T[i] << '\n';
}
