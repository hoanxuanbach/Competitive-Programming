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
const int mod=998244353;
const int maxn=200005;
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

map<pair<pii,pii>,int> mp;
int dp[maxn][2];
vector<int> edge[maxn];

void add(pii x,pii y,int id){
    if(x>y) swap(x,y);
    auto it=mp.find({x,y});
    if(it==mp.end()) mp[{x,y}]=id;
    else{
        edge[id].push_back(it->se);
        edge[it->se].push_back(id);
        it->se=-1;
    }
}
void dfs(int u,int par){
    for(int v:edge[u]){
        if(v==par) continue;
        dfs(v,u);dp[u][1]+=dp[v][0];
        dp[u][0]+=max(dp[v][0],dp[v][1]);
    }
}

void solve(){
    int n,total=0;cin >> n;
    for(int i=1;i<=n;i++){
        int x1,y1,x2,y2,x3,y3;cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
        dp[i][1]=abs(x1*y2-x2*y1+x2*y3-x3*y2+x3*y1-x1*y3);
        total+=dp[i][1];
        add({x1,y1},{x2,y2},i);
        add({x1,y1},{x3,y3},i);
        add({x2,y2},{x3,y3},i);
    }
    for(auto it:mp){
        if(it.se!=-1){
            dp[it.se][1]=0;
        }
    }
    dfs(1,0);
    int ans=total-max(dp[1][0],dp[1][1]);
    cout << ans/2;
    if(ans&1) cout << ".5\n";
    else cout << ".0\n";
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
