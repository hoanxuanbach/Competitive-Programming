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
struct Segtree{
    vector<int> tree;
    Segtree(int n=0){
        tree.assign(4*n,inf);
    }
    void update(int l,int r,int id,int pos,int val){
        if(l==r){tree[id]=min(tree[id],val);return;}
        int mid=(l+r)>>1;
        if(pos<=mid) update(l,mid,id<<1,pos,val);
        else update(mid+1,r,id<<1|1,pos,val);
        tree[id]=min(tree[id<<1],tree[id<<1|1]);
    }
    int query(int l,int r,int id,int tl,int tr){
        if(r<tl || tr<l) return inf;
        if(tl<=l && r<=tr) return tree[id];
        int mid=(l+r)>>1;
        return min(query(l,mid,id<<1,tl,tr),query(mid+1,r,id<<1|1,tl,tr));
    }
};
void solve(){
    int m,n;cin >> m >> n;
    vector<int> com;
    vector<int> a(m),b(m),c(m),d(m);
    for(int i=0;i<m;i++){
        cin >> a[i] >> b[i] >> c[i] >> d[i];
        com.push_back(c[i]);
    }
    sort(com.begin(),com.end());
    com.erase(unique(com.begin(),com.end()),com.end());
    int sz=(int)com.size(),ans=inf;
    Segtree lt(sz),rt(sz);
    for(int i=0;i<m;i++){
        int l=lower_bound(com.begin(),com.end(),a[i])-com.begin()+1;
        int r=upper_bound(com.begin(),com.end(),b[i])-com.begin();
        int p=lower_bound(com.begin(),com.end(),c[i])-com.begin()+1;
        int cl=(a[i]==1?0:inf),cr=(b[i]==n?0:inf);
        if(l<=r){
            cl=min(cl,lt.query(1,sz,1,l,r));
            cr=min(cr,rt.query(1,sz,1,l,r));
        }
        ans=min(ans,d[i]+cl+cr);
        lt.update(1,sz,1,p,d[i]+cl);
        rt.update(1,sz,1,p,d[i]+cr);
    }
    cout << (ans==inf?-1:ans) << '\n';
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
