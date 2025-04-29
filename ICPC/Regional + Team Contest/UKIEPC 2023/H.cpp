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
const int mod=998244353;
const int maxn=300005;
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
const int base=101;

pair<pii,bool> ff(int a1,int a2,int d,int b1,int b2){
    if(d==inf){
        if(a1==inf) return {{b1,b2},true};
        else if(b1==inf) return {{a1,a2},true};
        else return {{a1,b2},(a2<b1)};
    }
    else{
        if(a1==inf && b1==inf) return {{d,d},true};
        else if(a1==inf) return {{d,b2},d<b1};
        else if(b1==inf) return {{a1,d},a2<d};
        else return {{a1,b2},(a2<d) && (d<b1)};
    }
}

struct node{
    int l1=inf,l2=inf,r1=inf,r2=inf,f1=inf,f2=inf,lazy=0;
    bool check=true;
    node(int x=inf):l1(x),r1(x){}
    friend node operator+(node a,node b){
        node res;
        if(a.l2==inf && b.l2==inf){
            if(a.l1==b.l1) return a;
            else{
                res.l1=a.l1;res.l2=b.l1;
                res.r1=b.r1;res.r2=a.r1;
            }
        }
        else if(a.l2==inf){
            if(a.r1==b.l1) return b;
            res=b;
            res.l2=b.l1;
            res.l1=a.r1;
            if(a.r1>b.l1 && b.l1<b.l2){
                auto x = ff(a.f1,a.f2,b.l1,b.f1,b.f2);
                res.check &= x.se;
                res.f1=x.fi.fi;res.f2=x.fi.se;
            }
        }
        else if(b.l2==inf){
            if(a.r1==b.l1) return a;
            res=a;
            res.r2=a.r1;
            res.r1=b.l1;
            if(a.r1<a.r2 && a.r1<b.l1){
                auto x = ff(a.f1,a.f2,a.r1,b.f1,b.f2);
                res.check &= x.se;
                res.f1=x.fi.fi;res.f2=x.fi.se;
            }
        }
        else{
            res.l1=a.l1;res.l2=a.l2;
            res.r1=b.r1;res.r2=b.r2;
            res.check = (a.check && b.check);
            int d=inf;
            if(a.r1==b.l1){
                if(a.r1<a.r2 && b.l1<b.l2) d=a.r1;
            }
            else{
                if(a.r1<a.r2 && a.r1<b.l1) d=a.r1;
                if(b.l1<b.l2 && b.l1<a.r1) d=b.l1;
            }
            auto x=ff(a.f1,a.f2,d,b.f1,b.f2);
            res.f1=x.fi.fi;res.f2=x.fi.se;
            res.check&=x.se;
        }
        return res;
    }
    void print(){
        cout << l1 << ' ' << l2 << ' ' << r1 << ' ' << r2 << ' ' << f1 << ' ' << f2 << '\n';
    }
};

node tree[4*maxn];
int n,m,e[maxn];
void build(int l,int r,int id){
    if(l==r){
        tree[id]=node(e[l]);
        return;
    }
    int mid=(l+r)>>1;
    build(l,mid,id<<1);build(mid+1,r,id<<1|1);
    tree[id]=tree[id<<1]+tree[id<<1|1];
    //tree[id].print();
}
void getnew(int id,int val){
    tree[id].l1+=val;
    tree[id].r1+=val;
    if(tree[id].l2!=inf) tree[id].l2+=val;
    if(tree[id].r2!=inf) tree[id].r2+=val;
    if(tree[id].f1!=inf) tree[id].f1+=val;
    if(tree[id].f2!=inf) tree[id].f2+=val;
    tree[id].lazy+=val;
}
void pushdown(int id){
    if(tree[id].lazy==0) return;
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
    tree[id]=tree[id<<1]+tree[id<<1|1];tree[id].lazy=0;
}
node query(int l,int r,int id,int tl,int tr){
    if(tl<=l && r<=tr) return tree[id];
    pushdown(id);
    int mid=(l+r)>>1;
    if(tr<=mid) return query(l,mid,id<<1,tl,tr);
    else if(mid<tl) return query(mid+1,r,id<<1|1,tl,tr);
    else return query(l,mid,id<<1,tl,tr)+query(mid+1,r,id<<1|1,tl,tr);
}

void solve(){
    cin >> n;
    for(int i=1;i<=n;i++) cin >> e[i];
    build(1,n,1);
    int m;cin >> m;
    while(m--){
        string s;
        int l,r,val;
        cin >> s;
        if(s=="check"){
            cin >> l >> r;
            node res=query(1,n,1,l,r);
            if(res.l2==inf) cout << "YES\n";
            else if(!res.check) cout << "NO\n";
            else{
                pii cur={res.f1,res.f2};
                bool check=true;
                if(res.l1<res.l2){
                    auto x=ff(inf,inf,res.l1,cur.fi,cur.se);
                    if(!x.se) check=false;
                    cur=x.fi;
                }
                if(res.r1<res.r2){
                    auto x=ff(cur.fi,cur.se,res.r1,inf,inf);
                    if(!x.se) check=false;
                    cur=x.fi;
                }
                cout << (check?"YES\n":"NO\n");
            }
        }
        else{
            cin >> l >> r >> val;
            update(1,n,1,l,r,val);
        }
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
