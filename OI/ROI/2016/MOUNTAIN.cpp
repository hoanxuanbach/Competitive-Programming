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
const int inf=9e18;
const int mod=998244353;
const int maxn=400005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
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
const int base=101;

struct line{
    int a,b,p;
    bool operator<(line l){return a<l.a;}
    bool operator<(int k){return p<k;}
};
struct cvht{
    vector<line> x;
    int div(int a,int b){
        return a/b-((a^b)<0 && a%b);
    }
    bool isect(line &l,line y){
        if(l.a==y.a) l.p=(l.b>y.b)?inf:-inf;
        else l.p=div(y.b-l.b,l.a-y.a);
        return l.p>=y.p;
    }
    void add(line l){
        if(!x.empty()) isect(x.back(),l);
        while((int)x.size()>=2 && x[(int)x.size()-2].p>=x.back().p){
            x.pop_back();
            isect(x.back(),l);
        }
        x.push_back(l);
    }
    int query(int v){
        auto l=*lower_bound(x.begin(),x.end(),v);
        return l.a*v+l.b;
    }
};

cvht tree[4*maxn];
vector<pii> L[4*maxn];

int n,q,d[maxn],k[maxn],x[maxn],y[maxn];

void build(int l,int r,int id){
    if(l==r){
        L[id].push_back({k[l],y[l-1]-x[l-1]*k[l]});
        return;
    }
    int mid=(l+r)>>1;
    build(l,mid,id<<1);build(mid+1,r,id<<1|1);
    for(pii a:L[id<<1]) L[id].push_back(a);
    for(pii a:L[id<<1|1]) L[id].push_back(a);
}
int query_lt(int l,int r,int id,int p,int xt,int yt){
    //cout << l << ' ' << r << ' ' << tree[id].query(xt) << '\n';
    if(r<=p && tree[id].query(xt)<=yt) return x[0];
    if(l==r) return x[l];
    int mid=(l+r)>>1;
    if(p<=mid) return query_lt(l,mid,id<<1,p,xt,yt);
    else{
        int res=query_lt(mid+1,r,id<<1|1,p,xt,yt);
        if(res!=x[0]) return res;
        else return query_lt(l,mid,id<<1,p,xt,yt);
    }
}
int query_rt(int l,int r,int id,int p,int xt,int yt){
    if(p<=l && tree[id].query(xt)<=yt) return x[n];
    if(l==r) return x[l-1];
    int mid=(l+r)>>1;
    if(mid<p) return query_rt(mid+1,r,id<<1|1,p,xt,yt);
    else{
        int res=query_rt(l,mid,id<<1,p,xt,yt);
        if(res!=x[n]) return res;
        else return query_rt(mid+1,r,id<<1|1,p,xt,yt);
    }
}

void solve(){
    cin >> n >> q;
    for(int i=1;i<=n;i++){
        cin >> d[i] >> k[i];
        x[i]=x[i-1]+d[i];
        y[i]=y[i-1]+k[i]*d[i];
    }
    build(1,n,1);
    for(int i=1;i<4*n;i++){
        sort(L[i].begin(),L[i].end());
        for(pii x:L[i]) tree[i].add({x.fi,x.se,inf});
    }
    for(int i=1;i<=q;i++){
        int xt,yt;cin >> xt >> yt;
        int p=upper_bound(x,x+n+1,xt)-x;
        int lt=0,rt=x[n];
        if(p==n+1) p--;
        lt=query_lt(1,n,1,p,xt,yt);
        rt=query_rt(1,n,1,p,xt,yt);
        cout << lt << ' ' << rt << '\n';
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
