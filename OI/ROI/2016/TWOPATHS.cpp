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
const int maxn=200005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=20;
const int maxa=1000000;
const int root=3;
const int base=101;

int par[maxn][maxl],dep[maxn],L[maxn],R[maxn],cn[maxn],pos;
vector<int> edge[maxn];

pii lca(int u,int v){
    if(dep[u]>dep[v]) swap(u,v);
    for(int i=0;i<18;i++){
        if((dep[v]-dep[u])&(1<<i)) v=par[v][i];
    }
    if(u==v) return {u,-1};
    for(int i=17;i>=0;i--){
        if(par[u][i]!=par[v][i]){
            u=par[u][i];
            v=par[v][i];
        }
    }
    return {u,v};
}

piii ans;
pii Min1[maxn],Min2[maxn];
void add(int u,pii a){
    if(a<Min1[u]){
        Min2[u]=Min1[u];
        Min1[u]=a;
    }
    else if(a<Min2[u]) Min2[u]=a;
}

void dfs(int u){
    L[u]=++pos;cn[pos]=u;
    for(int v:edge[u]){
        dfs(v);
        add(u,Min1[v]);
        add(u,Min2[v]);
    }
    R[u]=pos;
    if(Min2[u].fi<dep[u]) ans=max(ans,mpp(dep[u]-Min2[u].fi,mpp(Min1[u].se,Min2[u].se)));
}

int qu[maxn],qv[maxn],anc;
map<pii,vector<int>> mp;

set<pii> s[maxn];
vector<int> query[maxn];
vector<int> adj[maxn];

void add2(int u,pii x){
    auto it=s[u].lower_bound(x);
    x.fi=cn[x.fi];
    if(it!=s[u].end()){
        pii y=*it;y.fi=cn[y.fi];
        pii a=lca(x.fi,y.fi);
        if(a.se!=-1) a.fi=par[a.fi][0];
        int len=dep[a.fi]+dep[u]-2*dep[anc];
        //cout << u << ' ' << len << ' ' << x.fi << ' ' << y.fi << '\n';
        ans=max(ans,{len,{x.se,y.se}});
    }
    if(it!=s[u].begin()){
        it--;
        pii y=*it;y.fi=cn[y.fi];
        pii a=lca(x.fi,y.fi);
        if(a.se!=-1) a.fi=par[a.fi][0];
        int len=dep[a.fi]+dep[u]-2*dep[anc];
        //cout << u << ' ' << len << ' ' << x.fi << ' ' << y.fi << '\n';
        ans=max(ans,{len,{x.se,y.se}});
    }
    x.fi=L[x.fi];
    s[u].insert(x);
}

void dfs2(int u){
    //cout << '*' << u << '\n';
    for(int v:adj[u]){
        dfs2(v);
        if((int)s[u].size()<(int)s[v].size()) s[u].swap(s[v]);
        for(pii x:s[v]) add2(u,x);
    }
    for(int id:query[u]) add2(u,{L[qv[id]],id});
}

void cal(vector<int> d){
    vector<int> ver;
    for(int id:d){
        ver.push_back(qu[id]);
        query[qu[id]].push_back(id);
    }
    sort(ver.begin(),ver.end(),[](int u,int v){
        return L[u]<L[v];
    });
    int sz=(int)ver.size();
    for(int i=1;i<sz;i++){
        int u=ver[i-1],v=ver[i];
        pii a=lca(u,v);
        if(a.se!=-1) a.fi=par[a.fi][0];
        ver.push_back(a.fi);
    }
    sort(ver.begin(),ver.end(),[](int u,int v){
        return L[u]<L[v];
    });
    ver.erase(unique(ver.begin(),ver.end()),ver.end());
    vector<int> cur;
    for(int u:ver){
        //cout << u << ' ';
        while(!cur.empty() && R[cur.back()]<L[u]) cur.pop_back();
        if(!cur.empty()){
            adj[cur.back()].push_back(u);
        }
        cur.push_back(u);
    }
    //cout << '\n';
    int root=cur[0];
    dfs2(root);
    for(int u:ver){
        adj[u].clear();
        query[u].clear();
        s[u].clear();
    }
}

void solve(){
    int n,k;cin >> n >> k;
    for(int i=1;i<=n;i++) Min2[i]=Min1[i]={n,0};
    for(int i=2;i<=n;i++){
        cin >> par[i][0];
        edge[par[i][0]].push_back(i);
        dep[i]=dep[par[i][0]]+1;
        for(int j=1;j<18;j++) par[i][j]=par[par[i][j-1]][j-1];
    }
    ans={0,{1,2}};
    for(int i=1;i<=k;i++){
        cin >> qu[i] >> qv[i];
        if(dep[qu[i]]>dep[qv[i]]) swap(qu[i],qv[i]);
        pii a=lca(qu[i],qv[i]);
        if(a.se!=-1){
            if(a.fi>a.se) swap(a.fi,a.se),swap(qu[i],qv[i]);
            mp[{a.fi,a.se}].push_back(i);
            a.fi=par[a.fi][0];
        }
        a.fi=dep[a.fi];a.se=i;
        add(qu[i],a);add(qv[i],a);
    }
    dfs(1);
    for(auto [p,vid]:mp){
        anc=par[p.fi][0];
        //cout << '*' << p.fi << ' ' << p.se << '\n';
        cal(vid);
    }
    cout << ans.fi << '\n' << ans.se.fi << ' ' << ans.se.se << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
