
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
const int maxn=205;
const int bl=650;
const int maxs=105;
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

ld dp[maxn][maxn][maxn];

void solve(){
    int n;cin >> n;
    for(int i=0;i<=n;i++){
        for(int x=0;x<=i;x++){
            int y=i-x;
            for(int k=0;k<=y/2;k++){
                dp[x][y][k]=1;
                if(x && y){
                    if(k) dp[x][y][k]+=(ld)2*x/n*(ld)(2*k)/n*dp[x-1][y][k-1];
                    dp[x][y][k]+=(ld)2*x/n*(ld)(y-2*k)/n*dp[x-1][y][k];
                }
                if(x>=2) dp[x][y][k]+=(ld)x/n*(ld)(x-1)/n*dp[x-2][y+2][k+1];
                if(y>=2){
                    if(k>=2) dp[x][y][k]+=(ld)(2*k)/n*(ld)(2*k-2)/n*dp[x][y-2][k-2];
                    if(k) dp[x][y][k]+=(ld)(4*k)/n*(ld)(y-2*k)/n*dp[x][y-2][k-1];
                    dp[x][y][k]+=(ld)(y-2*k)/n*(ld)(y-2*k-1)/n*dp[x][y-2][k];
                }
                int cnt=(2*x*y+x*(x-1)+y*(y-1)-2*k);
                if(cnt==0) dp[x][y][k]=0;
                else dp[x][y][k]*=(ld)n*n/cnt;
                //cout << x << ' ' << y << ' ' << k << ' ' << dp[x][y][k] << '\n';
            }
        }
    }
    cout << setprecision(9) << fixed << dp[n][0][0] << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
