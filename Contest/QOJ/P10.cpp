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
const int maxn=500005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=25;
const int maxa=500000;
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

struct Query{
    int L,R,id;
    bool operator<(Query o){
        if(L!=o.L) return L<o.L;
        else return R>o.R;
    }
}qq[maxn];

int n,q,a[maxn];
int res[maxn];
vector<int> pos[maxn];

namespace BIT{
    int bit[maxn];
    void update(int x,int val){
        for(int i=x;i<=n;i+=(i&(-i))) bit[i]+=val;
    }
    int query(int x){
        int ans=0;
        for(int i=x;i>=1;i-=(i&(-i))) ans+=bit[i];
        return ans;
    }
}
struct Segtree{
    pii tree[4*maxn];
    int lazy[4*maxn];
    void getnew(int id,int val){
        lazy[id]+=val;
        tree[id].fi-=val;
    }
    void pushdown(int id){
        if(!lazy[id]) return;
        getnew(id<<1,lazy[id]);
        getnew(id<<1|1,lazy[id]);
        lazy[id]=0;
    }
    void change(int l,int r,int id,int p,int val){
        if(l==r){
            tree[id]={val,-l};
            return;
        }
        pushdown(id);
        int mid=(l+r)>>1;
        if(p<=mid) change(l,mid,id<<1,p,val);
        else change(mid+1,r,id<<1|1,p,val);
        tree[id]=max(tree[id<<1],tree[id<<1|1]);
    }
    void update(int l,int r,int id,int tl,int tr){
        if(tr<l || r<tl) return;
        if(tl<=l && r<=tr){
            getnew(id,1);
            return;
        }
        pushdown(id);
        int mid=(l+r)>>1;
        update(l,mid,id<<1,tl,tr);update(mid+1,r,id<<1|1,tl,tr);
        tree[id]=max(tree[id<<1],tree[id<<1|1]);
    }
    pii query(int l,int r,int id,int tl,int tr){
        if(tr<l || r<tl) return {0,0};
        if(tl<=l && r<=tr) return tree[id];
        pushdown(id);
        int mid=(l+r)>>1;
        return max(query(l,mid,id<<1,tl,tr),query(mid+1,r,id<<1|1,tl,tr));
    }
}S1,S2;

void solve(){
    cin >> n >> q;
    for(int i=1;i<=n;i++){
        cin >> a[i];
        pos[a[i]].push_back(i);
    }
    for(int i=1;i<=q;i++){
        cin >> qq[i].L >> qq[i].R;
        qq[i].id=i;
    }
    sort(qq+1,qq+q+1);

    int Max=0;
    set<pii> sL,sR;
    for(int i=1;i<=q;i++){
        if(qq[i].R>Max){
            Max=qq[i].R;
            sL.insert({qq[i].L,i});
            sR.insert({qq[i].R,i});
            S1.change(1,q,1,i,qq[i].R-qq[i].L+1);
            //cout << "add " << qq[i].L << ' ' << qq[i].R << '\n';
        }
        else S2.change(1,q,1,i,qq[i].R);
    }

    for(int i=1;i<=n;i++) BIT::update(i,1);
    for(int i=maxa;i>=0;i--){
        //cout << Segtree::tree[1] << ' ' << i << '\n';
        while(true){
            pii p=S1.query(1,q,1,1,q);
            p.se=-p.se;
            if(p.fi<=i) break;
            res[qq[p.se].id]=i+1;
            sL.erase({qq[p.se].L,p.se});
            sR.erase({qq[p.se].R,p.se});
            S1.change(1,q,1,p.se,0);
            //cout << "del " << qq[p.se].L << ' ' << qq[p.se].R << '\n';
            //cout << "query " << i << ' ' << u << '\n';
            int pos=p.se;
            auto it=sR.upper_bound(mpp(qq[p.se].R,0));
            int cR=0;
            if(it!=sR.begin()){
                it--;
                cR=it->fi;
            }
            it=sL.upper_bound(mpp(qq[p.se].L,0));
            int lst=q;
            if(it!=sL.end()) lst=it->se-1;

            while(pos<=lst){
                p=S2.query(1,q,1,pos,lst);
                p.se=-p.se;
                if(p.fi<=cR) break;
                //cout << "add " << qq[p.se].L << ' ' << qq[p.se].R << '\n';
                S2.change(1,q,1,p.se,0);
                sL.insert({qq[p.se].L,p.se});
                sR.insert({qq[p.se].R,p.se});
                S1.change(1,q,1,p.se,BIT::query(qq[p.se].R)-BIT::query(qq[p.se].L-1));
                lst=p.se-1;
            }
        }
        for(int id:pos[i]){
            BIT::update(id,-1);
            auto it=sL.upper_bound({id,inf});
            int r=(it==sL.end()?q:it->se-1);
            it=sR.lower_bound({id,0});
            int l=(it==sR.end()?q+1:it->se);
            //cout << id << ' ' << l << ' ' << r << '\n';
            if(l<=r) S1.update(1,q,1,l,r);
        }
    }
    for(int i=1;i<=q;i++) cout << res[i] << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}