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
#define piii pair<long long,pii>
#define pli pair<pair<long long,int>,pii>
#define mpp make_pair
#define fi first
#define se second
const long long inf=1e18;
const int maxn=500005;

int n,m,a[maxn],pos[2*maxn];
long long ans,pa[maxn],pb[maxn];
int al,ar,bl,br;

namespace Segtree{
    pli cost[4*maxn];
    piii lazy[4*maxn];
    void build(int l,int r,int id){
        cost[id]={{-inf,0},{0,0}};
        lazy[id]={0,{0,0}};
        if(l==r) return;
        int mid=(l+r)>>1;
        build(l,mid,id<<1);build(mid+1,r,id<<1|1);
    }
    void getnew(int id,piii val){
        cost[id].fi.fi-=val.fi;
        lazy[id].fi+=val.fi;
        if(val.se.fi) cost[id].se.fi=lazy[id].se.fi=val.se.fi;
        if(val.se.se) cost[id].se.se=lazy[id].se.se=val.se.se;
    }
    void pushdown(int id){
        if(lazy[id]==mpp(0LL,mpp(0,0))) return;
        getnew(id<<1,lazy[id]);
        getnew(id<<1|1,lazy[id]);
        lazy[id]={0,{0,0}};
    }
    void update_pos(int l,int r,int id,int p,long long val,int tl,int tr,int pos){
        if(l==r){
            cost[id]={{val,pos},{tl,tr}};
            return;
        }
        pushdown(id);
        int mid=(l+r)>>1;
        if(p<=mid) update_pos(l,mid,id<<1,p,val,tl,tr,pos);
        else update_pos(mid+1,r,id<<1|1,p,val,tl,tr,pos);
        cost[id]=max(cost[id<<1],cost[id<<1|1]);
    }
    void update(int l,int r,int id,int tl,int tr,long long val,int pl,int pr){
        if(tr<l || r<tl) return;
        if(tl<=l && r<=tr){
            getnew(id,{val,{pl,pr}});
            return;
        }
        pushdown(id);
        int mid=(l+r)>>1;
        update(l,mid,id<<1,tl,tr,val,pl,pr);update(mid+1,r,id<<1|1,tl,tr,val,pl,pr);
        cost[id]=max(cost[id<<1],cost[id<<1|1]);
    }
}

void add(long long res,int xl,int xr,int yl,int yr){
    if(xl>xr || yl>yr) return;
    if(res>ans){
        ans=res;
        al=xl;ar=xr;
        bl=yl;br=yr;
    }
}
void cal(int l,int r,vector<pii> &p){
    int mid=(l+r)>>1,sz=(int)p.size();
    vector<int> lt,rt;
    Segtree::build(0,sz-1,1);
    for(int i=0;i<sz;i++){

        int dn=(i?p[i-1].fi:0),up=(i==sz-1?m:p[i+1].fi-1);
        Segtree::update_pos(0,sz-1,1,i,pa[r]-pa[l-1]-pb[dn],l-1,r+1,dn);
        if(p[i].se<=mid){
            int cur=l-1,pre=i;
            while(cur<p[i].se){
                int pl=(!lt.empty()?lt.back()+1:0);
                Segtree::update(0,sz-1,1,pl,pre,pa[p[i].se]-pa[cur],p[i].se,0);
                if(lt.empty() || p[pl-1].se>p[i].se) break;
                else lt.pop_back();
                cur=p[pl-1].se,pre=pl-1;
            }
            lt.push_back(i);
        }
        else{
            int cur=r+1,pre=i;
            while(true){
                int pl=(!rt.empty()?rt.back()+1:0);
                Segtree::update(0,sz-1,1,pl,pre,pa[cur-1]-pa[p[i].se-1],0,p[i].se);
                //cout << "update_rt " << pl << ' ' << pre << '\n';
                if(rt.empty() || p[pl-1].se<p[i].se) break;
                else rt.pop_back();
                cur=p[pl-1].se,pre=pl-1;
            }
            rt.push_back(i);
        }
        pli cur=Segtree::cost[1];
        add(cur.fi.fi+pb[up],cur.se.fi+1,cur.se.se-1,cur.fi.se+1,up);
    }
}
void dnc(int l,int r){
    if(l==r){
        if(a[l]){
            add(pa[l]-pa[l-1]+pb[a[l]-1],l,l,1,a[l]-1);
            add(pa[l]-pa[l-1]+pb[m]-pb[a[l]],l,l,a[l]+1,m);
        }
        else add(pa[l]-pa[l-1]+pb[m],l,l,1,m);
        return;
    }
    int mid=(l+r)>>1;
    dnc(l,mid);dnc(mid+1,r);
    vector<pii> p;
    for(int i=l;i<=r;i++) if(a[i]) p.push_back({a[i],i});
    sort(p.begin(),p.end());
    int sz=(int)p.size();
    int pre=0;
    for(int i=0;i<sz;i++){
        add(pa[r]-pa[l-1]+pb[p[i].fi-1]-pb[pre],l,r,pre+1,p[i].fi-1);
        pre=p[i].fi;
    }
    add(pa[r]-pa[l-1]+pb[m]-pb[pre],l,r,pre+1,m);
    if(sz) cal(l,r,p);
}

void solve(){
    cin >> n >> m;
    for(int i=1;i<=n;i++) cin >> a[i];
    for(int i=1;i<=n;i++) cin >> pa[i],pa[i]+=pa[i-1];
    for(int i=1;i<=m;i++){int x;cin >> x;pos[x]=i;}
    for(int i=1;i<=m;i++) cin >> pb[i],pb[i]+=pb[i-1];
    for(int i=1;i<=n;i++) a[i]=pos[a[i]];
    dnc(1,n);
    add(pa[n],1,n,0,0);
    add(pb[m],0,0,1,m);
    cout << ans << '\n' << al << ' ' << ar << '\n' << bl << ' ' << br << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
