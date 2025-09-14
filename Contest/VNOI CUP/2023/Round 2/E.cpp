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
- insert(x)
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
#define fi first
#define se second
const int inf=1e18;
const int mod=1e9+7;
const int maxn=25;
const int bl=650;
const int maxs=650;
const int maxm=205;
const int maxq=500005;
const int maxl=20;
const int maxa=10000000;
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
int n,m,k;
bool ok[maxn][maxm],c[maxm];
vector<pii> f[maxm];
int dp[2][(1<<16)+5],Max[2][(1<<16)+5];
void solve(){
    cin >> n >> m >> k;
    bool sw=0;
    if(n>m) swap(m,n),sw=1;
    int ans=1,res=0;
    while(k--){
        int x,y;cin >> x >> y;x--;y--;
        if(sw) swap(x,y);
        for(int i=0;i<=min(x,m-1-y);i++) ok[x-i][y+i]=1;
        for(int i=0;i<=min(y,n-1-x);i++) ok[x+i][y-i]=1;
        c[y-x+n+1]=1;
        //for(int i=0;i<=min(x,y);i++) ok[x-i][y-i]=1;
        //for(int i=0;i<=min(m-1-y,n-1-x);i++) ok[x+i][y+i]=1;
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            //cout << ok[i][j] << ' ';
            f[j-i+n+1].push_back({(j+i)/2,ok[i][j]});
        }
        
        //cout << '\n';
    }
    for(int i=2;i<=n+m;i++) sort(f[i].begin(),f[i].end());
    for(int i=0;i<(1<<n);i++) Max[0][i]=-inf;
    dp[0][0]=1;Max[0][0]=0;
    int t=0;
    for(int i=2;i<=n+m;i+=2){
        int sz=(int)f[i-2].size(),cur=(int)f[i].size();t^=1;
        for(int j=0;j<(1<<n);j++) Max[t][j]=-inf;
        memset(dp[t],0,sizeof(dp[t]));
        int has=0;
        for(int j=0;j<cur;j++) has+=(1<<j)*f[i][j].se;
        for(int mask=0;mask<(1<<sz);mask++){
            int cmask=mask;
            if(Max[t^1][mask]==-inf) continue;
            if(sz!=0){
                if(f[i-2][0].fi>f[i][0].fi) cmask<<=1;
                else if(f[i-2][0].fi<f[i][0].fi){
                    if((int)f[i].size()==(int)f[i-2].size()-2) cmask&=((1<<((int)f[i-2].size()-1))-1);
                    cmask>>=1;
                }
            }
            //cout << mask << ' ' << cmask << '\n';
            if(cmask&has) continue;
            if(Max[t^1][mask]>Max[t][cmask]){
                Max[t][cmask]=Max[t^1][mask];
                dp[t][cmask]=dp[t^1][mask];
            }
            else if(Max[t^1][mask]==Max[t][cmask]) dp[t][cmask]=(dp[t][cmask]+dp[t^1][mask])%mod;
        }
        //cout << has << '\n';
        if(!c[i]){
            for(int mask=(1<<cur)-1;mask>=0;mask--){
                if(Max[t][mask]==-inf) continue;
                for(int p=0;p<cur;p++){
                    if((mask&(1<<p)) || (has&(1<<p))) continue;
                    int cmask=mask^(1<<p);
                    if(Max[t][mask]+1>Max[t][cmask]){
                        Max[t][cmask]=Max[t][mask]+1;
                        dp[t][cmask]=dp[t][mask];
                    }
                    else if(Max[t][mask]+1==Max[t][cmask]) dp[t][cmask]=(dp[t][cmask]+dp[t][mask])%mod;
                }
            }
        }
        //for(int mask=0;mask<(1<<cur);mask++) cout << '{' <<  Max[t][mask] << ' ' << dp[t][mask] << '}' << '\n';
        //cout << '\n';
    }
    int cMax=0,sum=0;
    for(int i=0;i<(1<<n);i++) cMax=max(cMax,Max[t][i]);
    for(int i=0;i<(1<<n);i++){
        if(cMax==Max[t][i]) sum=(sum+dp[t][i])%mod;
    }
    //cout << cMax << ' ' << sum << '\n';
    res+=cMax;ans=ans*sum%mod;
    t=0;
    for(int j=0;j<(1<<n);j++) Max[t][j]=-inf;
    memset(dp[t],0,sizeof(dp[t]));
    dp[0][0]=1;Max[0][0]=0;
    for(int i=3;i<=n+m;i+=2){
        int sz=(int)f[i-2].size(),cur=(int)f[i].size();t^=1;
        for(int j=0;j<(1<<n);j++) Max[t][j]=-inf;
        memset(dp[t],0,sizeof(dp[t]));
        int has=0;
        for(int j=0;j<cur;j++) has+=(1<<j)*f[i][j].se;
        for(int mask=0;mask<(1<<sz);mask++){
            int cmask=mask;
            if(Max[t^1][mask]==-inf) continue;
            if(sz!=0){
                if(f[i-2][0].fi>f[i][0].fi) cmask<<=1;
                else if(f[i-2][0].fi<f[i][0].fi){
                    if((int)f[i-2].size()-2==(int)f[i].size()) cmask&=((1<<((int)f[i-2].size()-1))-1);
                    cmask>>=1;
                }
            }
            if(cmask&has) continue;
            if(Max[t^1][mask]>Max[t][cmask]){
                Max[t][cmask]=Max[t^1][mask];
                dp[t][cmask]=dp[t^1][mask];
            }
            else if(Max[t^1][mask]==Max[t][cmask]) dp[t][cmask]=(dp[t][cmask]+dp[t^1][mask])%mod;
        }
        if(!c[i]){
            for(int mask=(1<<cur)-1;mask>=0;mask--){
                if(Max[t][mask]==-inf) continue;
                for(int p=0;p<cur;p++){
                    if((mask&(1<<p)) || (has&(1<<p))) continue;
                    int cmask=mask^(1<<p);
                    if(Max[t][mask]+1>Max[t][cmask]){
                        Max[t][cmask]=Max[t][mask]+1;
                        dp[t][cmask]=dp[t][mask];
                    }
                    else if(Max[t][mask]+1==Max[t][cmask]) dp[t][cmask]=(dp[t][cmask]+dp[t][mask])%mod;
                }
            }
        }
        //for(int mask=0;mask<(1<<cur);mask++) cout << Max[t][mask] << ' ';
        //cout << '\n';
    }
    cMax=0;sum=0;
    for(int i=0;i<(1<<n);i++) cMax=max(cMax,Max[t][i]);
    for(int i=0;i<(1<<n);i++){
        if(cMax==Max[t][i]) sum=(sum+dp[t][i])%mod;
    }
    //cout << cMax << ' ' << sum << '\n';
    res+=cMax;ans=ans*sum%mod;
    cout << res << ' ' << ans << '\n';
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
