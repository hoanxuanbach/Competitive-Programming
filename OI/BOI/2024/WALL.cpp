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
const long long inf=1e18;
const int mod=1e9+7;
const int maxn=500005;
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

int c[maxn];

struct node{
    int ls=0,lt=0,rs=0,rt=0,val=1,ss=1;
    node(){}
    friend node operator+(node a,node b){
        node res;
        res.ls=(a.ls*b.ss+a.val*b.ls)%mod;
        res.lt=(a.lt*b.ss+a.val*b.lt)%mod;
        res.rs=(b.rs*a.ss+b.val*a.rs)%mod;
        res.rt=(b.rt*a.ss+b.val*a.rt)%mod;
        res.val=(a.val*b.val)%mod;
        res.ss=(a.ss*b.ss)%mod;
        return res;
    }
}tree[4*maxn];

void build(int l,int r,int id){
    if(l==r){
        tree[id].ss=2;
        tree[id].val=c[l];
        tree[id].ls=tree[id].rs=(2-c[l]);
        tree[id].lt=tree[id].rt=(2-c[l])*l;
        return;
    }
    int mid=(l+r)>>1;
    build(l,mid,id<<1);build(mid+1,r,id<<1|1);
    tree[id]=tree[id<<1]+tree[id<<1|1];
}
void update(int l,int r,int id,int p){
    if(l==r){
        tree[id].val=c[l];
        tree[id].ls=tree[id].rs=(2-c[l]);
        tree[id].lt=tree[id].rt=(2-c[l])*l;
        return;
    }
    int mid=(l+r)>>1;
    if(p<=mid) update(l,mid,id<<1,p);
    else update(mid+1,r,id<<1|1,p);
    tree[id]=tree[id<<1]+tree[id<<1|1];
}
node query(int l,int r,int id,int tl,int tr){
    if(tr<l || r<tl) return node();
    if(tl<=l && r<=tr) return tree[id];
    int mid=(l+r)>>1;
    return query(l,mid,id<<1,tl,tr)+query(mid+1,r,id<<1|1,tl,tr);
}

int n,a[2][maxn];
vector<pii> p;

void solve(){
    cin >> n;
    for(int i=1;i<=n;i++) cin >> a[0][i];
    for(int i=1;i<=n;i++) cin >> a[1][i];
    for(int i=1;i<=n;i++){
        p.push_back({a[0][i],i});
        p.push_back({a[1][i],i});
    }
    sort(p.begin(),p.end());
    build(1,n,1);
    int res=0,mul=power(2,n-1);
    for(auto [x,i]:p){
        node L=(i>1?query(1,n,1,1,i-1):node());
        node R=(i<n?query(1,n,1,i+1,n):node());
        int num=0;
        num=(num+(R.lt-R.rs*i%mod+mod)*L.val%mod)%mod;
        num=(num+(L.rs*i%mod-L.rt+mod)*R.val%mod)%mod;
        num=(num+L.val*R.val)%mod;
        //cout << x << ' ' << i << ' ' << num << ' ' << L.val << ' ' << R.val << ' ' << R.lt << ' ' << R.rs << '\n';
        res=(res+x*(num-mul)%mod+mod)%mod;
        c[i]++;
        update(1,n,1,i);
    }
    cout << res << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
