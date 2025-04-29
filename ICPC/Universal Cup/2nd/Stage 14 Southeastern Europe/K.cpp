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

int n,k,a[maxn];
int cur[maxn];

bool check(int x){
    vector<int> p0,pMax;
    for(int i=1;i<=k;i++){
        if(x) pMax.push_back(i);
        cur[i]=0;
    }
    for(int i=1;i<=n;i++){
        if(a[i]==-1){
            while(!p0.empty() && !cur[p0.back()]) p0.pop_back();
            if(!p0.empty()){
                int id=p0.back();
                cur[id]--;p0.pop_back();
                if(cur[id]<x) pMax.push_back(id);
                if(cur[id]>0) p0.push_back(id);
            }
        }
        else{
            while(!pMax.empty() && cur[pMax.back()]==x) pMax.pop_back();
            if(pMax.empty()) return false;
            int id=pMax.back();pMax.pop_back();
            cur[id]++;
            if(cur[id]<x) pMax.push_back(id);
            if(cur[id]>0) p0.push_back(id);
        }
    }
    return true;
}

int ans[maxn];
void get(int x){
    vector<int> p0,pMax;
    for(int i=1;i<=k;i++){
        if(x) pMax.push_back(i);
        cur[i]=0;
    }
    for(int i=1;i<=n;i++){
        if(a[i]==-1){
            while(!p0.empty() && !cur[p0.back()]) p0.pop_back();
            if(!p0.empty()){
                int id=p0.back();ans[i]=id;
                cur[id]--;p0.pop_back();
                if(cur[id]<x) pMax.push_back(id);
                if(cur[id]>0) p0.push_back(id);
            }
            else ans[i]=1;
        }
        else{
            while(!pMax.empty() && cur[pMax.back()]==x) pMax.pop_back();
            int id=pMax.back();pMax.pop_back();
            cur[id]++;ans[i]=id;
            if(cur[id]<x) pMax.push_back(id);
            if(cur[id]>0) p0.push_back(id);
        }
    }
    for(int i=1;i<=n;i++) cout << ans[i] << ' ';
    cout << '\n';
}

void solve(){
    cin >> n >> k;
    for(int i=1;i<=n;i++) cin >> a[i];
    int l=0,r=n,res=n;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(mid)) res=mid,r=mid-1;
        else l=mid+1;
    }
    get(res);
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}
