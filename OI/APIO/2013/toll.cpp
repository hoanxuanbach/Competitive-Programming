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
const int maxn=300025;
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

int p[maxn],a[maxn];
int findpar(int u){return (p[u]<0?u:p[u]=findpar(p[u]));}
bool unions(int u,int v){
    u=findpar(u);v=findpar(v);
    if(u==v) return false;
    if(p[u]>p[v]) swap(p[u],p[v]);
    p[u]+=p[v];p[v]=u;
    return true;
}

void init(int n){
    for(int i=1;i<=n;i++) p[i]=-a[i];
}

int N,M,K;
int U[maxn],V[maxn],W[maxn];
vector<int> edge[25];
int par[25],val[25],cnt[25],dep[25];

void dfs(int u,int P){
    cnt[u]=-p[u];val[u]=inf;
    par[u]=P;dep[u]=dep[P]+1;
    for(int v:edge[u]) if(v!=P) dfs(v,u),cnt[u]+=cnt[v];
}

void solve(){
    cin >> N >> M >> K;
    for(int i=0;i<M;i++) cin >> U[i] >> V[i] >> W[i];
    for(int i=0;i<K;i++) cin >> U[M+i] >> V[M+i];
    for(int i=1;i<=N;i++) cin >> a[i];

    vector<int> ord(M);
    iota(ord.begin(),ord.end(),0);
    sort(ord.begin(),ord.end(),[&](int x,int y){return W[x]<W[y];});

    init(N);
    vector<int> cc,add;
    for(int i:ord) if(unions(U[i],V[i])) cc.push_back(i);
    swap(cc,ord);

    init(N);
    for(int i=0;i<K;i++) unions(U[M+i],V[M+i]);
    cc.clear();
    for(int i:ord){
        if(unions(U[i],V[i])) cc.push_back(i);
        else add.push_back(i);
    }
    init(N);
    for(int i:cc) unions(U[i],V[i]);

    vector<pii> x;
    for(int u=1;u<=N;u++) if(p[u]<0){
        x.push_back({u,-p[u]});
        //cout << u << ' ' << -p[u] << '\n';
    }
    auto get = [&](int u){
        u=findpar(u);
        for(int i=0;i<(int)x.size();i++) if(x[i].fi==u) return i+1;
        return -1LL;
    };
    int S=get(1);
    for(int i:add){
        U[i]=get(U[i]),V[i]=get(V[i]);
        //cout << i << ' ' << U[i] << ' ' << V[i] << '\n';
    }
    for(int i=0;i<K;i++){
        U[M+i]=get(U[M+i]),V[M+i]=get(V[M+i]);
        //cout << M+i << ' ' << U[M+i] << ' ' << V[M+i] << '\n';
    }
    N=(int)x.size();
    for(int i=0;i<N;i++) a[i+1]=x[i].se;

    int res=0;
    for(int mask=0;mask<(1<<K);mask++){
        init(N);
        bool check=true;
        for(int i=0;i<K;i++) if((mask>>i&1) && !unions(U[M+i],V[M+i])) check=false;
        if(!check) continue;
        cc.clear();ord.clear();
        for(int i:add){
            if(unions(U[i],V[i])) cc.push_back(i);
            else ord.push_back(i);
        }
        init(N);
        for(int i:cc) unions(U[i],V[i]);

        int rt=findpar(S);
        for(int i=1;i<=N;i++) edge[i].clear();
        for(int i=0;i<K;i++) if(mask>>i&1){
            int u=findpar(U[M+i]),v=findpar(V[M+i]);
            edge[u].push_back(v);
            edge[v].push_back(u);
        }
        dfs(rt,0);
        for(int i:ord){
            int u=findpar(U[i]),v=findpar(V[i]);
            if(dep[u]>dep[v]) swap(u,v);
            while(dep[v]>dep[u]) val[v]=min(val[v],W[i]),v=par[v];
            while(v!=u){
                val[v]=min(val[v],W[i]);
                val[u]=min(val[u],W[i]);
                u=par[u];v=par[v];
            }
        }
        int total=0;
        //cout << "mask: " << mask << '\n';
        for(int u=1;u<=N;u++) if(p[u]<0 && u!=rt){
            total+=cnt[u]*val[u];
            //cout << u << ' ' << cnt[u] << ' ' << val[u] << '\n';
        }
        //cout << total << '\n';
        res=max(res,total);
    }
    cout << res << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
/*
5 5 1
3 5 2
1 2 3
2 3 5
2 4 4
4 3 6
1 3
10 20 30 40 50
*/
