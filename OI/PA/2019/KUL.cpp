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
#define ld long double
#define pii pair<int,int>
#define piii pair<int,pii>
#define fi first
#define se second
const int mod=1e9+7;
const int maxn=10005;
const int bl=650;
const int maxs=650;
const int maxm=200005;
const int maxq=500005;
const int maxl=20;
const int maxa=1000000;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=1LL*res*a%mod;
        a=1LL*a*a%mod;n>>=1;
    }
    return res;
}
int fac[maxn],dfac[maxn],inv[maxn];
int C(int k,int n){
    return 1LL*fac[n]*dfac[k]%mod*dfac[n-k]%mod;
}
int n,a[3],c[4],total[maxn][2*maxn];
bitset<maxn> x[3];
void solve(){
    cin >> n;
    inv[1]=fac[0]=fac[1]=dfac[0]=dfac[1]=1;
    for(int i=2;i<=n;i++){
        fac[i]=1LL*fac[i-1]*i%mod;
        inv[i]=(mod-1LL*(mod/i)*inv[mod%i]%mod);
        dfac[i]=1LL*dfac[i-1]*inv[i]%mod;
    }
    for(int i=0;i<=2;i++){
        cin >> a[i];a[i]=n-1-a[i];
        for(int j=0;j<n;j++){char c;cin >> c;x[i][j]=(c-'0')^1;}
    }
    x[1]^=x[0];x[2]^=x[0];x[0]^=x[0];
    for(int i=0;i<n;i++) c[x[1][i]<<1|x[2][i]]++;
    for(int i=0;i<=c[0];i++){
        for(int j=0;j<=c[3];j++){
            int add=1LL*C(i,c[0])*C(j,c[3])%mod;
            total[i+j][i-j+c[3]]=add;
        }
    }
    for(int i=0;i<=c[0]+c[3];i++){
        for(int j=0;j<=c[0]+c[3];j++){
            if(i>=1) total[i][j]=(total[i][j]+total[i-1][j])%mod;
            if(j>=1) total[i][j]=(total[i][j]+total[i][j-1])%mod;
            if(i>=1 && j>=1) total[i][j]=(total[i][j]+mod-total[i-1][j-1])%mod;
        }
    }
    int ans=0;
    for(int i=0;i<=c[1];i++){
        for(int j=0;j<=c[2];j++){
            int add=1LL*C(i,c[1])*C(j,c[2])%mod;
            int Max=a[0]-i-j,Min=min(a[1]-i+j-c[2],a[2]+i-j-c[1]);
            if(Max<0 || Min<0) continue;
            Max=min(Max,c[0]+c[3]);Min=min(Min,c[0]+c[3]);
            ans=(ans+1LL*add*total[Max][Min]%mod)%mod;
        }
    }
    ans=(power(2,n)-ans+mod)%mod;
    cout << ans << '\n';
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
