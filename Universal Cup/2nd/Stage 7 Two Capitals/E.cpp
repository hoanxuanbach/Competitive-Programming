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
#define piii pair<pii,int>
#define mpp make_pair
#define fi first
#define se second
const int maxn=10005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=25;
const int maxa=1000000;
const int root=3;
const int base=131;

short int d[maxn][maxn],c[maxn][maxn];
int n;
vector<int> a[maxn];

void solve(){
    cin >> n;
    for(int i=1;i<=n;i++){
        a[i].assign(3,0);
        for(int &x:a[i]) cin >> x,x--;
    }
    for(int i=0;i<=n;i++){
        for(int j=0;j<=n-i;j++){
            int k=n-i-j,x=max({i,j,k});
            if(i==x) d[i][j]=0;
            else if(j==x) d[i][j]=1;
            else d[i][j]=2;
        }
    }

    auto check = [&](int i,int j){
        if(d[i+1][j]!=d[i][j]) return true;
        if(d[i][j+1]!=d[i][j]) return true;
        return false;
    };

    vector<pii> cur;
    for(int i=0;i<=n;i++){
        for(int j=0;j<=n;j++){
            if(check(i,j)) cur.push_back({i,j});
        }
    }

    for(int t=n;t>=1;t--){
        vector<pii> nxt;
        vector<piii> val;

        for(auto [i,j]:cur){
            int res=-1;
            for(int x:a[t]) if(d[i][j]==x || d[i+1][j]==x || d[i][j+1]==x){
                res=x;
                break;
            }
            val.push_back({{i,j},res});
            int pre=d[i][j];
            d[i][j]=res;
            if(i && c[i-1][j]!=t && check(i-1,j)) nxt.push_back({i-1,j}),c[i-1][j]=t;
            if(j && c[i][j-1]!=t && check(i,j-1)) nxt.push_back({i,j-1}),c[i][j-1]=t;
            if(c[i][j]!=t && check(i,j)) nxt.push_back({i,j}),c[i][j]=t;
            d[i][j]=pre;
        }
        for(auto [x,v]:val) d[x.fi][x.se]=v;
        swap(cur,nxt);
    }
    cout << d[0][0]+1 << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
