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
const int maxn=50005;
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

int X[maxn],a[maxn],b[maxn],total[maxn];
int n,m,k,c[maxn];
vector<int> edge[maxn];
int dist[maxn],D[maxn];

int Num=0,num=0,res[maxn];
vector<int> dd[maxn];

void solve(){
    cin >> n >> m >> k;
    for(int i=1;i<=m;i++){
        int u,v;cin >> u >> v;
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    for(int i=1;i<=n;i++){
        char cc;cin >> cc;
        c[i]=cc-'0';Num+=c[i];
    }
    for(int i=1;i<=k;i++) cin >> X[i];

    memset(dist,-1,sizeof(dist));
    queue<int> q;
    for(int i=1;i<=n;i++) if(c[i]){
        dist[i]=0;
        q.push(i);
    }
    while(!q.empty()){
        int u=q.front();q.pop();
        for(int v:edge[u]) if(dist[v]==-1){
            dist[v]=dist[u]+1;
            q.push(v);
        }
    }
    for(int i=1;i<=k;i++) if(dist[X[i]]) a[i]=dist[X[i]]-2;

    for(int i=1;i<=n;i++) dist[i]=inf;
    deque<pii> dq;
    for(int i=1;i<=n;i++){
        bool cc=false;
        for(int v:edge[i]) if(c[v]) cc=true;
        if(c[i] && cc){
            dist[i]=0;
            dq.push_back({0,i});
        }
    }
    while(!dq.empty()){
        auto [d,u]=dq.front();dq.pop_front();
        if(dist[u]!=d) continue;
        for(int v:edge[u]){
            int nd=d+1-c[v];
            if(dist[v]<=nd) continue;
            dist[v]=nd;
            if(nd==d) dq.push_front({nd,v});
            else dq.push_back({nd,v});
        }
    }
    for(int i=1;i<=k;i++){
        b[i]=dist[X[i]];
        if(b[i]!=inf) b[i]-=(1-c[X[i]]);
    }

    dq.clear();
    for(int i=1;i<=n;i++) dist[i]=inf;
    dist[X[1]]=0;dq.push_back({0,X[1]});
    while(!dq.empty()){
        auto [d,u]=dq.front();dq.pop_front();
        if(dist[u]!=d) continue;
        for(int v:edge[u]){
            int nd=d+c[v];
            if(dist[v]<=nd) continue;
            dist[v]=nd;
            if(nd==d) dq.push_front({nd,v});
            else dq.push_back({nd,v});
        }
    }
    for(int i=1;i<=n;i++){
        D[i]=dist[i];
        //cout << D[i] << ' ';
    }
    //cout << '\n';
    int cur=k-1;
    for(int j=2;j<=k;j++) if(b[j]-a[j]<=Num) total[max(0LL,b[j]-a[j])]++;
    cur-=total[0];total[0]=0;
    for(int j=2;j<=k;j++) total[0]+=min(a[j],b[j]);
    for(int i=1;i<=Num;i++){
        int x=total[i];
        total[i]=total[i-1]+k-1+cur;
        cur-=x;
    }
    total[0]=0;
    queue<pii> qq;
    num=min(Num,500LL);
    for(int i=1;i<=n;i++) dd[i].resize(num+1,-1);
    dd[X[1]][0]=0;
    qq.push({X[1],0});
    while(!qq.empty()){
        auto [u,t]=qq.front();qq.pop();
        for(int v:edge[u]){
            if(t+c[v]-D[v]>num || t+c[v]>Num) continue;
            if(dd[v][t+c[v]-D[v]]==-1){
                dd[v][t+c[v]-D[v]]=dd[u][t-D[u]]+1;
                qq.push({v,t+c[v]});
            }
        }
    }
    priority_queue<pii,vector<pii>,greater<pii>> pq;
    for(int i=1;i<=n;i++) dist[i]=inf;
    for(int i=1;i<=n;i++){
        res[i]=inf;
        for(int j=0;j<=num;j++){
            if(dd[i][j]==-1) continue;
            dist[i]=dd[i][j]+total[j+D[i]];
            if(!c[i]) res[i]=min(res[i],dd[i][j]+total[j+D[i]]);
            else res[i]=min(res[i],dd[i][j]+total[max(0LL,j+D[i]-1)]);
        }
    }
    if(k<=100 && Num>500){
        for(int i=1;i<=n;i++) if(dist[i]!=inf) pq.push({dist[i],i});
        cur+=k-1;
        while(!pq.empty()){
            auto [d,u]=pq.top();pq.pop();
            for(int v:edge[u]){
                int nd=d+1+cur*c[v];
                if(nd<dist[v]) pq.push({dist[v]=nd,v});
            }
        }
        for(int i=1;i<=n;i++){
            if(dist[i]==inf) continue;
            if(!c[i]) res[i]=min(res[i],dist[i]);
            else res[i]=min(res[i],dist[i]-cur);
        }
    }
    for(int i=1;i<=n;i++) cout << res[i] << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
