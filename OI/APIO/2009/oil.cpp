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
const int mod=998244353;
const int maxn=1505;
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

int n,m,K,res;
int c[maxn][maxn],s[4][maxn][maxn],d[2][maxn];

int query(int x,int y,int u,int v){
    return c[u][v]-c[x-1][v]-c[u][y-1]+c[x-1][y-1];
}

void solve(){
    cin >> n >> m >> K;
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++){
        cin >> c[i][j];
        c[i][j]+=c[i-1][j]+c[i][j-1]-c[i-1][j-1];
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            s[0][i][j]=max(s[0][i-1][j],s[0][i][j-1]);
            if(i>=K && j>=K) s[0][i][j]=max(s[0][i][j],query(i-K+1,j-K+1,i,j));
        }
        for(int j=m;j>=1;j--){
            s[1][i][j]=max(s[1][i-1][j],s[1][i][j+1]);
            if(i>=K && j+K-1<=m) s[1][i][j]=max(s[1][i][j],query(i-K+1,j,i,j+K-1));
        }
    }
    for(int i=n;i>=1;i--){
        for(int j=1;j<=m;j++){
            s[2][i][j]=max(s[2][i+1][j],s[2][i][j-1]);
            if(i+K-1<=n && j>=K) s[2][i][j]=max(s[2][i][j],query(i,j-K+1,i+K-1,j));
        }
        for(int j=m;j>=1;j--){
            s[3][i][j]=max(s[3][i+1][j],s[3][i][j+1]);
            if(i+K-1<=n && j+K-1<=m) s[3][i][j]=max(s[3][i][j],query(i,j,i+K-1,j+K-1));
        }
    }
    for(int i=K;i+K<=n;i++){
        for(int j=K;j+K<=m;j++){
            res=max(res,s[0][i][j]+s[1][i][j+1]+s[3][i+1][1]);
            res=max(res,s[2][i+1][j]+s[3][i+1][j+1]+s[0][i][m]);
            res=max(res,s[0][i][j]+s[2][i+1][j]+s[3][1][j+1]);
            res=max(res,s[1][i][j+1]+s[3][i+1][j+1]+s[0][n][j]);
        }
    }
    for(int i=1;i+K-1<=n;i++) for(int j=1;j+K-1<=m;j++){
        d[0][i]=max(d[0][i],query(i,j,i+K-1,j+K-1));
        d[1][j]=max(d[1][j],query(i,j,i+K-1,j+K-1));
    }
    for(int i=K;i+2*K<=n;i++){
        int val=0;
        for(int j=i+1;j+K<=n;j++){
            val=max(val,d[0][j]);
            res=max(res,s[0][i][m]+val+s[3][j+K][1]);
        }
    }
    for(int i=K;i+2*K<=m;i++){
        int val=0;
        for(int j=i+1;j+K<=m;j++){
            val=max(val,d[1][j]);
            res=max(res,s[0][n][i]+val+s[3][1][j+K]);
        }
    }
    cout << res << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}

