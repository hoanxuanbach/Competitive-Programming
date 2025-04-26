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
const int maxn=300005;
const int B=650;
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
const int base=101;

int n,q,ans;
multiset<int> sa[maxn],sd[maxn];

namespace Segtree{
    int lazy[4*maxn],tree[4*maxn];
    pii Max[4*maxn],Min[4*maxn],lst[4*maxn];
    void merge(int id){
        Max[id]=max(Max[id<<1],Max[id<<1|1]);
        Min[id]=min(Min[id<<1],Min[id<<1|1]);
        tree[id]=min(tree[id<<1],tree[id<<1|1])+lazy[id];
        if(tree[id<<1]>tree[id<<1|1]) lst[id]=lst[id<<1|1];
        else if(tree[id<<1]<tree[id<<1|1]) lst[id]=lst[id<<1];
        else lst[id]={lst[id<<1].fi,lst[id<<1|1].se};
    }
    void cal(int l,int id){
        Max[id]={sd[l].empty()?-inf:*sd[l].rbegin(),l};
        Min[id]={sa[l].empty()?inf:*sa[l].begin(),l};
    }
    void build(int l,int r,int id){
        if(l==r){
            cal(l,id);
            tree[id]=l;
            lst[id]={l,l};
            return;
        }
        int mid=(l+r)>>1;
        build(l,mid,id<<1);build(mid+1,r,id<<1|1);
        merge(id);
    }
    void update(int l,int r,int id,int p,int val){
        if(l==r){
            tree[id]+=val;
            lazy[id]+=val;
            cal(l,id);
            return;
        }
        int mid=(l+r)>>1;
        if(p<=mid){
            tree[id<<1|1]+=val;
            lazy[id<<1|1]+=val;
            update(l,mid,id<<1,p,val);
        }
        else update(mid+1,r,id<<1|1,p,val);
        merge(id);
    }
    pii queryMax(int l,int r,int id,int tl,int tr){
        if(tr<l || r<tl) return {-inf,-1};
        if(tl<=l && r<=tr) return Max[id];
        int mid=(l+r)>>1;
        return max(queryMax(l,mid,id<<1,tl,tr),queryMax(mid+1,r,id<<1|1,tl,tr));
    }
    pii queryMin(int l,int r,int id,int tl,int tr){
        if(tr<l || r<tl) return {inf,-1};
        if(tl<=l && r<=tr) return Min[id];
        int mid=(l+r)>>1;
        return min(queryMin(l,mid,id<<1,tl,tr),queryMin(mid+1,r,id<<1|1,tl,tr));
    }
    pii query(int l,int r,int id,int tl,int tr){
        if(tr<l || r<tl) return {inf,-1};
        if(tl<=l && r<=tr) return {tree[id],lst[id].fi};
        int mid=(l+r)>>1;
        pii res=min(query(l,mid,id<<1,tl,tr),query(mid+1,r,id<<1|1,tl,tr));
        return {res.fi+lazy[id],res.se};
    }
}

void add(int t,int val){
    pii p=Segtree::query(1,n,1,t,n);
    if(p.fi){
        ans+=val;
        sa[t].insert(val);
        Segtree::update(1,n,1,t,-1);
        //Segtree::update(1,n,1,t);
    }
    else{
        pii X=Segtree::queryMin(1,n,1,1,p.se);
        if(X.fi<val){
            ans-=X.fi;
            sa[X.se].erase(sa[X.se].begin());
            sd[X.se].insert(X.fi);
            Segtree::update(1,n,1,X.se,1);
            //Segtree::update(1,n,1,X.se);
            ans+=val;
            sa[t].insert(val);
            Segtree::update(1,n,1,t,-1);
            //Segtree::update(1,n,1,t);
        }
        else{
            sd[t].insert(val);
            Segtree::update(1,n,1,t,0);
        }
    }
}
void del(int t,int val){
    if(sd[t].find(val)!=sd[t].end()){
        sd[t].erase(sd[t].find(val));
        Segtree::update(1,n,1,t,0);
    }
    else{
        ans-=val;
        sa[t].erase(sa[t].find(val));
        Segtree::update(1,n,1,t,1);
        //Segtree::update(1,n,1,t);

        int l=(Segtree::tree[1]==0?Segtree::lst[1].se+1:1);
        if(l<=n){
            pii X=Segtree::queryMax(1,n,1,l,n);
            if(X.fi!=-inf){
                ans+=X.fi;
                sd[X.se].erase(sd[X.se].find(X.fi));
                sa[X.se].insert(X.fi);
                Segtree::update(1,n,1,X.se,-1);
                //Segtree::update(1,n,1,X.se);
            }
        }
    }
}

void solve(){
    cin >> n >> q;
    Segtree::build(1,n,1);
    for(int i=1;i<=q;i++){
        string s;int t,val;cin >> s >> t >> val;
        if(s[0]=='A') add(t,val);
        else del(t,val);
        cout << ans << '\n';
        assert(Segtree::tree[1]>=0);
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
