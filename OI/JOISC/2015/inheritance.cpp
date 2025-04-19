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
const int base=101;
struct edge{
    int u,v,w,id;
    bool operator<(edge o){return w>o.w;}
};
void solve(){
    int n,m,k;cin >> n >> m >> k;
    vector<edge> e(m);
    vector<int> ans(m,0);
    vector<vector<int>> par(k+1,vector<int>(n+1,0));
    for(int i=1;i<=k;i++) for(int j=1;j<=n;j++) par[i][j]=j;
    for(int i=0;i<m;i++) cin >> e[i].u >> e[i].v >> e[i].w,e[i].id=i;
    sort(e.begin(),e.end());
    function<int(int,int)> findpar = [&](int x,int u){
        if(par[x][u]!=u) return par[x][u]=findpar(x,par[x][u]);
        return u;
    };
    for(edge x:e){
        int l=1,r=k,res=0;
        while(r>=l){
            int mid=(l+r)>>1;
            if(findpar(mid,x.u)!=findpar(mid,x.v)) res=mid,r=mid-1;
            else l=mid+1;
        }
        ans[x.id]=res;
        if(res) par[res][findpar(res,x.v)]=findpar(res,x.u);
    }
    for(auto x:ans) cout << x << '\n';
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}

