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
#include<bits/stdc++.h>
using namespace std;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_real_distribution<> pp(0.0,1.0);
#define int long long
#define pii pair<int,int>
const int inf=1e18;
const int mod=998244353;
const int maxn=100005;
const int maxl=20;
const int maxa=1000005;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
vector<pii> edge[maxn];
int n,m,du[maxn],dv[maxn],dist[maxn],dp[maxn][2][2];
void dijisktra(int st){
    for(int i=1;i<=n;i++) du[i]=inf;
    priority_queue<pii,vector<pii>,greater<pii>> pq;
    du[st]=0;pq.push({0,st});
    while(!pq.empty()){
        int u=pq.top().second,d=pq.top().first;pq.pop();
        if(du[u]!=d) continue;
        for(pii v:edge[u]){
            if(du[v.first]>d+v.second){
                du[v.first]=d+v.second;
                pq.push({d+v.second,v.first});
            }
        }
    }
}
void solve(){
    int u,v,s,t;cin >> n >> m >> s >> t >> u >> v;
    for(int i=1;i<=m;i++){
        int x,y,w;cin >> x >> y >> w;
        edge[x].push_back({y,w});
        edge[y].push_back({x,w});
    }
    dijisktra(v);
    for(int i=1;i<=n;i++) dv[i]=du[i];
    dijisktra(u);
    for(int i=1;i<=n;i++){
        dist[i]=inf;
        for(int j=0;j<=1;j++){
            for(int k=0;k<=1;k++) dp[i][j][k]=inf;
        }
    }
    priority_queue<pii,vector<pii>,greater<pii>> pq;
    dist[s]=0;pq.push({0,s});
    dp[s][0][0]=0;dp[s][1][0]=du[s];dp[s][0][1]=dv[s];dp[s][1][1]=du[s]+dv[s];
    while(!pq.empty()){
        int u=pq.top().second,d=pq.top().first;pq.pop();
        if(dist[u]!=d) continue;
        //cout << u << ' ' << d << '\n';
        for(pii v:edge[u]){
            if(dist[v.first]>d+v.second){
                dist[v.first]=d+v.second;
                pq.push({d+v.second,v.first});
                for(int i=0;i<=1;i++){
                    for(int j=0;j<=1;j++){
                        dp[v.first][i][j]=dp[u][i][j];
                        if(i) dp[v.first][i][j]=min(dp[v.first][i][j],dp[v.first][0][j]+du[v.first]);
                        if(j) dp[v.first][i][j]=min(dp[v.first][i][j],dp[v.first][i][0]+dv[v.first]);
                        if(i && j) dp[v.first][i][j]=min(dp[v.first][i][j],dp[v.first][0][0]+du[v.first]+dv[v.first]);
                    }
                }
            }
            else if(dist[v.first]==d+v.second){
                for(int i=0;i<=1;i++){
                    for(int j=0;j<=1;j++){
                        dp[v.first][i][j]=min(dp[u][i][j],dp[v.first][i][j]);
                        if(i) dp[v.first][i][j]=min(dp[v.first][i][j],dp[v.first][0][j]+du[v.first]);
                        if(j) dp[v.first][i][j]=min(dp[v.first][i][j],dp[v.first][i][0]+dv[v.first]);
                        if(i && j) dp[v.first][i][j]=min(dp[v.first][i][j],dp[v.first][0][0]+du[v.first]+dv[v.first]);
                    }
                }
            }
        }
    }
    cout << min(dp[t][1][1],du[v]) << '\n';
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int t=1;//cin >> t;
    while(t--) solve();
}