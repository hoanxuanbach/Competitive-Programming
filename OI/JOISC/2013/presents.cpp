#include<bits/stdc++.h>
using namespace std;
#define maxn 100005
#define int long long
struct node{
    int v,x,d;
};
int ans=0,n,a[maxn],b[maxn],c[maxn],d[maxn],deg[maxn],col[maxn];
node nxt[maxn];
bool visited[maxn];
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n;
    for(int i=1;i<=n;i++) cin >> a[i] >> b[i] >> c[i] >> d[i];
    for(int i=1;i<=n;i++){
        int v=a[i];deg[v]++;
        ans+=max(c[v],d[v])*b[i];
        if(c[v]>d[v]) nxt[i]={v,0,abs(c[v]-d[v])*b[i]};
        else nxt[i]={v,1,abs(c[v]-d[v])*b[i]};
    }
    queue<int> q;
    for(int i=1;i<=n;i++){
        if(deg[i]==0){q.push(i);visited[i]=true;}
    }
    while(!q.empty()){
        int u=q.front();q.pop();
        int v=nxt[u].v;deg[v]--;
        if(deg[v]==0){q.push(v);visited[v]=true;}
    }
    for(int i=1;i<=n;i++){
        if(!visited[i]){
            int u=i,Min=LLONG_MAX;
            bool check=true;
            while(true){
                Min=min(Min,nxt[u].d);
                int v=nxt[u].v;visited[u]=true;
                if(visited[v] && col[v]^col[u]!=nxt[u].x) check=false;
                col[v]=col[u]^nxt[u].x;u=v;
                if(visited[u]) break;
            }
            if(!check) ans-=Min;
        }
    }
    cout << ans << '\n';
}
