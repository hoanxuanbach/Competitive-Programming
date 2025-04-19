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
//#define int long long
#define ld long double
#define pii pair<int,int>
#define piii pair<pii,int>
#define mpp make_pair
#define fi first
#define se second
//const int inf=1e18;
const int mod=1e9+7;
const int maxn=1000005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=500005;
const int maxl=20;
const int maxa=250000;
const int root=3;
/*
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
const int iroot=power(3,mod-2);
*/
const int base=101;
struct node;
struct DSU{
    int par[maxn],col[maxn],r[maxn],cnt;
    void init(int N){
        cnt=N;
        for(int i=1;i<=N;i++) par[i]=i,r[i]=1;
    }
    int findpar(int u){
        if(u!=par[u]){
            int p=findpar(par[u]);
            col[u]^=col[par[u]];
            return par[u]=p;
        }
        return u;
    }
    bool unions(int u,int v,int val){
        int pu=findpar(u),pv=findpar(v);
        val^=col[u]^col[v];
        if(pu==pv){
            if(val==0) return true;
            else return false;
        }
        if(r[pu]<r[pv]) swap(pu,pv);
        par[pv]=pu;r[pu]+=r[pv];
        col[pv]^=val;cnt--;
        return true;
    }
}dsu;
struct node{
    int x=0,d=0;
    node(int x=0,int d=0):x(x),d(d){}
    friend node operator+(node &a,node &b){
        a=a.update();b=b.update();
        if(a.x==0) return b;
        else if(b.x==0) return a;
        else if(a.x==b.x && a.d && b.d) return node(a.x,a.d|b.d);
        else return node(a.x,0);
    }
    node update(){
        int p=dsu.findpar(x);
        if(d==3 || d==0) return node(p,d);
        else return node(p,((d-1)^dsu.col[x])+1);
    }
};
int ans=1;
namespace Segtree{
    node tree[4*maxn];
    void update(int l,int r,int id,int p,int x){
        if(l==r){
            tree[id]=node(x,1);
            return;
        }
        int mid=(l+r)>>1;
        if(p<=mid) update(l,mid,id<<1,p,x);
        else update(mid+1,r,id<<1|1,p,x);
        tree[id]=tree[id<<1]+tree[id<<1|1];
    }
    node add(node a,int x){
        if(a.d==3){ans=0;return a;}
        ans*=dsu.unions(a.x,x,(a.d-1)^1);
        return a.update();
    }
    void query(int l,int r,int id,int tl,int tr,int x){
        if(r<tl || tr<l || tree[id].x==0) return;
        if(tl<=l && r<=tr && tree[id].d){tree[id]=add(tree[id],x);return;}
        int mid=(l+r)>>1;
        query(l,mid,id<<1,tl,tr,x);query(mid+1,r,id<<1|1,tl,tr,x);
        tree[id]=tree[id<<1]+tree[id<<1|1];
    }
}
void solve(){
    int n;cin >> n;
    vector<int> cc(n);
    vector<pii> p(n);
    for(int i=0;i<n;i++){
        cin >> p[i].fi >> p[i].se;
        cc[i]=p[i].se;
    }
    sort(p.begin(),p.end());
    sort(cc.begin(),cc.end());
    dsu.init(n);
    for(int i=0;i<n;i++){
        int l=p[i].fi,r=p[i].se;
        l=lower_bound(cc.begin(),cc.end(),l)-cc.begin()+1;
        r=lower_bound(cc.begin(),cc.end(),r)-cc.begin()+1;
        Segtree::query(1,n,1,l,r,i+1);
        Segtree::update(1,n,1,r,i+1);
        if(ans==0){
            cout << 0 << '\n';
            return;
        }
    }
    /*
    for(int i=0;i<n;i++){
        for(int j=0;j<i;j++){
            if(p[j].fi<=p[i].fi && p[i].fi<=p[j].se && p[i].fi<=p[j].se && p[j].se<=p[i].se) ans*=dsu.unions(i+1,j+1,1);
        }
    }
    */
    for(int i=1;i<=dsu.cnt;i++) ans=ans*2%mod;
    cout << ans << '\n';
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
