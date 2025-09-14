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
const int maxn=200005;
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


int n,m,k,s[15],pos[15];
vector<piii> e[15];

int par[maxn];
int findpar(int u){
    if(u!=par[u]) return par[u]=findpar(par[u]);
    return u;
}
bool unions(int u,int v){
    u=findpar(u);v=findpar(v);
    if(u==v) return false;
    return par[v]=u,true;
}
void init(){
    for(int i=1;i<=n;i++) par[i]=i;
}


void solve(){
    cin >> n >> m >> k;
    for(int i=0;i<k;i++) e[i].clear();
    for(int i=1;i<=m;i++){
        int u,v,c,w;cin >> u >> v >> c >> w;
        e[c-1].push_back({w,{u,v}});
    }
    for(int i=0;i<k;i++) cin >> s[i];
    for(int i=0;i<k;i++){
        sort(e[i].begin(),e[i].end());
        init();
        vector<piii> nw;
        for(auto x:e[i]) if(unions(x.se.fi,x.se.se)) nw.push_back(x);
        swap(e[i],nw);
    }
    int res=inf;
    for(int mask=0;mask<(1<<k);mask++){
        int total=0;
        for(int i=0;i<k;i++) if(mask>>i&1) total+=s[i];
        priority_queue<pii,vector<pii>,greater<pii>> pq;
        for(int i=0;i<k;i++){
            pos[i]=0;
            if(!e[i].empty()) pq.push({e[i][pos[i]].fi*(1+!(mask>>i&1)),i});
        }
        int cnt=0;
        init();
        while(cnt<n-1){
            int i=pq.top().se;pq.pop();
            bool check=unions(e[i][pos[i]].se.fi,e[i][pos[i]].se.se);
            if(check) cnt++,total+=e[i][pos[i]].fi*(1+!(mask>>i&1));
            pos[i]++;
            if(pos[i]<(int)e[i].size()) pq.push({e[i][pos[i]].fi*(1+!(mask>>i&1)),i});
        }
        res=min(res,total);
    }
    cout << res << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}
