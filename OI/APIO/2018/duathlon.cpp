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
- insert(x)
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
#define fi first
#define se second
const int inf=1e18;
const int mod=1e9+7;
const int maxn=200005;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
int n,m,sz,pos,num[maxn],low[maxn];
vector<int> edge[maxn],adj[maxn],st;
int cnt[maxn],sum[maxn],cur,ans;
void add_edge(int u,int v){
    adj[u].push_back(v);
    adj[v].push_back(u);
    //cout << u << ' ' << v << '\n';
}
void dfs(int u,int par){
    low[u]=num[u]=++pos;
    st.push_back(u);
    for(int v:edge[u]){
        if(v==par) continue;
        if(!num[v]){
            dfs(v,u);
            low[u]=min(low[u],low[v]);
            if(low[v]>=num[u]){
                sz++;
                while(st.back()!=v){
                    add_edge(st.back(),sz);
                    st.pop_back();
                }
                add_edge(v,sz);st.pop_back();
                add_edge(u,sz);
            }
        }
        else low[u]=min(low[u],num[v]);
    }
}
bool vis[maxn];
void dfs_sz(int u,int par){
    cur+=cnt[u];
    for(int v:adj[u]){
        if(v==par) continue;
        dfs_sz(v,u);
    }
}
void dfs_cal(int u,int par){
    vis[u]=true;sum[u]=cnt[u];
    int mul=(u<=n?1:(int)adj[u].size()-2),total=(cur-cnt[u])*(cur-cnt[u]);
    for(int v:adj[u]){
        if(v==par) continue;
        dfs_cal(v,u);sum[u]+=sum[v];
        total-=sum[v]*sum[v];
    }
    total-=(cur-sum[u])*(cur-sum[u]);
    ans+=mul*total;
    //cout << u << ' ' << sum[u] << '\n';
    //if(u>n){cout << u << ' ' << mul+2 << ' ' << total << '\n';}
}
void solve(){
    cin >> n >> m;sz=n;
    for(int i=1;i<=m;i++){
        int u,v;cin >> u >> v;
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    for(int i=1;i<=n;i++){
        cnt[i]=1;
        if(!num[i]){
            dfs(i,0);sz++;
            while(!st.empty()){add_edge(st.back(),sz);st.pop_back();}
        }
    }
    for(int i=1;i<=sz;i++){
        if(!vis[i]){
            cur=0;
            dfs_sz(i,0);
            //cout << cur << '\n';
            dfs_cal(i,0);
        }
    }
    cout << ans << '\n';
}
signed main(){
    //freopen("test_input.txt","r",stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
