#include<bits/stdc++.h>
using namespace std;
const int maxn = 305;
int m,n,k,cnt[maxn],total[maxn],dist[maxn];
vector<int> f[maxn],edge[maxn];

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> m >> n >> k;
    for(int i=1;i<=k;i++){
        int x;cin >> x;
        cnt[x]++;
    }
    map<pair<int,int>,int> mp;
    for(int i=1;i<=m;i++){
        int s;cin >> s;
        vector<int> V(s);
        for(int j=0;j<s;j++){
            cin >> V[j];
            f[V[j]].push_back(i);
        }
        for(int j=0;j<s;j++){
            int u=V[j],v=V[(j+1)%s];
            if(u>v) swap(u,v);
            if(mp.find({u,v})!=mp.end()){
                int id=mp[{u,v}];
                edge[id].push_back(i);
                edge[i].push_back(id);
            }
            mp[{u,v}]=i;
        }
    }
    for(int i=1;i<=n;i++){
        if(!cnt[i]) continue;
        memset(dist,-1,sizeof(dist));
        queue<int> q;
        for(int id:f[i]) q.push(id),dist[id]=0;
        while(!q.empty()){
            int u=q.front();q.pop();
            for(int v:edge[u]) if(dist[v]==-1){
                dist[v]=dist[u]+1;
                q.push(v);
            }
        }
        for(int u=1;u<=m;u++) total[u]+=dist[u]*cnt[i];
    }
    int x=1;
    for(int i=2;i<=m;i++) if(total[i]<total[x]) x=i;
    cout << total[x] << '\n' << x << '\n';
}
