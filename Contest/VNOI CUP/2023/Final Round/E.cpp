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
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=500005;
const int maxl=20;
const int maxa=250000;
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
int fac[maxn],dfac[maxn];
int C(int k,int n){
    if(k>n || k<0 || n<0) return 0;
    return fac[n]*dfac[k]%mod*dfac[n-k]%mod;
}
void combi(int n){
    fac[0]=1;
    for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;
    dfac[n]=power(fac[n],mod-2);
    for(int i=n;i>=1;i--) dfac[i-1]=dfac[i]*i%mod;
}
int num[maxn],cnt[maxn],r[maxn][maxn],Min[maxn],f[maxn];
void solve(){
    int n,m,s;cin >> n >> m >> s;combi(n);
    for(int i=1;i<=n;i++) Min[i]=n+1;
    for(int i=1;i<m;i++) for(int j=1;j<=n;j++) cin >> r[i][j];
    for(int i=1;i<=n;i++) for(int j=1;j<m;j++) Min[r[j][i]]=min(Min[r[j][i]],i),cnt[i]+=!num[r[j][i]],num[r[j][i]]++;
    for(int i=1;i<=n;i++) cnt[i]+=cnt[i-1];
    for(int i=1;i<=n;i++){
        int k=s-cnt[i]-1,d=n-cnt[i]-1;
        for(int j=0;j<=k;j++) f[i]=(f[i]+C(j,i-1)*C(d-j,n-i))%mod;
        f[i]=f[i]*fac[cnt[i]]%mod*fac[d]%mod;
    }
    for(int i=1;i<=n;i++){
        int res=0,cur=Min[i],add=0;
        for(int j=1;j<cur;j++) res=(res+f[j])%mod;
        //j==Min[i](k+=1) -> (0 -> k)
        for(int j=0;j<=s-cnt[cur];j++) add=(add+C(j,cur-1)*C(n-cnt[cur]-j,n-cur))%mod;
        res=(res+add*fac[cnt[cur]-1]%mod*fac[n-cnt[cur]])%mod;
        //j>Min[i](d+=1) -> (0 -> k)C(t,Min[i])*C(d-t,n-Min[i]-1])
        add=0;
        for(int j=0;j<=s-cnt[cur];j++) add=(add+C(j,cur)*C(n-cnt[cur]-j,n-cur-1))%mod;
        add=add*(n-cur)%mod;
        res=(res+add*fac[cnt[cur]-1]%mod*fac[n-cnt[cur]])%mod;
        cout << res*dfac[n]%mod << ' ';
    }
    cout << '\n';
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
