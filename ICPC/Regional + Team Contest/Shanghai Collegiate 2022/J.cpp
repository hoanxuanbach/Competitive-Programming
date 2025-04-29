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

int n,m;
vector<pii> edge[maxn];

int del[maxn],low[maxn],num[maxn],pos;

int col[maxn],deg[maxn];
bool odd_cycle=false;
bool even_cycle=false;
bool has_path_3=false;
bool ok=true;
vector<int> ver;

void dfs(int u,int par){
    num[u]=low[u]=++pos;
    for(auto [v,id]:edge[u]){
        if(v==par) continue;
        if(!num[v]){
            dfs(v,u);
            low[u]=min(low[u],low[v]);
            if(low[v]>num[u]) del[id]=1;
        }
        else low[u]=min(low[u],num[v]);
    }
}

void dfs2(int u){
    ver.push_back(u);
    for(auto [v,id]:edge[u]){
        if(del[id]) continue;
        if(!col[v]){
            col[v]=col[u]^3;
            dfs2(v);
        }
        else if(col[v]!=(col[u]^3)) ok=false;
    }
}

int d[maxn],diameter;

void dfs3(int u){
    int Max=0;d[u]=1;
    for(auto [v,id]:edge[u]){
        if(d[v]) continue;
        dfs3(v);
        diameter=max(diameter,Max+d[v]);
        Max=max(Max,d[v]);
    }
    d[u]+=Max;
}

void solve(){
    cin  >> n >> m;
    for(int i=1;i<=m;i++){
        int u,v;cin >> u >> v;
        edge[u].push_back({v,i});
        edge[v].push_back({u,i});
    }
    if(n<=3){
        cout << -1 << '\n';
        return;
    }
    for(int i=1;i<=n;i++) if(!num[i]) dfs(i,0);

    for(int i=1;i<=n;i++){
        for(auto [v,id]:edge[i]) if(!del[id]) deg[i]++;
    }

    for(int i=1;i<=n;i++){
        if(!col[i]){
            ver.clear();
            ok=true;
            col[i]=1;
            dfs2(i);
            if(!ok){
                odd_cycle=true;
                bool ring=true;
                for(int v:ver) if(deg[v]!=2) ring=false;
                if(!ring) even_cycle=true;
                else{
                    int Max=0;
                    for(int v:ver) Max=(Max,(int)edge[v].size());
                    if(Max>2 || (int)ver.size()>3) has_path_3=true;
                }
            }
            else if((int)ver.size()>=4) even_cycle=true;
        }
    }
    if(!has_path_3){
        for(int i=1;i<=n;i++) if(!d[i]) dfs3(i);
        if(diameter>=3) has_path_3=true;
    }
    if(odd_cycle && even_cycle) cout << 0 << '\n';
    else if(even_cycle) cout << 1 << '\n';
    else if(odd_cycle){
        if(has_path_3) cout << 1 << '\n';
        else cout << 2 << '\n';
    }
    else{
        bool has_path_2=false;
        for(int i=1;i<=n;i++) if((int)edge[i].size()>=2) has_path_2=true;

        if(has_path_3) cout << 2 << '\n';
        else if(has_path_2){
            int Maxd=0;
            for(int i=1;i<=n;i++) Maxd=max(Maxd,(int)edge[i].size());
            if(Maxd>=3) cout << 2 << '\n';
            else cout << 3 << '\n';
        }
        else{
            if(m==0) cout << 5 << '\n';
            else if(m==1) cout << 4 << '\n';
            else cout << 3 << '\n';
        }
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
