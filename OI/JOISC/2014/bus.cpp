#include<bits/stdc++.h>
using namespace std;
#define maxn 100005
#define pii pair<int,int>
struct ed{
    int u,t,id,a;
    bool operator<(ed o){
        if(t!=o.t) return t<o.t;
        else return a<o.a;
    }
};
int n,m,d[3*maxn],Max[maxn];
vector<pii> dist[maxn];
vector<ed> e;
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> m;
    for(int i=1;i<=m;i++){
        int u,v,s,t;cin >> u >> v >> s >> t;
        e.push_back({u,s,i,1});
        e.push_back({v,t,i,0});
    }
    for(int i=1;i<=n;i++) Max[i]=-1;
    sort(e.begin(),e.end());
    for(ed x:e){
        if(x.a==1){
            if(x.u==1) d[x.id]=x.t;
            else d[x.id]=Max[x.u];
        }
        else{
            if(d[x.id]!=-1){
                dist[x.u].push_back({x.t,d[x.id]});
                Max[x.u]=max(Max[x.u],d[x.id]);
            }
        }
    }
    for(int i=1;i<(int)dist[n].size();i++) dist[n][i].second=max(dist[n][i].second,dist[n][i-1].second);
    int q;cin >> q;
    while(q--){
        int x;cin >> x;
        int p=upper_bound(dist[n].begin(),dist[n].end(),make_pair(x,INT_MAX))-dist[n].begin();
        if(p==0) cout << -1 << '\n';
        else cout << dist[n][p-1].second << '\n';
    }
}
