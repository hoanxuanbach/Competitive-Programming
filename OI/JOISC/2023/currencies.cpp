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
#include<bits/stdc++.h>
using namespace std;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_real_distribution<> pp(0.0,1.0);
#define int long long
#define ld long double
#define pii pair<int,int>
#define piii pair<int,pii>
#define fi first
#define se second
const int inf=1e18;
const int mod=998244353;
const int mod2=1e9+7;
const int maxn=100005;
const int bl=650;
const int maxs=650;
const int maxm=200005;
const int maxq=500005;
const int maxl=20;
const int maxa=1000005;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
struct ask{
    int s,t,x,y,id;
};
namespace Segtree{
    int val[4*maxn],num[4*maxn];
    void pushdown(int id){
        val[id<<1]+=val[id];num[id<<1]+=num[id];
        val[id<<1|1]+=val[id];num[id<<1|1]+=num[id];
        val[id]=num[id]=0;
    }
    void update(int l,int r,int id,int tl,int tr,int x,int y){
        if(tr<l || r<tl) return;
        if(tl<=l && r<=tr){
            val[id]+=x;num[id]+=y;
            return;
        }
        pushdown(id);
        int mid=(l+r)>>1;
        update(l,mid,id<<1,tl,tr,x,y);update(mid+1,r,id<<1|1,tl,tr,x,y);
    }
    pii query(int l,int r,int id,int p){
        if(l==r) return {val[id],num[id]};
        pushdown(id);
        int mid=(l+r)>>1;
        if(p<=mid) return query(l,mid,id<<1,p);
        else return query(mid+1,r,id<<1|1,p);
    }
}
int n,m,q,L[maxn],R[maxn],res[maxn],a[maxn],b[maxn],pos,dep[maxn];
int parent[maxn][maxl];
vector<int> edge[maxn];
vector<ask> query[maxn];
vector<pii> cp;
void add(pii p,int t){
    Segtree::update(1,n,1,L[b[p.se]],R[b[p.se]],p.fi*t,t);
}
void dfs(int u,int par){
    //cout << u << ' ' << par << '\n';
    L[u]=++pos;parent[u][0]=par;dep[u]=dep[par]+1;
    for(int v:edge[u]){
        if(v==par) continue;
        dfs(v,u);
    }
    R[u]=pos;
}
int lca(int u,int v){
    if(dep[u]>dep[v]) swap(u,v);
    for(int i=0;i<=18;i++){
        if((dep[v]-dep[u])&(1<<i)) v=parent[v][i];
    }
    if(u==v) return u;
    for(int i=18;i>=0;i--){
        if(parent[u][i]!=parent[v][i]){
            u=parent[u][i];
            v=parent[v][i];
        }
    }
    return parent[u][0];
}
void build_tree(){
    dfs(1,0);
    for(int i=1;i<=18;i++){
        for(int j=1;j<=n;j++) parent[j][i]=parent[parent[j][i-1]][i-1];
    }
}
pii cal(int x,int y){
    int p=lca(x,y);
    //cout << x << ' ' << y << ' ' << p << '\n';
    pii fx=Segtree::query(1,n,1,L[x]),fy=Segtree::query(1,n,1,L[y]),fp=Segtree::query(1,n,1,L[p]);
    return {fx.fi+fy.fi-2*fp.fi,fx.se+fy.se-2*fp.se};
}
void dnc(int l,int r){
    int mid=(l+r)>>1,mid1=(l+mid-1)>>1,mid2=(mid+1+r)>>1;
    for(ask d:query[mid]){
        pii ans=cal(d.s,d.t);
        //cout << mid << ' ' << d.x << ' ' << d.y << '\n';
        if(ans.fi<=d.x){
            res[d.id]=ans.se;
            if(mid<r) query[mid2].push_back(d);
        }
        else if(l<mid) query[mid1].push_back(d);
    }
    if(l<mid){
        for(int i=mid;i>mid1;i--) add(cp[i],-1);
        dnc(l,mid-1);
        for(int i=mid1+1;i<=mid;i++) add(cp[i],1);
    }
    if(mid<r){
        for(int i=mid+1;i<=mid2;i++) add(cp[i],1);
        dnc(mid+1,r);
        for(int i=mid2;i>mid;i--) add(cp[i],-1);
    }
}
void solve(){
    cin >> n >> m >> q;
    for(int i=1;i<n;i++){
        cin >> a[i] >> b[i];
        edge[a[i]].push_back(b[i]);
        edge[b[i]].push_back(a[i]);
    }
    build_tree();
    for(int i=1;i<=m;i++){
        int p,c;cin >> p >> c;
        cp.push_back({c,p});
        if(L[a[p]]>L[b[p]]) swap(a[p],b[p]);
    }
    sort(cp.begin(),cp.end());
    int mid=(m-1)>>1;
    for(int i=1;i<=q;i++){
        res[i]=0;
        int s,t,x,y;cin >> s >> t >> y >> x;
        query[mid].push_back({s,t,x,y,i});
    }
    for(int i=0;i<=mid;i++) add(cp[i],1);
    dnc(0,m-1);
    for(int i=mid+1;i<m;i++) add(cp[i],1);
    for(ask d:query[mid]){
        pii ans=cal(d.s,d.t);
        res[d.id]=ans.se-res[d.id];
        if(res[d.id]>d.y) res[d.id]=-1;
        else res[d.id]=d.y-res[d.id];
    }
    for(int i=1;i<=q;i++) cout << res[i] << '\n';
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}