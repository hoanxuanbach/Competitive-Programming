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
- insert(x)
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
#define fi first
#define se second
const int inf=1e18;
const int mod=998244353;
const int maxn=200005;
const int bl=650;
const int maxs=650;
const int maxm=200005;
const int maxq=500005;
const int maxl=20;
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
int par[maxn],cnt[maxn],c[maxn];
int findpar(int u){
    if(u!=par[u]) return par[u]=findpar(par[u]);
    return u;
}
void unions(int u,int v){
    u=findpar(u);v=findpar(v);
    if(u==v) return;
    if(cnt[u]<cnt[v]) swap(v,u);
    cnt[u]+=cnt[v];c[u]|=c[v];par[v]=u;
}
bool del[maxn];
vector<int> com;
vector<piii> p;
int n,m,l,sz,X[maxn],Y[maxn];
namespace Segtree{
    int tree[4*maxn];
    void reset(){
        for(int i=0;i<=4*sz;i++) tree[i]=0;
    }
    void update(int l,int r,int id,int pos,int val){
        tree[id]=val;
        if(l==r) return;
        int mid=(l+r)>>1;
        if(pos<=mid) update(l,mid,id<<1,pos,val);
        else update(mid+1,r,id<<1|1,pos,val);
    }
    void add(int x,int val){
        int pos=lower_bound(com.begin(),com.end(),x)-com.begin()+1;
        //cout << '*' << pos << ' ' << val << '\n';
        update(1,sz,1,pos,val);
    }
    int query(int l,int r,int id,int tl,int tr){
        if(tr<l || r<tl) return 0;
        if(tl<=l && r<=tr){
            if(!del[tree[id]]) return tree[id];
            else return 0;
        }
        int mid=(l+r)>>1;
        return max(query(l,mid,id<<1,tl,tr),query(mid+1,r,id<<1|1,tl,tr));
    }
    int query(int l,int r){
        l=lower_bound(com.begin(),com.end(),l)-com.begin()+1;
        r=upper_bound(com.begin(),com.end(),r)-com.begin();
        if(l<=r) return query(1,sz,1,l,r);
        else return 0;
    }
}
void solve(){
    cin >> n >> m >> l;
    for(int i=1;i<=m;i++){
        par[i]=i;cnt[i]=1;
        int x,y;cin >> x >> y;
        X[i]=x;Y[i]=y;
        p.push_back({x,{y,i}});
        if(x<=l) c[i]|=1;
        if(y<=l) c[i]|=2;
        if(x+l>=n) c[i]|=4;
        if(y+l>=n) c[i]|=8;
        com.push_back(y);
    }
    sort(com.begin(),com.end());
    com.erase(unique(com.begin(),com.end()),com.end());
    sz=(int)com.size();
    sort(p.begin(),p.end());
    int cur=0;
    for(int i=0;i<m;i++){
        while(cur<i && p[cur].fi<p[i].fi-l){del[cur+1]=true;cur++;}
        int pos1=Segtree::query(p[i].se.fi-l,p[i].se.fi);
        int pos2=Segtree::query(p[i].se.fi,p[i].se.fi+l);
        if(pos1!=0) unions(p[pos1-1].se.se,p[i].se.se);
        if(pos2!=0) unions(p[pos2-1].se.se,p[i].se.se);
        Segtree::add(p[i].se.fi,i+1);
    }
    Segtree::reset();
    cur=m-1;
    for(int i=0;i<=m;i++) del[i]=false;
    for(int i=m-1;i>=0;i--){
        while(cur>i && p[cur].fi>p[i].fi+l){del[m-cur]=true;cur--;}
        int pos1=Segtree::query(p[i].se.fi-l,p[i].se.fi);
        int pos2=Segtree::query(p[i].se.fi,p[i].se.fi+l);
        if(pos1!=0) unions(p[m-pos1].se.se,p[i].se.se);
        if(pos2!=0) unions(p[m-pos2].se.se,p[i].se.se);
        Segtree::add(p[i].se.fi,m-i);
    }
    vector<pii> ans;
    for(int i=1;i<=m;i++){
        int u=c[findpar(i)],d=__builtin_popcount(u);
        if(d>=3 || (d==2 && u!=9 && u!=6)) ans.push_back({X[i],Y[i]});
    }
    cout << (int)ans.size() << '\n';
    for(pii v:ans) cout << v.fi << ' ' << v.se << '\n';
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
