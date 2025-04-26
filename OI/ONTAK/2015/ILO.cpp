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
const int maxn=105;
const int bl=650;
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
const int base=131;

const ld eps = 1e-12;

int n;
ld a[maxn][maxn];
vector<ld> g[maxn];
ld x[maxn],y[maxn],val[maxn];

void add(vector<ld> d,ld num){
    for(int i=0;i<n-1;i++){
        if(abs(d[i])>eps){
            if(g[i].empty()){
                g[i]=d;
                val[i]=num;
                return;
            }
            ld w=d[i]/g[i][i];num-=val[i]*w;
            for(int j=0;j<n-1;j++) d[j]-=g[i][j]*w;
        }
    }
}

void solve(){
    cin >> n;
    for(int i=0;i<n;i++) for(int j=0;j<n;j++) cin >> a[i][j];
    x[0]=1;y[0]=0;
    for(int i=1;i<n;i++) y[i]=a[0][i];
    for(int i=1;i<n;i++){
        for(int j=i+1;j<n;j++){
            vector<ld> cur(n-1,0);
            cur[i-1]=y[j];
            cur[j-1]=-y[i];
            add(cur,a[i][j]);
        }
    }
    for(int i=n-2;i>=0;i--){
        ld num=0;
        if(!g[i].empty()){
            num=val[i];
            for(int j=i+1;j<n-1;j++) num-=g[i][j]*x[j+1];
            num/=g[i][i];
        }
        x[i+1]=num;
    }
    for(int i=0;i<n;i++) cout << setprecision(20) << fixed << x[i] << ' ' << y[i] << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
