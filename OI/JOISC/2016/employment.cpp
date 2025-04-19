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
namespace BIT{
    int bit[2*maxn],n;
    void init(int N){n=N;}
    int query(int x){
        int res=0;
        for(int i=x;i>=1;i-=(i&(-i))) res+=bit[i];
        return res;
    }
    void update(int x,int val){
        for(int i=x;i<=n;i+=(i&(-i))) bit[i]+=val;
    }
    void update_range(int l,int r,int val){
        update(l,val);update(r+1,-val);
    }
}
int n,m,a[maxn];
void solve(){
    cin >> n >> m;
    vector<int> com;
    for(int i=1;i<=n;i++) cin >> a[i],com.push_back(a[i]);
    vector<pii> p;
    for(int i=1;i<=m;i++){
        int t,c,d=-1;cin >> t >> c;
        if(t==2) cin >> d,com.push_back(d);
        p.push_back({c,d});
    }
    sort(com.begin(),com.end());
    com.erase(unique(com.begin(),com.end()),com.end());
    int sz=(int)com.size();BIT::init(sz+1);
    auto get = [&](int x){
        return lower_bound(com.begin(),com.end(),x)-com.begin()+1;
    };
    auto add = [&](int x,int y,int val){
        if(x>y) BIT::update_range(y+1,x,val);
    };
    for(int i=1;i<=n;i++){
        a[i]=get(a[i]);
        if(i>=2) add(a[i-1],a[i],1);
    }
    for(auto &[c,d]:p){
        if(d==-1) cout << BIT::query(c=get(c))+(a[n]>=c) << '\n';
        else{
            d=get(d);
            if(c>=2) add(a[c-1],a[c],-1);
            if(c<n) add(a[c],a[c+1],-1);
            a[c]=d;
            if(c>=2) add(a[c-1],a[c],1);
            if(c<n) add(a[c],a[c+1],1);
        }
    }
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
