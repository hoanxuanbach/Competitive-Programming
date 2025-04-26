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

int n,D[maxn],U[maxn],P[maxn],M[maxn],C[maxn],dd[maxn];
pii a[maxn];
int b[maxn];

struct node{
    pii Min={inf,0};
    int val=0,lazy=0;
    bool flag=false;
    node(){}
    friend node operator+(node a,node b){
        node res;
        if(a.flag) res.Min=min(res.Min,a.Min);
        if(b.flag) res.Min=min(res.Min,b.Min);
        res.val=min(a.val,b.val);
        res.flag=a.flag||b.flag;
        return res;
    }
};

struct Segtree{
    node tree[4*maxn];
    void build(int l,int r,int id){
        if(l==r){
            tree[id].Min=a[l];
            tree[id].flag=b[l];
            return;
        }
        int mid=(l+r)>>1;
        build(l,mid,id<<1);build(mid+1,r,id<<1|1);
        tree[id]=tree[id<<1]+tree[id<<1|1];
    }
    void getnew(int id,int val){
        tree[id].lazy+=val;
        tree[id].Min.fi+=val;
        tree[id].val+=val;
    }
    void pushdown(int id){
        if(!tree[id].lazy) return;
        getnew(id<<1,tree[id].lazy);
        getnew(id<<1|1,tree[id].lazy);
        tree[id].lazy=0;
    }
    void update(int l,int r,int id,int tl,int tr,int val){
        if(tr<l || r<tl) return;
        if(tl<=l && r<=tr){
            getnew(id,val);
            return;
        }
        pushdown(id);
        int mid=(l+r)>>1;
        update(l,mid,id<<1,tl,tr,val);update(mid+1,r,id<<1|1,tl,tr,val);
        tree[id]=tree[id<<1]+tree[id<<1|1];
    }
    pii query(int l,int r,int id,int tl,int tr){
        if(tr<l || r<tl || !tree[id].flag) return mpp(inf,0);
        if(tl<=l && r<=tr) return tree[id].Min;
        pushdown(id);
        int mid=(l+r)>>1;
        return min(query(l,mid,id<<1,tl,tr),query(mid+1,r,id<<1|1,tl,tr));
    }
}lt,rt,fl;

void update(int l,int r,int id,int tl,int tr,int val){
    if(tr<l || r<tl || (val<0 && !fl.tree[id].flag)) return;
    if(tl<=l && r<=tr && ((val<0 && fl.tree[id].Min.fi+val>0) || (val>0 && fl.tree[id].val>0))){
        fl.getnew(id,val);
        return;
    }
    if(l==r){
        fl.tree[id].Min.fi+=val;fl.tree[id].val+=val;
        if(fl.tree[id].Min.fi) fl.tree[id].flag=true,dd[l]+=C[l]+M[l];
        else{
            fl.tree[id].flag=false,lt.update(1,n,1,1,l,C[l]+M[l]);
            //cout << "lt update " << l << ' ' << C[l]+M[l] << '\n';
        }
        return;
    }
    fl.pushdown(id);
    int mid=(l+r)>>1;
    update(l,mid,id<<1,tl,tr,val);update(mid+1,r,id<<1|1,tl,tr,val);
    fl.tree[id]=fl.tree[id<<1]+fl.tree[id<<1|1];
}

/*
1 1 2 5
1 2 1 6
2 2 2 1
3 3 1 5
4 4 2 5
*/

void solve(){
    cin >> n;
    for(int i=1;i<=n;i++) cin >> D[i];
    for(int i=1;i<=n;i++) cin >> U[i];
    for(int i=1;i<=n;i++) cin >> P[i];
    for(int i=1;i<n;i++) cin >> C[i];
    for(int i=1;i<n;i++) cin >> M[i];
    for(int i=1;i<=n;i++) a[i]=mpp(a[i-1].fi+M[i-1],i);
    for(int i=1;i<=n;i++) a[i].fi+=P[i],b[i]=1;
    rt.build(1,n,1);
    for(int i=1;i<=n;i++) a[i].fi=P[i];
    lt.build(1,n,1);
    for(int i=1;i<=n;i++) a[i].fi=0,b[i]=0;
    fl.build(1,n,1);

    int ans=0;
    for(int i=1;i<=n;i++){
        if(i>1){
            //cout << "lt update " << i-1 << ' ' << C[i-1]-dd[i-1] << '\n';
            lt.update(1,n,1,1,i-1,C[i-1]-dd[i-1]);
            rt.update(1,n,1,i,n,-M[i-1]);
        }
        while(D[i]){
            pii L=(i==1?mpp(inf,0LL):lt.query(1,n,1,1,i-1));
            pii R=rt.query(1,n,1,i,n);
            //cout << "get " << i << ' ' << L.fi << ' ' << L.se
            if(L<R){
                int x=L.se,F=min(U[x],D[i]);
                if(x<i) F=min(F,fl.query(1,n,1,x,i-1).fi);
                U[x]-=F;D[i]-=F;
                ans+=F*L.fi;
                //cout << i << ' ' << x << ' ' << F <<  ' ' << L.fi << '\n';
                if(!U[x]){
                    lt.update(1,n,1,x,x,inf);
                    rt.update(1,n,1,x,x,inf);
                }
                if(x<i) update(1,n,1,x,i-1,-F);
            }
            else{
                int x=R.se,F=min(U[x],D[i]);
                U[x]-=F;D[i]-=F;
                ans+=F*R.fi;
                //cout << i << ' ' << x << ' ' << F << ' ' << R.fi << '\n';
                if(!U[x]){
                    lt.update(1,n,1,x,x,inf);
                    rt.update(1,n,1,x,x,inf);
                }
                if(i<x) update(1,n,1,i,x-1,F);
            }
        }
    }
    cout << ans << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
