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
struct BIT{
    int n;
    vector<int> bit;
    BIT(int N):n(N){
        bit.assign(n+1,0);
    };
    void update(int x,int val){
        for(int i=x;i<=n;i+=(i&(-i))) bit[i]+=val;
    }
    int query(int x){
        int res=0;
        for(int i=x;i>=1;i-=(i&(-i))) res+=bit[i];
        return res;
    }
};
struct Segtree{
    int n;
    vector<int> tree,lazy;
    Segtree(int N):n(N){
        tree.assign(4*n,-inf);
        lazy.assign(4*n,0);
    }
    void update(int l,int r,int id,int tl,int tr,int val){
        if(tr<l || r<tl) return;
        if(tl<=l && r<=tr){
            lazy[id]+=val;tree[id]+=val;
            return;
        }
        int mid=(l+r)>>1;
        update(l,mid,id<<1,tl,tr,val);update(mid+1,r,id<<1|1,tl,tr,val);
        tree[id]=max(tree[id<<1],tree[id<<1|1])+lazy[id];
    }
    int query(int l,int r,int id,int p){
        if(l==r) return tree[id];
        int mid=(l+r)>>1;
        if(p<=mid) return query(l,mid,id<<1,p)+lazy[id];
        else return max(tree[id<<1],query(mid+1,r,id<<1|1,p))+lazy[id];
    }
};
int n,sz;
vector<int> get(vector<int> &h,vector<int> &c,vector<int> &p){
    vector<vector<int>> pos(sz+1);
    for(int i=1;i<=n;i++) pos[h[i]].push_back(i);
    vector<int> dp(n+1);
    Segtree ST(n);
    BIT bit(n);
    for(int i=1;i<=n;i++){
        ST.update(1,n,1,i,n,p[i]);
        bit.update(i,p[i]);
    }
    for(int i=1;i<=sz;i++){
        for(int x:pos[i]) ST.update(1,n,1,x,n,-p[x]),bit.update(x,-p[x]);
        for(int x:pos[i]){
            dp[x]=max(0LL,ST.query(1,n,1,x))-bit.query(x)+c[x];
            //cout << x << ' ' << h[x] << ' ' << bit.query(x) << '\n';
            ST.update(1,n,1,x,x,inf+dp[x]);
        }
    }
    //for(int i=1;i<=n;i++) cout << dp[i] << ' ';
    //cout << '\n';
    return dp;
}
void solve(){
    cin >> n;
    vector<int> h(n+1),c(n+1),p(n+1),com;
    for(int i=1;i<=n;i++) cin >> h[i] >> c[i] >> p[i],com.push_back(h[i]);

    sort(com.begin(),com.end());
    com.erase(unique(com.begin(),com.end()),com.end());
    for(int i=1;i<=n;i++) h[i]=lower_bound(com.begin(),com.end(),h[i])-com.begin()+1;
    sz=(int)com.size();

    vector<int> dpl=get(h,c,p);
    reverse(h.begin()+1,h.end());
    reverse(c.begin()+1,c.end());
    reverse(p.begin()+1,p.end());
    vector<int> dpr=get(h,c,p);
    int ans=0;
    for(int i=1;i<=n;i++) ans=max(ans,dpr[i]+dpl[n-i+1]-c[i]);
    cout << ans << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
