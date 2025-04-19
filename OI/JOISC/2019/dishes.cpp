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

void solve(){
    int n,m;cin >> n >> m;
    vector<int> a(n+1,0),b(m+1,0),s(n+1),t(m+1),p(n+1),q(m+1);
    for(int i=1;i<=n;i++) cin >> a[i] >> s[i] >> p[i],a[i]+=a[i-1];
    for(int i=1;i<=m;i++) cin >> b[i] >> t[i] >> q[i],b[i]+=b[i-1];
    vector<vector<pii>> add(n+1);
    int ans=0;
    for(int i=1;i<=n;i++){
        int l=0,r=m,res=m+1;
        while(r>=l){
            int mid=(l+r)>>1;
            if(a[i]+b[mid]<=s[i]) l=mid+1;
            else res=mid,r=mid-1;
        }
        //cout << res << '\n';
        if(res==0) continue;
        ans+=p[i];
        if(res!=m+1) add[i].push_back({res,-p[i]});
    }
    for(int i=1;i<=m;i++){
        int l=0,r=n,res=n+1;
        while(r>=l){
            int mid=(l+r)>>1;
            if(b[i]+a[mid]<=t[i]) l=mid+1;
            else res=mid,r=mid-1;
        }
        //cout << res << '\n';
        if(res==0) continue;
        if(res!=n+1) add[res].push_back({i,q[i]});
        else ans+=q[i];
    }
    set<pii> ss,Min;
    for(int i=1;i<=n;i++){
        for(auto [x,val]:add[i]){
            auto it=ss.lower_bound({x,-inf});
            if(it!=ss.end() && it->fi==x){
                pii np=*it;
                int sum=val+np.se;
                ss.erase(it);Min.erase({np.se,np.fi});
                ss.insert({x,sum});Min.insert({sum,x});
            }
            else ss.insert({x,val}),Min.insert({val,x});
        }
        while(!Min.empty() && Min.begin()->fi<0){
            pii np=*Min.begin();Min.erase(Min.begin());
            swap(np.fi,np.se);
            auto it=ss.lower_bound(np);it=ss.erase(it);
            if(it!=ss.end()){
                np.fi=it->fi,np.se+=it->se;
                Min.erase({it->se,it->fi});ss.erase(it);
                ss.insert(np);Min.insert({np.se,np.fi});
            }
        }
    }
    for(auto [x,val]:ss) ans+=val;
    cout << ans << '\n';
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
