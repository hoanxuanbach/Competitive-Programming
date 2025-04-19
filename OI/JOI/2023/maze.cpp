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
const int maxn=200005;
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

int n,m,k;
int sx,sy,tx,ty;

void solve(){
    cin >> n >> m >> k >> sx >> sy >> tx >> ty;
    sx--;sy--;tx--;ty--;k=1-k;
    vector<vector<char>> c(n,vector<char>(m));
    for(int i=0;i<n;i++) for(int j=0;j<m;j++) cin >> c[i][j];
    vector<vector<array<int,3>>> d(n,vector<array<int,3>>(m,{inf,0,0}));
    vector<pii> q1,q2;

    auto add = [&](vector<pii> &q,int x,int y,int dd,int a,int b){
        if(x<0 || y<0 || x>=n || y>=m) return;
        if(d[x][y][0]<=dd) return;
        d[x][y]={dd,a,b};
        q.push_back({x,y});
    };
    auto add2 = [&](int x,int y,int dd){
        if(x<0 || y<0 || x>=n || y>=m) return;
        if(c[x][y]=='#') add(q2,x,y,dd+1,k,k);
        else add(q1,x,y,dd,0,0);
    };

    add(q1,sx,sy,0,0,0);
    while(!q1.empty()){
        for(int i=0;i<(int)q1.size();i++){
            auto [x,y]=q1[i];
            auto [dd,a,b]=d[x][y];
            if(b==0) continue;
            add(q1,x,y+1,dd,a,b+1);
            add(q1,x,y-1,dd,a,b+1);
        }
        for(int i=0;i<(int)q1.size();i++){
            auto [x,y]=q1[i];
            auto [dd,a,b]=d[x][y];
            if(a==0) continue;
            add(q1,x-1,y,dd,a+1,b);
            add(q1,x+1,y,dd,a+1,b);
        }
        for(int i=0;i<(int)q1.size();i++){
            auto [x,y]=q1[i];
            auto [dd,a,b]=d[x][y];
            add2(x-1,y,dd);
            add2(x+1,y,dd);
            add2(x,y-1,dd);
            add2(x,y+1,dd);
        }
        swap(q1,q2);
        q2.clear();
    }
    cout << d[tx][ty][0] << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
