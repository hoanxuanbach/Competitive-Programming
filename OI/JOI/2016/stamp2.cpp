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

int n,s[maxn],pre[maxn][5],suf[maxn][5];
int cn[256];

void solve(){
    cin >> n;
    cn['J']=1;cn['O']=2;cn['I']=3;
    for(int i=1;i<=n;i++){
        char c;cin >> c;
        s[i]=cn[c];
    }
    int Max=0;
    pre[0][0]=1;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=3;j++) pre[i][j]=pre[i-1][j];
        pre[i][s[i]]+=pre[i-1][s[i]-1];
    }
    suf[n+1][4]=1;
    for(int i=n;i>=1;i--){
        for(int j=1;j<=4;j++) suf[i][j]+=suf[i+1][j];
        suf[i][s[i]]+=suf[i+1][s[i]+1];
    }
    for(int i=0;i<=n;i++){
        for(int j=0;j<=2;j++) Max=max(Max,pre[i][j]*suf[i+1][j+2]);
    }
    cout << pre[n][3]+Max << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
