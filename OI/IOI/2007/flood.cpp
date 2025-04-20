#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int,int>
#define fi first
#define se second
const int maxn = 2e5+5;
int dx[]={0,1,0,-1},
    dy[]={1,0,-1,0};

int N,M,X[maxn],Y[maxn],C[maxn],total[maxn],dist[maxn];
int P[maxn][2],nxt[maxn][4],cnt;
vector<int> edge[maxn];

int g(int a,int b){
    if(X[a]==X[b]) return 2*(Y[a]<Y[b]);
    else return 2*(X[a]<X[b])+1;
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> N;
    for(int i=1;i<=N;i++) cin >> X[i] >> Y[i];
    cin >> M;
    for(int i=1;i<=M;i++){
        int u,v;cin >> u >> v;
        nxt[u][g(u,v)]=i;
        nxt[v][g(v,u)]=-i;
        C[i]=u^v;
    }
    for(int i=1;i<=N;i++) for(int j=0;j<4;j++){
        if(!nxt[i][j]) continue;
        int u=i,t=j,pos=0;
        vector<pii> p;
        int add=0;
        while(true){
            int id=abs(nxt[u][t]),k=(nxt[u][t]<0);
            if(P[id][k]){
                pos=P[id][k];
                break;
            }
            P[id][k]=-1;
            p.push_back({id,k});
            int v=C[id]^u;t^=2;
            for(int d=1;d<=4;d++){
                int nt=(t+d)%4;
                if(nxt[v][nt]){t=nt;break;}
            }
            add+=X[u]*Y[v]-X[v]*Y[u];
            u=v;
        }
        if(pos==-1) pos=++cnt;
        for(auto [x,y]:p) P[x][y]=pos;
        total[pos]+=add;
    }
    for(int i=1;i<=cnt;i++) total[i]=abs(total[i]);
    for(int i=1;i<=M;i++){
        edge[P[i][0]].push_back(P[i][1]);
        edge[P[i][1]].push_back(P[i][0]);
    }
    memset(dist,-1,sizeof(dist));
    vector<int> ord(cnt);
    iota(ord.begin(),ord.end(),1);
    sort(ord.begin(),ord.end(),[&](int x,int y){
        return total[x]>total[y];
    });
    for(int s:ord){
        if(dist[s]!=-1) continue;
        queue<int> q;
        dist[s]=0;q.push(s);
        while(!q.empty()){
            int u=q.front();q.pop();
            for(int v:edge[u]) if(dist[v]==-1){
                dist[v]=dist[u]+1;
                q.push(v);
            }
        }
    }
    int ans=0;
    for(int i=1;i<=M;i++) ans+=(dist[P[i][0]]==dist[P[i][1]]);
    cout << ans << '\n';
    for(int i=1;i<=M;i++) if(dist[P[i][0]]==dist[P[i][1]]) cout << i << '\n';
}
