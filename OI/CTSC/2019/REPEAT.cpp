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
const int maxn=2005;
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

string s;
int n,m,mx[maxn],dp[maxn][maxn];
int kmp[maxn],nxt[maxn][30];

void solve(){
    cin >> m >> s;
    n=(int)s.length();s="#"+s;
    kmp[0]=-1;
    for(int i=2;i<=n;i++){
        int j=kmp[i-1];
        while(j>=0 && s[j+1]!=s[i]) j=kmp[j];
        kmp[i]=j+1;
    }
    for(int i=0;i<=n;i++){
        for(int j=1;j<=26;j++){
            if(i+1<=n && (s[i+1]-'a'+1)==j) nxt[i][j]=i+1;
            else nxt[i][j]=(i?nxt[kmp[i]][j]:0);
            if(nxt[i][j]) mx[i]=j;
            //cout << nxt[i][j] << ' ';
        }
        //cout << '\n';
    }
    dp[0][0]=1;
    for(int i=0;i<m;i++){
        for(int j=0;j<=n;j++){
            //cout << dp[i][j] << ' ';
            for(int k=mx[j];k<=26;k++) dp[i+1][nxt[j][k]]=(dp[i+1][nxt[j][k]]+dp[i][j])%mod;
        }
        //cout << '\n';
    }
    int total=power(26,m),cnt=0;
    for(int i=0;i<=n;i++){
        int u=i;
        for(int j=1;j<=m;j++){
            cnt=(cnt+(26-mx[u])*dp[m-j][i])%mod;
            u=nxt[u][mx[u]];
            if(!u){
                u=-1;
                break;
            }
        }
        if(u==i) cnt=(cnt+1)%mod;
    }
    //cout << total << ' ' << cnt << '\n';
    total=(total-cnt+mod)%mod;
    cout << total << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
