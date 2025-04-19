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
const int mod=1e9+7;
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
int n,m,a[maxn][maxn],c[maxn][maxn],s[maxn][maxn],x[maxn][maxn];
void solve(){
    cin >> n >> m;
    int Max=0,Min=inf;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++) cin >> a[i][j],Max=max(Max,a[i][j]),Min=min(Min,a[i][j]);
    }
    auto cal = [&](){
        for(int i=1;i<=n;i++){
            s[i][m+1]=3;
            for(int j=m;j>=1;j--) s[i][j]=c[i][j]&s[i][j+1];
            int cur=0,p=3;
            for(int j=0;j<=m;j++){
                cur|=x[i-1][j];
                x[i][j]=cur&((p&1) && (s[i][j+1]&2));
                p&=c[i][j+1];
            }
        }
        for(int i=0;i<=m;i++){
            if(x[n][i]) return true;
        }
        return false;
    };
    auto check = [&](int mid){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++) c[i][j]=(a[i][j]<=Min+mid)+2*(a[i][j]>=Max-mid);
        }

        bool ok=cal();
        for(int i=1;i<=n/2;i++){
            for(int j=1;j<=m;j++) swap(c[i][j],c[n+1-i][j]);
        }
        ok|=cal();
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++) c[i][j]^=((c[i][j]>=1 && c[i][j]<=2)*3);
        }
        ok|=cal();
        for(int i=1;i<=n/2;i++){
            for(int j=1;j<=m;j++) swap(c[i][j],c[n+1-i][j]);
        }
        ok|=cal();
        return ok;
    };
    for(int i=0;i<=m;i++) x[0][i]=1;
    int l=0,r=Max-Min;
    while(l<r){
        int mid=(l+r)>>1;
        if(check(mid)) r=mid;
        else l=mid+1;
    }
    cout << r << '\n';
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
