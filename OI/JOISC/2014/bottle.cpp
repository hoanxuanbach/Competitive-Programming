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
const int maxn=2005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=200005;
const int maxl=25;
const int maxa=1000000;
const int root=3;
const int base=131;

int dx[]={0,0,1,-1},
    dy[]={1,-1,0,0};

int n,m,p,q,res[maxq];
char c[maxn][maxn];
int f[maxn][maxn],d[maxn][maxn];

vector<piii> s[maxq];
int par[maxq];

int findpar(int u){
    if(u!=par[u]) return par[u]=findpar(par[u]);
    return u;
}
void unions(int u,int v,int w){
    u=findpar(u);v=findpar(v);
    if(u==v) return;
    if((int)s[u].size()<(int)s[v].size()) swap(u,v);
    for(auto [id,x]:s[v]){
        x.fi=findpar(x.fi);
        x.se=findpar(x.se);
        if(x.fi==x.se) continue;
        if(min(x.fi,x.se)==min(u,v) && max(x.fi,x.se)==max(u,v)) res[id]=w;
        else s[u].push_back({id,x});
    }
    par[v]=u;
}

void solve(){
    cin >> n >> m >> p >> q;
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) cin >> c[i][j];
    queue<pii> qq;
    for(int i=1;i<=p;i++){
        par[i]=i;
        int x,y;cin >> x >> y;
        f[x][y]=i;qq.push({x,y});
    }
    while(!qq.empty()){
        int x=qq.front().fi,y=qq.front().se;qq.pop();
        for(int t=0;t<4;t++){
            int xt=x+dx[t],yt=y+dy[t];
            if(xt<=0 || yt<=0 || xt>n || yt>m || f[xt][yt] || c[xt][yt]=='#') continue;
            d[xt][yt]=d[x][y]+1;
            f[xt][yt]=f[x][y];
            qq.push({xt,yt});
        }
    }
    vector<piii> e;
    for(int x=1;x<=n;x++) for(int y=1;y<=m;y++){
        if(!f[x][y]) continue;
        for(int t=0;t<4;t++){
            int xt=x+dx[t],yt=y+dy[t];
            if(xt<=0 || yt<=0 || xt>n || yt>m || !f[xt][yt] || f[xt][yt]==f[x][y]) continue;
            e.push_back({d[xt][yt]+d[x][y],{f[xt][yt],f[x][y]}});
        }
    }
    for(int i=1;i<=q;i++){
        int u,v;cin >> u >> v;res[i]=-1;
        s[u].push_back({i,{u,v}});
        s[v].push_back({i,{u,v}});
    }
    sort(e.begin(),e.end());
    for(auto x:e) unions(x.se.fi,x.se.se,x.fi);
    for(int i=1;i<=q;i++) cout << res[i] << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
