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
const int mod=1e11+69;
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
        if(n&1) res=(__int128)res*a%mod;
        a=(__int128)a*a%mod;n>>=1;
    }
    return res;
}
const int iroot=power(3,mod-2);
const int base=101;

int n,k,h[maxn],p[maxn],c[maxn];
map<int,vector<int>> pos;

void solve(){
    cin >> n >> k;
    int st=1;
    for(int i=1;i<=k;i++){
        h[i]=rng()%(mod-1)+1;
        st=(__int128)st*h[i]%mod;
    }
    c[0]=1;
    for(int i=1;i<=n;i++){
        cin >> p[i];
        c[i]=(__int128)c[i-1]*h[p[i]]%mod;
        p[i]+=p[i-1];
    }
    for(int i=0;i<=n;i++) pos[p[i]%(k*(k+1)/2)].push_back(i);
    int ans=0;
    for(auto it:pos){
        map<int,int> mp;
        //cout << it.fi << '\n';
        for(int i:it.se){
            //cout << i << ' ';
            int num=p[i]/(k*(k+1)/2);
            int hh=(__int128)c[i]*power(power(st,num),mod-2)%mod;
            if(mp.find(hh)!=mp.end()) ans=max(ans,i-mp[hh]);
            else mp[hh]=i;
        }
        //cout << '\n';
    }
    cout << ans << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
