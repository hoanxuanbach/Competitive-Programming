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

int n,m,dp[maxn],dep[maxn],c[maxn],res[maxn];
vector<int> edge[maxn];

void solve(){
    cin >> n >> m;
    for(int i=1;i<n;i++){
        int u,v;cin >> u >> v;
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    for(int i=1;i<=n;i++) cin >> c[i];
    int root=1;
    for(int i=0;i<=1;i++){
        int x=1;
        function<void(int,int)> dfs = [&](int u,int p){
            dp[u]=dep[u]=dep[p]+1;
            if(dep[u]>dep[x]) x=u;
            for(int v:edge[u]) if(v!=p) dfs(v,u),dp[u]=max(dp[u],dp[v]);
        };
        dfs(root,0);
        //cout << '*' << x << '\n';
        root=x;
        dfs(root,0);

        int cnt=0;
        vector<int> d(m+1,0);
        vector<int> cur;
        auto add = [&](int u){
            //cout << "add " << u << '\n';
            cur.push_back(u);
            cnt+=(!d[c[u]]);
            d[c[u]]++;
        };
        auto del = [&](int u){
            //cout << "del " << u << '\n';
            d[c[u]]--;
            cnt-=(!d[c[u]]);
            cur.pop_back();
        };
        function<void(int,int)> dfs2 = [&](int u,int p){
            //cout << u << '\n';
            if(p) add(p);
            vector<int> cc;
            for(int v:edge[u]) if(v!=p) cc.push_back(v);
            sort(cc.begin(),cc.end(),[](int a,int b){
                return dp[a]>dp[b];
            });
            for(int v:cc){
                if(v==p) continue;
                int d2=(v!=cc[0]?dp[cc[0]]:((int)cc.size()<=1?0:dp[cc[1]]));
                while(!cur.empty() && dep[u]-dep[cur.back()]<=d2-dep[u]) del(cur.back());
                dfs2(v,u);
            }
            while(!cur.empty() && dep[u]-dep[cur.back()]<=dp[u]-dep[u]) del(cur.back());
            //cout << u << ' ' << cnt << '\n';
            res[u]=max(res[u],cnt);
        };
        dfs2(root,0);
    }
    for(int i=1;i<=n;i++) cout << res[i] << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
