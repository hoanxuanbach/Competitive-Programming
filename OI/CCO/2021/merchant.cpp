#include<bits/stdc++.h>
using namespace std;
const int inf = 2e9;
const int maxn = 2e5+5;

int n,m,d[maxn],f[maxn];
vector<int> edge[maxn];
bool del[maxn];

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> m;
    vector<array<int,4>> e(m);
    for(int i=0;i<m;i++) cin >> e[i][1] >> e[i][2] >> e[i][0] >> e[i][3];
    sort(e.begin(),e.end());
    for(int i=0;i<m;i++) edge[e[i][2]].push_back(i),d[e[i][1]]++;
    queue<int> q;
    for(int i=1;i<=n;i++){
        f[i]=inf;
        if(!d[i]) q.push(i);
    }
    for(int i=m-1;i>=0;i--){
        while(!q.empty()){
            int v=q.front();q.pop();
            for(int id:edge[v]){
                if(del[id]) continue;
                int u=e[id][1],r=e[id][0],p=e[id][3];
                if(f[v]<inf) f[u]=min(f[u],max(r,f[v]-p));
                del[id]=1;
                if(!(--d[u])) q.push(u);
            }
        }
        if(!del[i]){
            int u=e[i][1],r=e[i][0];del[i]=1;
            f[u]=min(f[u],r);
            if(!(--d[u])) q.push(u);
        }
    }
    for(int i=1;i<=n;i++) cout << (f[i]==inf?-1:f[i]) << " \n"[i==n];
}
