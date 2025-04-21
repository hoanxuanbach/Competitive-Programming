#include<bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
#define fi first
#define se second
const int maxn = 120005;

int n,k,res[2*maxn];
vector<pii> edge[maxn],qq[maxn];

int bit[2*maxn];
void update(int x,int val){
    for(int i=x;i<=n+k;i+=(i&(-i))) bit[i]+=val;
}
int get(int x){
    int ans=0;
    for(int i=x;i>=1;i-=(i&(-i))) ans+=bit[i];
    return ans;
}

bool used[maxn];
int child[maxn],sz;
void dfs_sz(int u,int p){
    child[u]=1;
    for(auto [v,w]:edge[u]){
        if(used[v] || v==p) continue;
        dfs_sz(v,u);child[u]+=child[v];
    }
}
int findcen(int u,int p){
    for(auto [v,w]:edge[u]){
        if(used[v] || v==p) continue;
        if(child[v]>sz/2) return findcen(v,u);
    }
    return u;
}

int f[maxn],d[maxn];
bool A[maxn],B[maxn];

vector<int> V;

void dfs(int u,int p){
    V.push_back(u);
    for(auto [v,w]:edge[u]){
        if(used[v] || v==p) continue;
        d[v]=w;f[v]=f[u];
        A[v]=A[u]&&(d[u]>d[v]);
        B[v]=B[u]&&(d[v]>d[u]);
        dfs(v,u);
    }
}

void decompose(int u){
    dfs_sz(u,0);sz=child[u];
    u=findcen(u,0);

    V.clear();
    f[u]=u;d[u]=0;
    A[u]=B[u]=true;
    V.push_back(u);
    for(auto [v,w]:edge[u]){
        if(used[v]) continue;
        f[v]=v;d[v]=w;
        A[v]=B[v]=true;
        dfs(v,u);
    }
    vector<pii> query,val;
    for(int v:V){
        if(v!=u && B[v]) val.push_back({d[f[v]],d[v]});
        for(auto [x,id]:qq[v]){
            if(x){
                if(f[v]!=f[x] && f[x]){
                    bool ok=A[v] && B[x];
                    if(v!=u && x!=u) ok&=d[f[v]]<d[f[x]];
                    if(v!=u) ok&=(d[f[v]]<id);
                    if(x!=u) ok&=(d[x]<id);
                    res[id]=ok-2;
                }
            }
            else{
                if(A[v] && d[f[v]]<id){
                    res[id]++;
                    query.push_back({d[f[v]],id});
                }
            }
        }
    }

    vector<pii> add;
    sort(val.begin(),val.end());
    sort(query.begin(),query.end());
    while(!query.empty()){
        auto [l,id]=query.back();query.pop_back();
        while(!val.empty() && val.back().fi>l){
            pii p=val.back();
            val.pop_back();
            add.push_back(p);
            update(p.se,1);
        }
        res[id]+=get(id);
    }
    for(auto p:add) update(p.se,-1);
    for(int v:V) f[v]=0;
    used[u]=true;
    for(auto [v,w]:edge[u]) if(!used[v]) decompose(v);
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> k;
    vector<int> pos;
    for(int i=1;i<n+k;i++){
        char op;cin >> op;
        if(op!='S') pos.push_back(i);
        if(op=='S'){
            int u,v;cin >> u >> v;
            edge[u].push_back({v,i});
            edge[v].push_back({u,i});
        }
        else if(op=='Q'){
            int u,v;cin >> u >> v;
            if(u==v) res[i]=-1;
            else qq[v].push_back({u,i});
        }
        else{
            int v;cin >> v;
            qq[v].push_back({0,i});
        }
    }
    decompose(1);
    for(int id:pos){
        if(res[id]==-2) cout << "no\n";
        else if(res[id]==-1) cout << "yes\n";
        else cout << res[id] << '\n';
    }
}