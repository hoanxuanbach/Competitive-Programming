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
const int maxn=200005;
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
const int base=131;

int n,q,a[maxn],res[maxn],s[maxn];
vector<pii> qq[maxn];

int sz[maxn],k[maxn],d[maxn];

struct BIT{
    int bit[2*maxn];
    void update(int x,int val){
        assert(x);
        for(int i=x;i<=2*n;i+=(i&(-i))) bit[i]+=val;
    }
    int query(int x){
        int res=0;
        for(int i=x;i>=1;i-=(i&(-i))) res+=bit[i];
        return res;
    }
};

struct DS{
    BIT f0,f1,g0,g1;
    void update(int D,int K,int S,int val){
        f0.update(S+K+n,D*val);
        f1.update(S+K+n,D*(S+K)*val);
        g0.update(K,D*val);
        g1.update(K,D*K*val);
    }
    int query(int T,int T0){
        int res=0;
        res+=f1.query(T+n);
        res+=T*(f0.query(2*n)-f0.query(T+n));
        res-=g1.query(T0);
        res-=(g0.query(2*n)-g0.query(T0))*T;
        return res;
    }
}d0,d1;

void solve(){
    cin >> n >> q;
    for(int i=1;i<=n;i++) cin >> a[i],s[i]=s[i-1]+a[i];
    for(int i=1;i<=q;i++){
        int t,l,r;cin >> t >> l >> r;
        t=min(t,n-1);
        qq[l-1].push_back({-i,t});
        qq[r].push_back({i,t});
        res[i]=s[r]-s[l-1];
    }
    vector<int> v;
    for(int i=1;i<=n;i++){
        while(!v.empty() && a[v.back()]<a[i]){
            int x=v.back();v.pop_back();
            if(v.empty()) break;
            d0.update(d[x],k[x],sz[x],-1);
            sz[x]+=i-1;
            d1.update(d[x],k[x],sz[x],1);
        }
        if(!v.empty()){
            d[i]=a[v.back()]-a[i];
            k[i]=i-v.back();
            sz[i]=1-i;
            d0.update(d[i],k[i],sz[i],1);
            //cout << d[i] << ' ' << k[i] << ' ' << sz[i] << ' ' << i << '\n';
        }
        v.push_back(i);
        for(auto [id,T]:qq[i]){
            int val=d1.query(T+1,T+1)+d0.query(T+1-i,T+1);
            val+=i*d0.g0.query(T+1);
            if(id<0) res[-id]-=val;
            else res[id]+=val;
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
