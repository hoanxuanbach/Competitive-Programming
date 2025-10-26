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
const int mod=1e12+169;
const int maxn=2000005;
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
const int base=998244353;

int n,a[maxn],h[maxn],pw[maxn];
int F[305];

void solve(){
    cin >> n;
    for(int i=1;i<=n;i++){
        string s;cin >> s;
        for(char c:s) a[i]=a[i]*62+F[c];
    }
    pw[0]=1;
    for(int i=1;i<=n;i++){
        pw[i]=(__int128)pw[i-1]*base%mod;
        h[i]=((__int128)h[i-1]*base+a[i])%mod;
    }
    auto get = [&](int l,int r){
        return (h[r]-(__int128)h[l-1]*pw[r-l+1]%mod+mod)%mod;
    };
    int k=1;
    for(int i=1;i<=n;i++){
        while(k<=(i-1)/2){
            int a=get(1,i-2*k),b=get(k+1,i-k),c=get(2*k+1,i);
            if((a+c-2*b%mod+mod)%mod!=0) k++;
            else break;
        }
        if(k>(i-1)/2) cout << 0;
        else cout << 1;
    }
    cout << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    for(int i=0;i<10;i++) F['0'+i]=i;
    for(int i=0;i<26;i++) F['a'+i]=10+i;
    for(int i=0;i<26;i++) F['A'+i]=36+i;
    int test=1;//cin >> test;
    while(test--) solve();
}

