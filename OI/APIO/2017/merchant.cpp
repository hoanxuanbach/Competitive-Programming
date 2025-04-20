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
const int inf=1e9;
const int mod=998244353;
const int maxn=105;
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

int n,m,K,dist[maxn][maxn],d[maxn][maxn],dd[maxn][maxn];
int s[maxn][1005],b[maxn][1005];

void solve(){
    cin >> n >> m >> K;
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) dist[i][j]=inf;
    for(int i=1;i<=n;i++){
        for(int j=0;j<K;j++) cin >> b[i][j] >> s[i][j];
    }
    for(int i=1;i<=m;i++){
        int u,v,w;cin >> u >> v >> w;
        dist[u][v]=min(dist[u][v],w);
    }
    for(int k=1;k<=n;k++){
        for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) dist[i][j]=min(dist[i][j],dist[i][k]+dist[k][j]);
    }
    /*
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++) cout << dist[i][j] << ' ';
        cout << '\n';
    }
    */
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++){
        for(int k=0;k<K;k++) if(b[i][k]<s[j][k] && b[i][k]!=-1) d[i][j]=max(d[i][j],s[j][k]-b[i][k]);
    }
    /*
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++) cout << d[i][j] << ' ';
        cout << '\n';
    }
    */
    auto check = [&](int mid){
        for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) dd[i][j]=d[i][j]-dist[i][j]*mid;
        /*
        cout << mid << '\n';
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++) cout << dd[i][j] << ' ';
            cout << '\n';
        }
        */
        for(int k=1;k<=n;k++){
            for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) dd[i][j]=max(dd[i][j],dd[i][k]+dd[k][j]);
        }
        for(int i=1;i<=n;i++) if(dd[i][i]>=0) return true;
        return false;
    };
    int l=1,r=inf,res=0;
    while(r>=l){
        int mid=(l+r)>>1;
        if(check(mid)) res=mid,l=mid+1;
        else r=mid-1;
    }
    cout << res << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
