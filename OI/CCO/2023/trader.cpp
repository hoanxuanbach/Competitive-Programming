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

int n,k,a[maxn];
vector<int> edge[maxn];

namespace sub1{
    pii dist[maxn];
    void dfs(int u,int par){
        dist[u]={0,u};
        for(int v:edge[u]){
            if(v==par) continue;
            dfs(v,u);
            dist[u]=max(dist[u],{dist[v].fi,v});
        }
        dist[u].fi+=a[u];
    }
    void solve(){
        dfs(1,0);
        cout << dist[1].fi << '\n';
        vector<int> res;
        int u=1;res.push_back(u);
        while(dist[u].se!=u){
            u=dist[u].se;
            res.push_back(u);
        }
        cout << (int)res.size() << '\n';
        for(int v:res) cout << v << (v==res.back()?'\n':' ');
    }
}
namespace sub2{
    int dp[maxn][2][2];
    piii trace[maxn][2][2];
    vector<int> res;

    void dfs(int u,int par){
        int total=0;
        for(int v:edge[u]){
            if(v==par) continue;
            dfs(v,u);total+=a[v];
        }
        {//cur = u and jump back to par
            pii Max={0,0};
            for(int v:edge[u]){
                if(v==par) continue;
                Max=max(Max,{dp[v][1][1]+total,v});
            }
            dp[u][0][1]=Max.fi;
            trace[u][0][1]={Max.se,{0,0}};
        }
        {//cur = child of u and jump back to u
            pii Max={0,0};
            for(int v:edge[u]){
                if(v==par) continue;
                Max=max(Max,{dp[v][0][1]+total,v});
            }
            dp[u][1][1]=Max.fi;
            trace[u][1][1]={Max.se,{0,0}};
        }
        {//cur = u and not jump back
            piii Max={0,{0,0}};
            vector<pii> p1={{0,0}},p2={{0,0}};
            for(int v:edge[u]){
                if(v==par) continue;
                Max=max(Max,{dp[v][1][0]+a[v],{-1,v}});
                p1.push_back({dp[v][1][1],v});
                p2.push_back({dp[v][0][0],v});
            }
            sort(p1.begin(),p1.end(),greater<pii>());
            sort(p2.begin(),p2.end(),greater<pii>());
            for(int i=0;i<min(2LL,(int)p1.size());i++)
                for(int j=0;j<min(2LL,(int)p2.size());j++){
                    if(p2[j].se!=0 && p2[j].se==p1[i].se) continue;
                    Max=max(Max,{p1[i].fi+p2[j].fi+total,{p1[i].se,p2[j].se}});
                }
            dp[u][0][0]=Max.fi;
            trace[u][0][0]={Max.se.fi,{Max.se.se,0}};
        }
        {//cur = child of u and not jump back
            pair<int,piii> Max={0,{0,{0,0}}};
            {
                piii Max2={0,{0,0}};
                vector<pii> p1={{0,0}},p2={{0,0}};
                for(int v:edge[u]){
                    if(v==par) continue;
                    p1.push_back({dp[v][0][1],v});
                    p2.push_back({dp[v][1][0],v});
                }
                sort(p1.begin(),p1.end(),greater<pii>());
                sort(p2.begin(),p2.end(),greater<pii>());
                for(int i=0;i<min(2LL,(int)p1.size());i++)
                    for(int j=0;j<min(2LL,(int)p2.size());j++){
                        if(p2[j].se!=0 && p2[j].se==p1[i].se) continue;
                        Max2=max(Max2,{p1[i].fi+p2[j].fi+total,{p1[i].se,p2[j].se}});
                    }
                Max=max(Max,{Max2.fi,{-1,Max2.se}});
            }

            vector<pii> p1={{0,0}},p2={{0,0}},p3={{0,0}};
            for(int v:edge[u]){
                if(v==par) continue;
                p1.push_back({dp[v][0][1],v});
                p2.push_back({dp[v][1][1],v});
                p3.push_back({dp[v][0][0],v});
            }
            sort(p1.begin(),p1.end(),greater<pii>());
            sort(p2.begin(),p2.end(),greater<pii>());
            sort(p3.begin(),p3.end(),greater<pii>());
            for(int i=0;i<min(3LL,(int)p1.size());i++)
                for(int j=0;j<min(3LL,(int)p2.size());j++)
                    for(int k=0;k<min(3LL,(int)p3.size());k++){
                        if(p2[j].se!=0 && p2[j].se==p1[i].se) continue;
                        if(p3[k].se!=0 && (p3[k].se==p1[i].se || p3[k].se==p2[j].se)) continue;
                        Max=max(Max,{p1[i].fi+p2[j].fi+p3[k].fi+total,{p1[i].se,{p2[j].se,p3[k].se}}});
                    }
            dp[u][1][0]=Max.fi;
            trace[u][1][0]=Max.se;
        }
    }

    void f(int u,int par,int t1,int t2){
        if(!t1 && t2){
            res.push_back(u);
            if(trace[u][0][1].fi) f(trace[u][0][1].fi,u,1,1);
            for(int v:edge[u]){
                if(v==par) continue;
                if(v==trace[u][0][1].fi) continue;
                res.push_back(v);
            }
        }
        else if(t1 && t2){
            for(int v:edge[u]){
                if(v==par) continue;
                if(v==trace[u][1][1].fi) continue;
                res.push_back(v);
            }
            if(trace[u][1][1].fi) f(trace[u][1][1].fi,u,0,1);
            res.push_back(u);
        }
        else if(!t1 && !t2){
            res.push_back(u);
            if(trace[u][0][0].fi==-1){
                if(trace[u][0][0].se.fi) f(trace[u][0][0].se.fi,u,1,0);
                return;
            }
            if(trace[u][0][0].fi) f(trace[u][0][0].fi,u,1,1);
            for(int v:edge[u]){
                if(v==par) continue;
                if(v==trace[u][0][0].se.fi || v==trace[u][0][0].fi) continue;
                res.push_back(v);
            }
            if(trace[u][0][0].se.fi) f(trace[u][0][0].se.fi,u,0,0);
        }
        else{
            if(trace[u][1][0].fi==-1){
                for(int v:edge[u]){
                    if(v==par) continue;
                    if(v==trace[u][1][0].se.fi || v==trace[u][1][0].se.se) continue;
                    res.push_back(v);
                }
                if(trace[u][1][0].se.fi) f(trace[u][1][0].se.fi,u,0,1);
                res.push_back(u);
                if(trace[u][1][0].se.se) f(trace[u][1][0].se.se,u,1,0);
                return;
            }
            if(trace[u][1][0].fi) f(trace[u][1][0].fi,u,0,1);
            res.push_back(u);
            if(trace[u][1][0].se.fi) f(trace[u][1][0].se.fi,u,1,1);
            for(int v:edge[u]){
                if(v==par) continue;
                if(v==trace[u][1][0].fi || v==trace[u][1][0].se.fi || v==trace[u][1][0].se.se) continue;
                res.push_back(v);
            }
            if(trace[u][1][0].se.se) f(trace[u][1][0].se.se,u,0,0);
        }
    }

    void solve(){
        dfs(1,0);
        f(1,0,0,0);
        cout << dp[1][0][0]+a[1] << '\n';
        cout << (int)res.size() << '\n';
        for(int v:res) cout << v << (v==res.back()?'\n':' ');
    }
}
namespace sub3{
    vector<int> res;
    void dfs(int u,int par){
        res.push_back(u);
        for(int v:edge[u]){
            if(v==par) continue;
            for(int w:edge[v]){
                if(w==u) continue;
                dfs(w,v);
            }
            res.push_back(v);
        }
    }
    void solve(){
        int total=0;
        for(int i=1;i<=n;i++) total+=a[i];
        dfs(1,0);
        cout << total << '\n';
        cout << n << '\n';
        for(int v:res) cout << v << (v==res.back()?'\n':' ');
    }
}
void solve(){
    cin >> n >> k;
    for(int i=1;i<n;i++){
        int u,v;cin >> u >> v;
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    for(int i=1;i<=n;i++) cin >> a[i];
    if(k==1) sub1::solve();
    else if(k==2) sub2::solve();
    else sub3::solve();
}

signed main(){
    //freopen("E.INP","r",stdin);
    //freopen("E.OUT","w",stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();

}