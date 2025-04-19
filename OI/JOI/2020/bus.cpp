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
#define piii pair<pii,int>
#define mpp make_pair
#define fi first
#define se second
const int inf=1e9;
const int mod=1e9+7;
const int maxn=205;
const int bl=650;
const int maxs=655;
const int maxm=50005;
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
struct ed{
    int u,v,c,d;
};

int n,m,dist[maxn],trace[maxn];
vector<pii> edge[maxn];
bool check[maxm];
ed e[maxm];
void del(int u,int v,int id){
    for(int i=0;i<(int)edge[u].size();i++){
        if(edge[u][i]==mpp(v,id)){
            edge[u].erase(edge[u].begin()+i);
            return;
        }
    }
}
void add(int u,int v,int id){
    edge[u].push_back({v,id});
}
int dijisktra(int s,int t){
    for(int i=1;i<=n;i++) dist[i]=inf,trace[i]=0;
    priority_queue<pii,vector<pii>,greater<pii>> pq;
    dist[s]=0;pq.push({0,s});
    while(!pq.empty()){
        auto [d,u]=pq.top();pq.pop();
        if(u==t) return d;
        if(d!=dist[u]) continue;
        for(auto &[v,id]:edge[u]){
            if(d+e[id].c<dist[v]){
                dist[v]=d+e[id].c;trace[v]=id;
                pq.push({dist[v],v});
            }
        }
    }
    return inf;
}
int d[maxn][maxn];
void solve(){
    cin >> n >> m;
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) d[i][j]=inf*(i!=j);
    for(int i=1;i<=m;i++){
        cin >> e[i].u >> e[i].v >> e[i].c >> e[i].d;
        add(e[i].u,e[i].v,i);
        d[e[i].u][e[i].v]=min(d[e[i].u][e[i].v],e[i].c);
    }
    for(int k=1;k<=n;k++) for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) d[i][j]=min(d[i][j],d[i][k]+d[k][j]);
    int res=dijisktra(1,n);
    int cur=n;
    while(trace[cur]){
        int id=trace[cur];check[id]=true;
        cur=(e[id].u==cur?e[id].v:e[id].u);
    }
    res+=dijisktra(n,1);
    cur=1;
    while(trace[cur]){
        int id=trace[cur];check[id]=true;
        cur=(e[id].u==cur?e[id].v:e[id].u);
    }
    if(res>=inf) res=2*inf;
    /*
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++) cout << d[i][j] << ' ';
        cout << '\n';
    }
    */
    for(int i=1;i<=m;i++){
        //cout << i << ' ' << check[i] << '\n';
        if(check[i]){
            del(e[i].u,e[i].v,i);
            add(e[i].v,e[i].u,i);
            int d1=dijisktra(1,n),d2=dijisktra(n,1);
            if(d1<inf && d2<inf) res=min(res,d1+d2+e[i].d);
            del(e[i].v,e[i].u,i);
            add(e[i].u,e[i].v,i);
        }
        else{
            int d1=min(d[1][n],d[1][e[i].v]+e[i].c+d[e[i].u][n]);
            int d2=min(d[n][1],d[n][e[i].v]+e[i].c+d[e[i].u][1]);
            //cout << i << ' ' << d1 << ' ' << d2 << '\n';
            if(d1<inf && d2<inf) res=min(res,d1+d2+e[i].d);
        }
    }
    cout << (res==2*inf?-1:res) << '\n';
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
