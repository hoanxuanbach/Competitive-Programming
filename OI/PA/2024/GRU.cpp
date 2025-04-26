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
const int mod=1e9+7;
const int maxn=3005;
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

int n,k,a[maxn];
int p[maxn][maxn];
int par[maxn*maxn],cnt[maxn*maxn][2];
int findpar(int u){
    if(u!=par[u]) return par[u]=findpar(par[u]);
    return u;
}


void solve(){
    cin >> n >> k;
    for(int i=1;i<=k;i++) for(int j=1;j<=n;j++) cin >> p[i][j];
    for(int i=1;i<=n*n;i++) par[i]=i;
    for(int t=0;t<40;t++){
        for(int i=1;i<=n;i++) a[i]=i;
        for(int i=1;i<=k;i++) if(rng()&1){
            for(int j=1;j<=n;j++) a[j]=p[i][a[j]];
        }
        for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) par[findpar((i-1)*n+j)]=findpar((a[i]-1)*n+a[j]);
    }
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) if(i!=j) cnt[findpar((i-1)*n+j)][i>j]++;
    int res=0;
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) if(i!=j && findpar((i-1)*n+j)==(i-1)*n+j){
        int a=cnt[(i-1)*n+j][0],b=cnt[(i-1)*n+j][1];
        res=(res+a*b%mod*power(a+b,mod-2))%mod;
    }
    cout << res << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
