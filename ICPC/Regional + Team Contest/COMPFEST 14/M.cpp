#include<bits/stdc++.h>
using namespace std;
#define int long long
#define maxn 100005
#define pii pair<int,int>
#define piii pair<int,pii>
#define se second
#define fi first
vector<pii> edge[maxn][2];
int n,m,dist[maxn][2];
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> m;
    for(int i=1;i<=n;i++) dist[i][0]=dist[i][1]=LLONG_MAX;
    for(int i=1;i<=m;i++){
        int u,v,w;cin >> u >> v >> w;
        edge[u][0].push_back({v,w});
        edge[v][1].push_back({u,w});
    }
    priority_queue<piii,vector<piii>,greater<piii>> pq;
    dist[1][0]=0;pq.push({0,{1,0}});
    while(!pq.empty()){
        int d=pq.top().fi,u=pq.top().se.fi,t=pq.top().se.se;pq.pop();
        if(dist[u][t]!=d) continue;
        if(t==0 && d<dist[u][1]){
            dist[u][1]=d;
            pq.push({d,{u,1}});
        }
        for(pii x:edge[u][t]){
            if(d+x.second<dist[x.first][t]){
                dist[x.first][t]=d+x.second;
                pq.push({d+x.second,{x.first,t}});
            }
        }
    }
    for(int i=2;i<=n;i++){
        if(dist[i][1]==LLONG_MAX) cout << -1 << ' ';
        else cout << dist[i][1] << ' ';
    }
}
