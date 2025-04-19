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
#define ld long double
#define pii pair<int,int>
#define piii pair<int,pii>
#define mpp make_pair
#define fi first
#define se second
const int inf=1e9;
const int mod=998244353;
const int maxn=505;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=25;
const int maxa=1000000;
const int root=3;
const int base=131;

int n,a[maxn],c[maxn],val[maxn],sum[maxn],Max=0;
bool f[maxn][maxn][maxn],g[maxn][maxn][maxn];

void cal(int x,int y,int z,int t){
    //cout << x << ' ' << y << ' ' << z << ' ' << t << '\n';
    Max=max(Max,sum[min(n,x+y+z+2)]-val[x+1]-val[x+y+2]);
    if(z && f[x][y][z]) return;
    if(!z && g[x][y][t]) return;
    int p1=x+1,p3=x+y+z+3;
    if(a[p1]==a[t] || c[p1]==c[t] || !t) cal(x+1+y,z,0,p1);
    if(a[p3]==a[t] || c[p3]==c[t] || !t) cal(x,y,z+1,p3);
    if(z) f[x][y][z]=true;
    else g[x][y][t]=true;
}

void solve(){
    cin >> n;
    for(int i=1;i<=n;i++) cin >> a[i] >> c[i] >> val[i],sum[i]=sum[i-1]+val[i];
    cal(0,0,0,0);
    cout << Max << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
