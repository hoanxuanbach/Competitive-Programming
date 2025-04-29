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
const int maxn=305;
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

int n,m,c[maxn];
vector<pii> edge[maxn];
vector<int> in[maxn],out[maxn];

int d[maxn];
vector<int> g[maxn];

void add(vector<int> f,int val){
    for(int j=0;j<m;j++) f[j]=(f[j]+mod)%mod;
    for(int i=0;i<m;i++){
        if(f[i]){
            if(g[i].empty()){
                int w=power(f[i],mod-2);val=val*w%mod;
                for(int j=0;j<m;j++) f[j]=f[j]*w%mod;
                g[i]=f;d[i]=val;
                return;
            }
            else{
                int w=f[i];val=(val-d[i]*w%mod+mod)%mod;
                for(int j=0;j<m;j++) f[j]=(f[j]-g[i][j]*w%mod+mod)%mod;
            }
        }
    }
}

void cal(){
    vector<int> res(m,0);
    for(int i=m-1;i>=0;i--){
        if(g[i].empty()) continue;
        for(int j=i+1;j<m;j++) d[i]=(d[i]-res[j]*g[i][j]%mod+mod)%mod;
        //cout << g[i][i] << '\n';
        res[i]=d[i];
    }
    int ans=0;
    for(int i=0;i<m;i++){
        //cout << res[i] << '\n';
        ans=(ans+res[i]*res[i]%mod*c[i]%mod)%mod;
    }
    cout << ans << '\n';
}


void solve(){
    cin >> n >> m;
    for(int i=1;i<=n;i++){
        par[i]=i,edge[i].clear();
        out[i].clear();
        in[i].clear();
    }
    for(int i=0;i<m;i++) g[i].clear(),d[i]=0;
    vector<piii> e;
    for(int i=0;i<m;i++){
        int u,v;cin >> u >> v >> c[i];
        in[v].push_back(i);
        out[u].push_back(i);
        if(unions(u,v)){
            edge[u].push_back({v,i+1});
            edge[v].push_back({u,-i-1});
        }
        else{
            e.push_back({i,{u,v}});
        }
    }
    for(int i=1;i<n;i++){
        vector<int> f(m,0);
        for(int id:in[i]) f[id]=-1;
        for(int id:out[i]) f[id]=1;
        add(f,(i==1));
    }
    for(auto x:e){
        vector<int> f(m,0);
        function<bool(int,int)> dfs = [&](int u,int p){
            if(u==x.se.se) return true;
            for(auto [v,id]:edge[u]){
                if(v==p) continue;
                if(dfs(v,u)){
                    f[abs(id)-1]=(id<0?-1:1)*c[abs(id)-1];
                    return true;
                }
            }
            return false;
        };
        dfs(x.se.fi,0);
        f[x.fi]=-c[x.fi];
        add(f,0);
    }
    cal();
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}
