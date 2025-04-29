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
const int maxn=105;
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

int dp[maxn][maxn][maxn];
int n,a[maxn],b[maxn];

string trace(int l,int r,int x){
    if(l>r) return "";
    string res;res+="S";
    for(int k=0;k<=r-l;k++){
        if(a[l]==b[x+k] && (dp[l+1][l+k][x]&dp[l+k+1][r][x+k+1])){
            res+=trace(l+1,l+k,x);
            res+="C";
            res+=trace(l+k+1,r,x+k+1);
            return res;
        }
    }
    return "";
}

void solve(){
    cin >> n;
    for(int i=1;i<=n;i++) cin >> a[i];
    for(int i=1;i<=n;i++) cin >> b[i];
    for(int i=1;i<=n+1;i++) for(int j=0;j<=n+1;j++) dp[i][i-1][j]=1;
    for(int len=1;len<=n;len++) for(int l=1;l<=n-len+1;l++){
        int r=l+len-1;
        for(int x=1;x<=n-len+1;x++){
            for(int k=0;k<len;k++){
                if(a[l]==b[x+k]) dp[l][r][x]|=(dp[l+1][l+k][x]&dp[l+k+1][r][x+k+1]);
            }
        }
    }
    if(dp[1][n][1]){
        cout << "YES\n";
        cout << trace(1,n,1) << '\n';
    }
    else cout << "NO\n";
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
