#include<bits/stdc++.h>
using namespace std;
#define maxn 100005
#define pii pair<int,int>
vector<pii> edge[maxn];
long long n,m,c[maxn],st,en,num=0,ans[maxn],dep[maxn];
bool check[maxn],visited[maxn];
bool dfs(int u,int par){
    bool ok=false;
    visited[u]=true;
    for(pii x:edge[u]){
        int v=x.first;
        if(v==par) continue;
        if(visited[v]){st=u;en=v;}
        else if(dfs(v,u)) ok=true;
    }
}
void dfs2(int u,int par){
    for(pii v:edge[u]){
        if(v.first==par || check[v.first]) continue;
        dfs2(v.first,u);
        ans[v.second]-=c[v.first];
        c[u]-=c[v.first];
        c[v.first]=0;
    }
}
void bfs(){
    queue<int> q;
    for(int i=1;i<=n;i++){
        if(dep[i]==1) q.push(i);
    }
    while(!q.empty()){
        int u=q.front();q.pop();
        for(pii v:edge[u]){
            dep[v.first]--;
            if(dep[v.first]==1) q.push(v.first);
        }
    }
    for(int i=1;i<=n;i++){
        if(dep[i]>1){check[i]=true;num++;}
    }
}
int main(){
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> m;
    if(m>n){
        cout << 0 << '\n';
        return 0;
    }
    for(int i=1;i<=n;i++) cin >> c[i];
    for(int i=1;i<=m;i++){
        int u,v;cin >> u >> v;
        edge[u].push_back({v,i});dep[u]++;
        edge[v].push_back({u,i});dep[v]++;
    }
    bfs();
    if(num%2==0 && m==n){
        cout << 0 << '\n';
        return 0;
    }
    for(int i=1;i<=n;i++){
        if(check[i]) dfs2(i,0);
    }
    if(m!=n) dfs2(1,0);
    int cur=0,u=0,pre=0;
    for(int i=1;i<=n;i++){
        if(check[i]){cur=i;u=i;break;}
    }
    for(int i=0;i<=1;i++){
        u=cur;
        if(i==1) c[u]/=2;
        while(true){
            for(pii v:edge[u]){
                if(check[v.first] && v.first!=pre){
                    //cout << u << ' ' << v.first << '\n';
                    ans[v.second]-=c[u];
                    c[v.first]-=c[u];
                    c[u]=0;pre=u;u=v.first;
                    break;
                }
            }
            if(u==cur) break;
        }
    }
    for(int i=1;i<=m;i++) cout << -ans[i]*2 << '\n';
}
