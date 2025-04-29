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
const int mod=998244353;
const int maxn=200005;
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
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}

const int iroot=power(3,mod-2);
const int base=101;


void solve(){
    int s,c;cin >> s >> c;
    int total=0,Max=0;
    if(s>c*(c+1)/2){
        total+=(s+c*(c+1)/2+1)*(s-c*(c+1)/2)/2;
        s=c*(c+1)/2;
    }
    for(int k=0;k<=s/(c+1);k++){
        int rx=min(c,s-k*(c+1)),lx=max(0LL,s-(k+1)*(c+1)+1);
        if(lx>rx) continue;
        //cout << lx << ' ' << rx << '\n';
        int d=(k+1)*c,p=k*(c+1),st=d*lx+p*d/2,en=(s+lx+p+1)*(s-lx-p)/2;
        //cout << st << ' ' << en << '\n';
        Max=max(Max,st+en);
        int dd=max(0LL,min(rx-lx,d-lx-p));
        Max=max(Max,st+en+dd*d-dd*(lx+p+dd+lx+p+1)/2);
    }
    cout << total+Max << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}
