#include<bits/stdc++.h>
using namespace std;
const int maxn = 1505;
#define pii pair<int,int>
#define fi first
#define se second
int dx[]={0,0,-1,1},
    dy[]={-1,1,0,0};

int N,M,K,L,X,Y,U,V,_;
int c[maxn][maxn],d[maxn][maxn];
int lt[2][maxn][maxn],up[2][maxn][maxn];

bool out(int x,int y){
    return (x<=0 || y<=0 || x>N || y>M);
}

bool query(int x,int y,int u,int v){
    if(out(x,y) || out(u,v)) return true;
    return c[u][v]-c[x-1][v]-c[u][y-1]+c[x-1][y-1];
}

bool check(int x,int y,int u,int v){
    if(x>u || y>v) swap(x,u),swap(y,v);
    if(query(x,y,u,v)) return false;
    if(y+1==v){
        int p=max(up[1][x][y],x-L)+1;
        if(query(p,y,p+L-1,y+1)) return false;
        p=max(lt[0][x][y],y-K+1)+1;
        if(query(x,p,x,p+K-1)) return false;
    }
    else if(x+1==u){
        int p=max(lt[1][x][y],y-K)+1;
        if(query(x,p,x+1,p+K-1)) return false;
        p=max(up[0][x][y],x-L+1)+1;
        if(query(p,y,p+L-1,y)) return false;
    }
    return true;
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> M >> N >> K >> L;
    cin >> _ >> X >> Y >> _;X++;Y++;
    for(int i=1;i<=N;i++) for(int j=1;j<=M;j++){
        char cc;cin >> cc;
        if(cc=='*') U=i,V=j;
        else c[i][j]=(cc=='X');
    }
    for(int t=0;t<=1;t++){
        for(int i=1;i<=N;i++) for(int j=1;j<=M-t;j++){
            int val=c[i][j]+c[i][j+t];
            up[t][i][j]=(val?i:up[t][i-1][j]);
        }
        for(int i=1;i<=N-t;i++) for(int j=1;j<=M;j++){
            int val=c[i][j]+c[i+t][j];
            lt[t][i][j]=(val?j:lt[t][i][j-1]);
        }
    }
    for(int i=1;i<=N;i++) for(int j=1;j<=M;j++) c[i][j]+=c[i-1][j]+c[i][j-1]-c[i-1][j-1];

    queue<pii> q;
    q.push({X,Y});d[X][Y]=1;
    while(!q.empty()){
        auto [x,y]=q.front();q.pop();
        //cout << x << ' ' << y << '\n';
        for(int t=0;t<4;t++){
            int xt=x+dx[t],yt=y+dy[t];
            //cout << "nxt " << xt << ' ' << yt << '\n';
            if(out(xt,yt) || d[xt][yt]) continue;
            if(check(x,y,xt,yt)){
                //cout << x << ' ' << y << ' ' << xt << ' ' << yt << '\n';
                d[xt][yt]=1,q.push({xt,yt});
            }
        }
    }
    cout << (d[U][V]?"YES":"NO") << '\n';
}
