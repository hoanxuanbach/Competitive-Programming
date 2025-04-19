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
const int maxn=200005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=500005;
const int maxl=20;
const int maxa=1e9;
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
vector<int> com;
namespace Segtree{
    int tree[4*maxn],cnt[4*maxn];
    void update(int l,int r,int id,int p,int val){
        if(l==r){
            cnt[id]+=val;;
            tree[id]+=val*com[l-1];
            return;
        }
        int mid=(l+r)>>1;
        if(p<=mid) update(l,mid,id<<1,p,val);
        else update(mid+1,r,id<<1|1,p,val);
        tree[id]=tree[id<<1]+tree[id<<1|1];
        cnt[id]=cnt[id<<1]+cnt[id<<1|1];
    }
    int query(int l,int r,int id,int x){
        if(l==r) return com[l-1]*x;
        int mid=(l+r)>>1;
        if(cnt[id<<1|1]<x) return tree[id<<1|1]+query(l,mid,id<<1,x-cnt[id<<1|1]);
        else return query(mid+1,r,id<<1|1,x);
    }
}
void solve(){
    int n,m;cin >> n >> m;
    vector<pii> x(n);
    for(int i=0;i<n;i++) cin >> x[i].se >> x[i].fi,com.push_back(x[i].se);
    sort(x.begin(),x.end());
    sort(com.begin(),com.end());
    com.erase(unique(com.begin(),com.end()),com.end());
    for(int i=0;i<n;i++) x[i].se=lower_bound(com.begin(),com.end(),x[i].se)-com.begin()+1;
    int ans=-inf,sz=(int)com.size(),cl=0,cr=-1;
    auto cost = [&](int l,int r){
        while(cl>l) Segtree::update(1,sz,1,x[--cl].se,1);
        while(cr<r) Segtree::update(1,sz,1,x[++cr].se,1);
        while(cl<l) Segtree::update(1,sz,1,x[cl++].se,-1);
        while(cr>r) Segtree::update(1,sz,1,x[cr--].se,-1);
        return Segtree::query(1,sz,1,m)-2*(x[r].fi-x[l].fi);
    };
    function<void(int,int,int,int)> dnc = [&](int l,int r,int optl,int optr){
        if(l>r) return;
        int sum=0,mid=(l+r)>>1;
        pii opt={-inf,-1};
        for(int i=min(optr,mid-m+1);i>=optl;i--){
            int res=cost(i,mid);ans=max(ans,res);
            opt=max(opt,{res,i});
        }
        dnc(l,mid-1,optl,opt.se);
        dnc(mid+1,r,opt.se,optr);
    };
    dnc(m-1,n-1,0,n-m);
    cout << ans << '\n';
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
