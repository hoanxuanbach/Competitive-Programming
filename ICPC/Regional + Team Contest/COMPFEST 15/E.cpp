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
const int maxn=305;
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

int c[3][maxn],Min[3][maxn][maxn];
int dp[maxn][maxn][maxn],a[maxn],s[maxn],t[maxn];

void solve(){
    int n,q,total=0;cin >> n >> q;
    for(int i=1;i<=q;i++) cin >> a[i];
    c[0][0]=c[1][0]=c[2][0]=t[0]=1;
    a[0]=inf;
    for(int i=1;i<=q;i++){
        for(int j=0;j<3;j++) c[j][i]=c[j][i-1];
        int id;cin >> id;
        if(id==1){
            cin >> s[i] >> t[i];
            total+=abs(s[i]-t[i])*a[i];
        }
        else{int p;cin >> p;p--;c[p][i]^=1;}
    }
    memset(dp,-1,sizeof(dp));
    for(int k=0;k<3;k++){
        for(int i=0;i<=q;i++){
            Min[k][i][i]=(c[k][i]?a[i]:inf);
            for(int j=i+1;j<=q;j++) Min[k][i][j]=min(Min[k][i][j-1],(c[k][j]?a[j]:inf));
        }
    }
    auto cal = [&](int x,int y,int z,int val){
        if(dp[x][y][z]==-1) dp[x][y][z]=val;
        else dp[x][y][z]=min(dp[x][y][z],val);
    };
    auto update = [&](int x,int y,int z,int i,int val){
        if(val==-1) return;
        //cout << x << ' ' << y << ' ' << z << ' ' << i << ' ' << val << '\n';
        if(Min[0][x][i]!=inf && c[0][i]) cal(i,y,z,Min[0][x][i]*abs(s[i]-t[x])+val);
        if(Min[1][y][i]!=inf && c[1][i]) cal(x,i,z,Min[1][y][i]*abs(s[i]-t[y])+val);
        if(Min[2][z][i]!=inf && c[2][i]) cal(x,y,i,Min[2][z][i]*abs(s[i]-t[z])+val);
    };

    int p=0;
    dp[0][0][0]=0;
    for(int i=1;i<=q;i++){
        if(s[i]==0 && t[i]==0) continue;
        for(int f1=0;f1<=p;f1++){
            for(int f2=0;f2<=p;f2++){
                update(p,f1,f2,i,dp[p][f1][f2]);
                update(f1,p,f2,i,dp[f1][p][f2]);
                update(f1,f2,p,i,dp[f1][f2][p]);
            }
        }
        p=i;
    }
    int ans=inf;
    for(int f1=0;f1<=p;f1++){
        for(int f2=0;f2<=p;f2++){
            if(dp[p][f1][f2]!=-1) ans=min(ans,dp[p][f1][f2]);
            if(dp[f1][p][f2]!=-1) ans=min(ans,dp[f1][p][f2]);
            if(dp[f1][f2][p]!=-1) ans=min(ans,dp[f1][f2][p]);
        }
    }
    cout << total+ans << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();

}
