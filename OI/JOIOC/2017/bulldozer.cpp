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
#define piii pair<pii,int>
#define mpp make_pair
#define fi first
#define se second
const int inf=1e18;
const int mod=1e9+7;
const int maxn=2005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=500005;
const int maxl=20;
const int maxa=250000;
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
const int base=101;
struct point{
    int x,y,w;
    bool operator<(point o){
        if(x!=o.x) return x<o.x;
        else return y<o.y;
    }
}p[maxn];
struct line{
    int x,y,u,v;
    bool operator<(line o){
        if(y*o.x!=x*o.y) return y*o.x<x*o.y;
        else return mpp(u,v)<mpp(o.u,o.v);
    }
}l[maxn*maxn/2];
struct node{
    int pre,suf,maxsum,sum;
};
namespace Segtree{
    node st[4*maxn];
    node change(node x,node y){
        node res;res.sum=x.sum+y.sum;
        res.pre=max(x.pre,x.sum+y.pre);
        res.suf=max(y.suf,y.sum+x.suf);
        res.maxsum=max(max(x.maxsum,y.maxsum),x.suf+y.pre);
        return res;
    }
    void update(int l,int r,int id,int pos,int x){
        if(l==r){
            st[id].pre=st[id].suf=st[id].maxsum=st[id].sum=x;
            return;
        }
        int mid=(l+r)/2;
        if(pos<=mid) update(l,mid,id*2,pos,x);
        else update(mid+1,r,id*2+1,pos,x);
        st[id]=change(st[id*2],st[id*2+1]);
    }
    void build(int l,int r,int id){
        if(l==r){
            st[id].pre=st[id].suf=st[id].maxsum=st[id].sum=p[l].w;
            return;
        }
        int mid=(l+r)/2;
        build(l,mid,id*2);build(mid+1,r,id*2+1);
        st[id]=change(st[id*2],st[id*2+1]);
    }
}
int cur[maxn];
void solve(){
    int n;cin >> n;
    for(int i=1;i<=n;i++) cin >> p[i].x >> p[i].y >> p[i].w,cur[i]=i;
    sort(p+1,p+n+1);
    int cnt=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<i;j++) l[cnt++]={p[i].x-p[j].x,p[i].y-p[j].y,i,j};
    }
    sort(l,l+cnt);
    Segtree::build(1,n,1);
    int ans=max(0LL,Segtree::st[1].maxsum);
    for(int i=0;i<cnt;i++){
        int u=l[i].u,v=l[i].v;
        Segtree::update(1,n,1,cur[u],p[v].w);
        Segtree::update(1,n,1,cur[v],p[u].w);
        swap(cur[u],cur[v]);
        if(i==cnt-1 || l[i].x*l[i+1].y!=l[i+1].x*l[i].y) ans=max(ans,Segtree::st[1].maxsum);
    }
    cout << ans << '\n';
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
