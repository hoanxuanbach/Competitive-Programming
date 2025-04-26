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
#define ld long double
#define pii pair<int,int>
#define piii pair<int,pii>
#define mpp make_pair
#define fi first
#define se second
const long long inf=1e18;
const int mod=998244353;
const int maxn=505;
const int B=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=25;
const int maxa=1000000;
const int root=3;
const int base=101;

const int D = 20000000;
int cnt[2*D+5];
int n,a[maxn];

void solve(){
    cin >> n;
    for(int i=1;i<=n;i++) cin >> a[i],a[i]+=a[i-1];
    long long total=0;
    for(int i=1;i<=n;i++){
        for(int l=1;l<=n;l++) for(int r=l;r<=n;r++) cnt[a[r]-a[l-1]-a[i-1]+D]++;
        for(int l=1;l<=n;l++) for(int r=l;r<=n;r++) total+=cnt[-(a[r]-a[l-1]+a[i])+D];
    }
    map<int,int> mp;
    for(int l=1;l<=n;l++) for(int r=l;r<=n;r++){
        if(a[r]-a[l-1]==0) total+=2;
        mp[a[r]-a[l-1]]++;
    }
    for(int l=1;l<=n;l++) for(int r=l;r<=n;r++) total-=3*mp[-2*(a[r]-a[l-1])];
    cout << total/6 << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
