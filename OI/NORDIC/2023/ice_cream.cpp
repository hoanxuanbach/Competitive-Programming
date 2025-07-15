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
#define piii pair<pii,int>
#define mpp make_pair
#define fi first
#define se second
const int mod=998244353;
const int maxn=200005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=20;
const int maxa=1000000;
const int root=3;
const int base=101;

int n,m,k,nxt[maxn],a[maxn],cur[maxn];

void solve(){
    cin >> n >> m >> k;
    for(int i=1;i<=n;i++) cin >> a[i];
    for(int i=1;i<=m;i++) cur[i]=n+1;
    for(int i=n;i>=1;i--){
        nxt[i]=cur[a[i]];
        cur[a[i]]=i;
    }
    set<pii> ss;
    set<int> s;
    int cnt=0;
    for(int i=1;i<=n;i++){
        int x=a[i];
        if(s.find(x)!=s.end()){
            ss.erase({i,x});
            ss.insert({nxt[i],x});
            continue;
        }
        if((int)s.size()==k){
            pii d=*ss.rbegin();
            ss.erase(d);s.erase(d.se);
        }
        ss.insert({nxt[i],x});
        s.insert(x);cnt++;
    }
    cout << cnt << '\n';
}

signed main(){
    //freopen("ICECREAM.INP","r",stdin);
    //freopen("ICECREAM.OUT","w",stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}