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
const int maxn=500005;
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
const int base=101;

int n,L,d[2][maxn];
int cnt[maxn],pre[2][maxn],pos[maxn];
int dp[2005][2005][2];

void solve(){
    cin >> n >> L;
    vector<int> com;
    int N=n;
    for(int i=1;i<=n;i++){
        int x;cin >> x;cnt[x]++;
        com.push_back(x);
    }
    for(int i=0;i<=L;i++) pre[0][i]=(i?pre[0][i-1]:0)+cnt[i];
    for(int i=L;i>=0;i--) pre[1][i]=pre[1][i+1]+cnt[i];
    sort(com.begin(),com.end());
    com.erase(unique(com.begin(),com.end()),com.end());
    for(int i=0;i<(int)com.size();i++) pos[com[i]]=i+1;
    n=(int)com.size();
    if(n<=2000){
        for(int t=0;t<=1;t++){
            for(int l=0;l<n;l++) for(int r=l;r<n;r++) for(int k=0;k<=1;k++) dp[l][r][k]=inf;
            dp[0][n-1][t]=0;
            for(int len=n;len>1;len--){
                for(int l=0;l<=n-len;l++){
                    int r=l+len-1;
                    if(dp[l][r][0]!=inf){
                        int num=pre[0][com[l]]+pre[1][com[r]+1]+1;
                        dp[l+1][r][0]=min(dp[l+1][r][0],dp[l][r][0]+num*(com[l+1]-com[l]));
                        dp[l+1][r][1]=min(dp[l+1][r][1],dp[l][r][0]+num*(com[r]-com[l]));
                    }
                    if(dp[l][r][1]!=inf){
                        int num=(com[l]?pre[0][com[l]-1]:0)+pre[1][com[r]]+1;
                        dp[l][r-1][0]=min(dp[l][r-1][0],dp[l][r][1]+num*(com[r]-com[l]));
                        dp[l][r-1][1]=min(dp[l][r-1][1],dp[l][r][1]+num*(com[r]-com[r-1]));
                    }
                }
            }
            int Min=inf;
            for(int i=0;i<=L;i++){
                Min+=(N+1);
                if(pos[i]){
                    int p=pos[i]-1;
                    Min=min({Min,dp[p][p][0],dp[p][p][1]});
                }
                d[t][i]=Min;
            }
            Min=inf;
            for(int i=L;i>=0;i--){
                Min+=(N+1);
                if(pos[i]){
                    int p=pos[i]-1;
                    Min=min({Min,dp[p][p][0],dp[p][p][1]});
                }
                d[t][i]=min(d[t][i],Min);
            }
            //cout << dp[0][0][0] << ' ' << dp[0][0][1] << ' ' << dp[1][1][0] << ' ' << dp[1][1][1] << '\n';
        }
    }
    //cout << d[0][100] << ' ' << d[1][100] << '\n';
    int q;cin >> q;
    for(int i=1;i<=q;i++){
        int s,g,t;cin >> s >> g >> t;
        //cout << d[0][g] << ' ' << d[1][g] << '\n';
        int k=min(d[0][g]+abs(com[0]-s),d[1][g]+abs(com.back()-s))+N;
        cout << ((k<=t && n<=2000)?"Yes":"No") << '\n';
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
