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
const int mod=1e6+3;
const int maxn=1000005;
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
 
int par[maxn],col[maxn],a[maxn];
 
int findpar(int u){
    if(u!=par[u]) return par[u]=findpar(par[u]);
    return u;
}
void unions(int u,int v){
    u=findpar(u);v=findpar(v);
    if(u==v) return;
    par[v]=u;
}
 
int dd[maxn][2];
 
int C(int k,int n){
    int res=1;
    for(int i=k+1;i<=n;i++) res=res*i%mod;
    for(int i=1;i<=n-k;i++) res=res*power(i,mod-2)%mod;
    return res;
}
 
void solve(){
    memset(col,-1,sizeof(col));
    int n,k;cin >> n >> k;
    for(int i=1;i<=n;i++) par[i]=i;
    for(int i=k;i<=n;i++) cin >> a[i];
    int ans=1;
    for(int i=k+1;i<=n;i++){
        int d=a[i]-a[i-1];
        if(d==0) unions(i-k,i);
        else if(d==1){
            if(col[i-k]==1) ans=0;
            col[i-k]=0;col[i]=1;
        }
        else{
            if(col[i-k]==0) ans=0;
            col[i-k]=1;col[i]=0;
        }
    }
    for(int i=1;i<=n;i++){
        if(col[i]!=-1) dd[findpar(i)][col[i]]=1;
    }
    for(int i=1;i<=n;i++){
        if(dd[i][0] && dd[i][1]) ans=0;
        int x=findpar(i);
        if(dd[x][0]) col[i]=0;
        else if(dd[x][1]) col[i]=1;
    }
    int cnt=a[k],num=0;
    for(int i=1;i<=k;i++){
        if(col[i]!=-1) cnt-=col[i];
        else num++;
    }
    if(cnt<0 || cnt>num) ans=0;
    if(!ans){
        cout << 0 << '\n';
        return;
    }
    cout << C(cnt,num) << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}