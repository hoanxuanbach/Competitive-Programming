#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e6+5;
int n,m,d[maxn];
vector<pair<int,int>> edge[maxn];

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> m;
    for(int i=1;i<=n;i++) cin >> d[i];
    for(int i=1;i<=m;i++){
        int u,v,w;cin >> u >> v >> w;
        edge[u].push_back({v,w});
        edge[v].push_back({u,w});
    }
    priority_queue<pair<int,int>> pq;
    for(int i=1;i<=n;i++) pq.push({d[i],i});
    while(!pq.empty()){
        auto [dd,u]=pq.top();pq.pop();
        if(dd!=d[u]) continue;
        for(auto [v,w]:edge[u]) if(dd-w>d[v]) pq.push({d[v]=dd-w,v});
    }
    for(int i=1;i<=n;i++) cout << d[i] << '\n';
}
/*
4 5
6 5 9 2
1 2 0
3 2 3
4 3 6
1 3 5
2 4 2
*/
