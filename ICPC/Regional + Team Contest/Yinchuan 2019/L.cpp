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
#include<bits/stdc++.h>
using namespace std;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_real_distribution<> pp(0.0,1.0);
#define int long long
#define ld long double
#define pii pair<int,int>
#define piii pair<int,pii>
#define fi first
#define se second
const int inf=1e18;
const int mod=998244353;
const int mod2=1e9+7;
const int maxn=20;
const int maxq=500005;
const int maxl=20;
const int maxa=1000005;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
int n,m,k,s[maxn],cnt,num[maxn][maxn],mk[maxn][maxn][2],dist[maxn][maxn],dp[(1<<18)+5];
pii pos[maxn];
string ss[maxn][maxn];

void solve(){
    cin >> n >> m >> k;
    string check;cnt=0;
    for(int i=1;i<=k;i++) check.push_back('-');
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin >> ss[i][j];
            if(ss[i][j]!=check){num[i][j]=cnt;pos[cnt++]={i,j};}
            else num[i][j]=-1;
        }
    }
    for(int i=0;i<=k;i++) cin >> s[i];
    for(int i=0;i<cnt;i++){
        for(int j=i+1;j<cnt;j++){
            int dif=0;
            for(int p=0;p<k;p++){
                if(ss[pos[i].first][pos[i].second][p]==ss[pos[j].first][pos[j].second][p]) dif++;
            }
            dist[i][j]=s[dif];
            mk[i][j][0]=mk[i][j][1]=0;
            for(int p=pos[i].first+1;p<pos[j].first;p++){
                if(num[p][pos[i].second]!=-1) mk[i][j][0]^=(1<<num[p][pos[i].second]);
            }
            for(int p=pos[i].first;p<pos[j].first;p++){
                if(num[p][pos[j].second]!=-1) mk[i][j][1]^=(1<<num[p][pos[j].second]);
            }
            if(pos[i].second>pos[j].second){
                for(int p=pos[i].second;p>pos[j].second;p--){
                    if(num[pos[j].first][p]!=-1) mk[i][j][0]^=(1<<num[pos[j].first][p]);
                }
                for(int p=pos[i].second-1;p>pos[j].second;p--){
                    if(num[pos[i].first][p]!=-1) mk[i][j][1]^=(1<<num[pos[i].first][p]);
                }
            }
            else{
                for(int p=pos[i].second;p<pos[j].second;p++){
                    if(num[pos[j].first][p]!=-1) mk[i][j][0]^=(1<<num[pos[j].first][p]);
                }
                for(int p=pos[i].second+1;p<pos[j].second;p++){
                    if(num[pos[i].first][p]!=-1) mk[i][j][1]^=(1<<num[pos[i].first][p]);
                }
            }
        }
    }
    dp[0]=0;
    for(int mask=1;mask<(1<<cnt);mask++){
        dp[mask]=0;
        for(int i=0;i<cnt;i++){
            if(((mask>>i)&1)==0) continue;
            for(int j=i+1;j<cnt;j++){
                if(((mask>>j)&1)==0) continue;
                if((mask&mk[i][j][0]) && (mask&mk[i][j][1])) continue;
                dp[mask]=max(dp[mask],dp[mask^(1<<i)^(1<<j)]+dist[i][j]);
            }
        }
    }
    cout << dp[(1<<cnt)-1] << '\n';
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}
