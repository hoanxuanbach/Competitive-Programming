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
//#define int long long
#define ld long double
#define pii pair<int,int>
#define piii pair<pii,int>
#define mpp make_pair
#define fi first
#define se second
//const int inf=1e18;
const int mod=1e9+7;
const int maxn=1005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=500005;
const int maxl=20;
const int maxa=250000;
const int root=3;
/*
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
const int iroot=power(3,mod-2);
*/
int dx[]={0,0,1,-1},
    dy[]={1,-1,0,0};

const int base=101;
int n,m,c[maxn][maxn],s[2*maxn];
bool check(int x,int y){
    if((x==n && y==m) || (x==1 && y==1)) return false;
    if((x==n || c[x+1][y]) && (y==m || c[x][y+1])) return true;
    if((x==1 || c[x-1][y]) && (y==1 || c[x][y-1])) return true;
    return false;
}
void del(int u,int v){
    c[u][v]=1;s[u+v]--;
    for(int t=0;t<4;t++){
        int x=u+dx[t],y=v+dy[t];
        if(x<=0 || y<=0 || x>n || y>m || c[x][y]) continue;
        if(check(x,y)) del(x,y);
    }
}
void solve(){
    cin >> n >> m;
    int cc;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            s[i+j]++;
            if(c[i][j]){cin >> cc;continue;}
            cin >> c[i][j];
            if(c[i][j]) del(i,j);
        }
    }
    int q;cin >> q;
    for(int i=1;i<=q;i++){
        int x,y;cin >> x >> y;
        if(c[x][y]) cout << 1 << '\n';
        else if(s[x+y]==1) cout << 0 << '\n';
        else{
            del(x,y);
            cout << 1 << '\n';
        }
    }
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}

