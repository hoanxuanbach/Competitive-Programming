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

int n,m,d[maxn];
vector<pii> edge[maxn];

bool check[maxn];
int pos,low[maxn],num[maxn];
vector<int> st,ind;

void dfs(int u,int p){
    low[u]=num[u]=++pos;
    st.push_back(u);
    for(auto [v,w]:edge[u]){
        if(v==p) continue;
        if(!num[v]){
            dfs(v,u);
            low[u]=min(low[u],low[v]);
            if(low[v]>=num[u]){
                vector<int> cur={u};
                while(true){
                    int x=st.back();
                    st.pop_back();
                    cur.push_back(x);
                    if(x==v) break;
                }
                sort(cur.begin(),cur.end());
                if(cur[0]==1 && cur.back()==n) ind=cur;
            }
        }
        else low[u]=min(low[u],num[v]);
    }
}

map<int,int> mp[maxn];

void solve(){
    cin >> n >> m;
    for(int i=1;i<=m;i++){
        int u,v,w;cin >> u >> v >> w;
        edge[u].push_back({v,w});
        edge[v].push_back({u,w});
    }
    {
        for(int i=1;i<=n;i++) d[i]=inf;
        priority_queue<pii,vector<pii>,greater<pii>> pq;
        d[1]=0;pq.push({0,1});
        while(!pq.empty()){
            auto [dd,u]=pq.top();pq.pop();
            if(dd!=d[u]) continue;
            for(auto [v,w]:edge[u]) if(d[v]>dd+w) pq.push({d[v]=dd+w,v});
        }
        edge[1].push_back({n,d[n]});
        edge[n].push_back({1,d[n]});
    }
    dfs(1,0);
    auto add_edge = [&](int u,int v,int w){
        if(mp[u].count(v) && mp[u][v]!=w) mp[u][v]=-1;
        else mp[u][v]=w;
    };
    for(int u:ind) check[u]=true;
    for(int u:ind){
        for(auto [v,w]:edge[u]){
            if(check[v]) add_edge(u,v,w);
        }
    }
    queue<int> q;
    for(int u:ind) if((int)mp[u].size()<=2) q.push(u);
    while(!q.empty()){
        int u=q.front();q.pop();
        if(u==1 || u==n) continue;
        for(auto [v,w]:mp[u]) mp[v].erase(u);
        if((int)mp[u].size()==2){
            auto [a,b] = *mp[u].begin();
            auto [c,d] = *mp[u].rbegin();
            int val = ((~b && ~d)? b+d:-1);
            add_edge(a,c,val);
            add_edge(c,a,val);
        }
        for(auto [v,w]:mp[u]) if((int)mp[v].size()<=2) q.push(v);
        mp[u].clear();
    }
    bool res=!((int)mp[1].size()==1 && mp[1].count(n) && ~mp[1][n]);
    cout << res << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
