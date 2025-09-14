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
const long long inf=1e18;
const int mod=998244353;
const int maxn=200005;
const int B=650;
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
const int base=101;

int n,k;
int t,dp[2][15][15][3][2];

void solve(){
    cin >> n >> k;
    string s;cin >> s;
    for(char &c:s) c=char((c=='K')+'0');
    for(int i=0;i<=k;i++) for(int j=0;j<=k;j++) for(int d=0;d<=2;d++) for(int x=0;x<=1;x++) dp[t][i][j][d][x]=-inf;
    dp[t][0][0][1][0]=0;
    for(int p=0;p<n;p++){
        t^=1;
        for(int i=0;i<=k;i++) for(int j=0;j<=k;j++) for(int d=0;d<=2;d++) for(int x=0;x<=1;x++) dp[t][i][j][d][x]=-inf;
        for(int i=0;i<=k;i++) for(int j=0;j<=k;j++) for(int d=0;d<=2;d++) for(int x=0;x<=1;x++){
            int val=dp[t^1][i][j][d][x];
            if(val==-inf) continue;
            //cout << p << ' ' << i << ' ' << j << ' ' << d << ' ' << x << ' ' << val << '\n';
            for(int nx=0;nx<=1;nx++){
                int nval=val+(!x && nx && p),ni=i,nj=j,nd=d;
                nd+=(!x && nx && p)-(x && !nx && p);
                if(nx!=s[p]-'0') ni+=!nx,nj+=nx;
                //cout << ni << ' ' << nj << ' ' << nd << ' ' << nx << ' ' << nval << '\n';
                if(ni<=k && nj<=k && 0<=nd && nd<=2) dp[t][ni][nj][nd][nx]=max(dp[t][ni][nj][nd][nx],nval);
            }
        }
    }
    int res=-inf;
    for(int i=0;i<=k;i++){
        for(int j=0;j<=2;j++) for(int x=0;x<=1;x++){
            int val=dp[t][i][i][j][x];
            if(val==-inf) continue;
            //cout << i << ' ' << j << ' ' << x << ' ' << val << '\n';
            int a=val,b=val-(j-1);
            res=max(res,a*a-b*b);
        }
    }
    cout << res << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}
