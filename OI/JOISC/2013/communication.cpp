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
const int maxn=100005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=25;
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
const int base=131;

struct DSU{
    int par[3*maxn],sz[3*maxn],d[3*maxn],cnt;
    void init(int n,int N){
        for(int i=1;i<=N;i++){
            par[i]=i;sz[i]=1;
            d[i]=(i<=n);
        }
        cnt=n;
    }
    vector<pii> event;
    int findpar(int u){
        if(u!=par[u]) return findpar(par[u]);
        return u;
    }
    void unions(int u,int v){
        u=findpar(u);v=findpar(v);
        if(u==v){
            event.push_back({-1,-1});
            return;
        }
        if(sz[v]>sz[u]) swap(u,v);
        cnt-=(d[u] && d[v]);
        d[u]+=d[v];
        sz[u]+=sz[v];
        par[v]=u;
        event.push_back({u,v});
    }
    void roll_back(){
        auto [u,v]=event.back();
        event.pop_back();
        if(u==-1) return;
        par[v]=v;
        sz[u]-=sz[v];
        d[u]-=d[v];
        cnt+=(d[u] && d[v]);
    }

}dsu;

int n,m1,m2,q;
int y[3*maxn],res[maxn];
vector<int> c1,c2;
vector<pii> e1[maxn],e2[maxn];

void dnc(int l,int r,int L,int R){
    //cout << l << ' ' << r << ' ' << L << ' ' << R << endl;
    if(l>r) return;
    int mid=(l+r)>>1;
    for(int i=l;i<=mid;i++){
        for(auto [u,v]:e1[i]) dsu.unions(u,v);
    }
    int M=L;
    while(dsu.cnt>1){
        for(auto [u,v]:e2[++M]) dsu.unions(u,v);
    }
    res[mid]=M;
    for(int i=L+1;i<=M;i++) for(int j=0;j<(int)e2[i].size();j++) dsu.roll_back();
    dnc(mid+1,r,L,M);
    for(int i=l;i<=mid;i++) for(int j=0;j<(int)e1[i].size();j++) dsu.roll_back();
    for(int i=L+1;i<=M;i++) for(auto [u,v]:e2[i]) dsu.unions(u,v);
    dnc(l,mid-1,M,R);
    for(int i=L+1;i<=M;i++) for(int j=0;j<(int)e2[i].size();j++) dsu.roll_back();
}

void solve(){
    cin >> n >> m1 >> m2 >> q;
    c1.push_back(0);
    c2.push_back(0);
    for(int i=1;i<=m1;i++){
        int x;cin >> x >> y[n+i];
        c1.push_back(y[n+i]);
    }
    vector<pii> e;
    for(int i=1;i<n+m1;i++){
        int t,u,v;cin >> t >> u >> v;
        if(t==1) e.push_back({u,n+v});
        else e.push_back({n+u,n+v});
    }
    for(int i=1;i<=m2;i++){
        int x;cin >> x >> y[n+m1+i];
        y[n+m1+i]=-y[n+m1+i];
        c2.push_back(y[n+m1+i]);
    }
    for(int i=1;i<n+m2;i++){
        int t,u,v;cin >> t >> u >> v;
        if(t==1) e.push_back({u,n+m1+v});
        else e.push_back({n+m1+u,n+m1+v});
    }
    sort(c1.begin(),c1.end());
    sort(c2.begin(),c2.end());
    c1.erase(unique(c1.begin(),c1.end()),c1.end());
    c2.erase(unique(c2.begin(),c2.end()),c2.end());
    for(int i=1;i<=m1;i++) y[n+i]=lower_bound(c1.begin(),c1.end(),y[n+i])-c1.begin();
    for(int i=1;i<=m2;i++) y[n+m1+i]=lower_bound(c2.begin(),c2.end(),y[n+m1+i])-c2.begin();
    for(auto [u,v]:e){
        int d=max(u,v);
        if(y[u]<y[v]) swap(u,v);
        if(d<=n+m1) e1[y[u]].push_back({u,v});
        else e2[y[u]].push_back({u,v});
        //cout << u << ' ' << v << ' ' << y[u] << ' ' << y[v] << '\n';
    }
    dsu.init(n,n+m1+m2);
    dnc(0,(int)c1.size()-1,0,(int)c2.size()-1);
    for(int i=1;i<=q;i++){
        int a;cin >> a;
        int pos=upper_bound(c1.begin(),c1.end(),a)-c1.begin()-1;
        cout << -c2[res[pos]] << '\n';
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
