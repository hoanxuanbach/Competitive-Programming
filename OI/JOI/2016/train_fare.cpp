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

int n,m,Q,R[maxn],U[maxn],V[maxn];
int d[2][maxn];
int check[maxn],res[maxn];
vector<pii> edge[maxn];

void bfs(int t){
    for(int i=1;i<=n;i++) d[t][i]=-1;
    queue<int> q;q.push(1);d[t][1]=0;
    while(!q.empty()){
        int u=q.front();q.pop();
        for(auto [v,id]:edge[u]){
            if(check[id]>t) continue;
            if(d[t][v]==-1){
                d[t][v]=d[t][u]+1;
                q.push(v);
            }
        }
    }
}

void solve(){
    cin >> n >> m >> Q;
    for(int i=1;i<=m;i++){
        cin >> U[i] >> V[i];
        edge[U[i]].push_back({V[i],i});
        edge[V[i]].push_back({U[i],i});
    }
    for(int i=1;i<=Q;i++){
        cin >> R[i];
        check[R[i]]=1;
    }
    int cnt=0;
    bfs(1);bfs(0);
    for(int i=1;i<=n;i++){
        //cout << d[0][i] << ' ' << d[1][i] << '\n';
        if(d[0][i]==d[1][i]) cnt++;
        vector<pii> adj;
        for(auto [v,id]:edge[i]){
            if(check[id]) continue;
            if(d[1][v]==d[1][i]+1) adj.push_back({v,id});
        }
        swap(edge[i],adj);
    }
    for(int i=Q;i>=1;i--){
        res[i]=n-cnt;
        int u=U[R[i]],v=V[R[i]];
        if(d[1][u]>d[1][v]) swap(u,v);
        if(d[1][v]!=d[1][u]+1) continue;
        edge[u].push_back({v,R[i]});
        if(d[0][u]!=d[1][u] || d[0][v]==d[1][v]) continue;
        function<void(int)> bfs2 = [&](int s){
            queue<int> q;q.push(s);
            d[0][s]=d[1][s];cnt++;
            while(!q.empty()){
                int x=q.front();q.pop();
                for(auto [v,id]:edge[x]){
                    if(d[0][v]!=d[1][v]){
                        d[0][v]=d[1][v];
                        q.push(v);cnt++;
                    }
                }
            }
        };
        bfs2(v);
    }
    for(int i=1;i<=Q;i++) cout << res[i] << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
