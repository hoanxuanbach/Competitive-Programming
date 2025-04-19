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
const int mod=1e9+7;
const int maxn=2005;
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

int fac[3*maxn],dfac[3*maxn],inv[3*maxn];
int C(int n,int k){
    if(k>n || k<0 || n<0) return 0;
    return fac[n]*dfac[k]%mod*dfac[n-k]%mod;
}
int P(int n,int k){
    if(k>n || k<0 || n<0) return 0;
    return fac[n]*dfac[n-k]%mod;
}

void combi(int n){
    fac[0]=1;
    for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;
    dfac[n]=power(fac[n],mod-2);
    for(int i=n;i>=1;i--){
        dfac[i-1]=dfac[i]*i%mod;
        inv[i]=dfac[i]*fac[i-1]%mod;
    }
}
/*
dp[i][j][k] first i columns position j and (k = vertical/horizontal)

0->0
dp[i][j][0] -> dp[i+1][0][0]+=dp[i][j][0]*P(sum[i+1],cnt[i+1]) if c[1][i+1] = 'o',
            -> dp[i+1][d][0]+=dp[i][j][0]*P(d-1,cnt[i+1]-1) if c[1][i+1] = 'x';

0->1
if c[1][i+1] = 'o' || cnt[i+1]==1) don't do anything
dp[i][j][0] -> (j<d<=sum[i]+1) g[i+1][d]+=dp[i][j][0]

if(cnt[i+1]==2) g[i+1][d] -> dp[i+1][d][1]+=g[i+1][d]*(sum[i+1]-d);
if(cnt[i+1]==3){
    1. g[i+1][d] -> dp[i+1][d+1][1]+=g[i+1][d]*d*(sum[i+1]-d-1)*2;
    2. g[i+1][d] -> dp[i+1][d][1]+=g[i+1][d]*P(sum[i+1]-d,2);
}

1->0
if c[1][i+1] = 'o' dp[i][j][1] -> dp[i+1][0][0]+=dp[i][j][1]*P(sum[i+1],cnt[i+1])
dp[i][j][1] -> (1<=d<=j) f[i+1][d]+=dp[i][j][1]

f[i+1][d] -> dp[i+1][d+cnt[i+1]-1][0]+=f[i+1][d]*P(d+cnt[i+1]-2,cnt[i+1]-1);

*/

int n,c[3][maxn],sum[maxn],cnt[maxn];
int dp[maxn][3*maxn][2],f[maxn][3*maxn],g[maxn][3*maxn];

void solve(){
    cin >> n;
    combi(3*n);
    for(int i=0;i<=2;i++) for(int j=1;j<=n;j++){
        char cc;cin >> cc;
        c[i][j]=(cc=='x');
        cnt[j]+=c[i][j];
    }

    bool check=true;
    if(c[0][1] || c[2][1] || c[0][n] || c[2][n]) check=false;
    for(int i=1;i<n;i++){
        if(c[0][i] && c[0][i+1]) check=false;
        if(c[2][i] && c[2][i+1]) check=false;
    }

    if(!check){
        cout << 0 << '\n';
        return;
    }

    for(int j=1;j<=n;j++){
        sum[j]=sum[j-1]+cnt[j];
        //cout << sum[j] << ' ' << cnt[j] << '\n';
    }
    dp[0][0][0]=1;
    for(int i=0;i<n;i++){
        {//0->0
            int total=0;
            for(int j=0;j<=sum[i];j++) total=(total+dp[i][j][0])%mod;
            if(c[1][i+1]){
                for(int j=1;j<=sum[i+1];j++) dp[i+1][j][0]=(dp[i+1][j][0]+total*P(j-1,cnt[i+1]-1))%mod;
            }
            else{
                total=total*P(sum[i+1],cnt[i+1])%mod;
                dp[i+1][0][0]=(dp[i+1][0][0]+total)%mod;
            }
        }
        if(c[1][i+1] && cnt[i+1]>1 && i){//0->1
            for(int j=0;j<=sum[i];j++) g[i+1][j+1]=(g[i+1][j+1]+dp[i][j][0])%mod;
            for(int j=1;j<=sum[i]+1;j++){
                g[i+1][j]=(g[i+1][j]+g[i+1][j-1])%mod;
                if(cnt[i+1]==2) dp[i+1][j][1]=(dp[i+1][j][1]+g[i+1][j]*(sum[i+1]-j))%mod;
                else{
                    dp[i+1][j+1][1]=(dp[i+1][j+1][1]+g[i+1][j]*j*(sum[i+1]-j-1)*2)%mod;
                    dp[i+1][j][1]=(dp[i+1][j][1]+g[i+1][j]*P(sum[i+1]-j,2))%mod;
                }
            }
        }
        {//1->0
            if(!c[1][i+1]){
                for(int j=0;j<=sum[i];j++) dp[i+1][0][0]=(dp[i+1][0][0]+dp[i][j][1]*P(sum[i+1],cnt[i+1]))%mod;
            }
            else{
                for(int j=0;j<=sum[i];j++) f[i+1][j]=(f[i+1][j]+dp[i][j][1])%mod;
                for(int j=sum[i];j>=1;j--){
                    f[i+1][j]=(f[i+1][j]+f[i+1][j+1])%mod;
                    dp[i+1][j+cnt[i+1]-1][0]=(dp[i+1][j+cnt[i+1]-1][0]+f[i+1][j]*P(j+cnt[i+1]-2,cnt[i+1]-1))%mod;
                    //if(i==2) cout << f[i+1][j] << ' ' << dp[i+1][j+cnt[i+1]-1][0] << '\n';
                }
            }
        }
        /*
        cout << '*' << i+1 << '\n';
        for(int j=0;j<=sum[i+1];j++) cout << dp[i+1][j][0] << ' ';
        cout << '\n';
        for(int j=0;j<=sum[i+1];j++) cout << dp[i+1][j][1] << ' ';
        cout << '\n';
        */
    }
    int res=0;
    for(int i=0;i<=sum[n];i++) res=(res+dp[n][i][0])%mod;
    cout << res << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
