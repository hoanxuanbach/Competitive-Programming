//#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,popcnt,lzcnt,abm,bmi,bmi2,fma")
#include<bits/stdc++.h>
using namespace std;
#define maxn 1005
const int maxL = 3e6;
#define pii pair<int,int>
#define fi first
#define se second

struct road{
    int x,y,u,v,t,len;
};
vector<int> p[maxn][maxn][4];
int dist[maxn][4*maxn],n,m,s,gx,gy,sx,sy;
road r[maxn];
void update(int x,int y,int u,int v,int id){
    int xt=x,yt=y;
    while(yt<v){p[xt][yt][0].push_back(id);yt++;}
    while(xt<u){p[xt][yt][1].push_back(id);xt++;}
    while(yt>y){p[xt][yt][2].push_back(id);yt--;}
    while(xt>x){p[xt][yt][3].push_back(id);xt--;}
}
int wait(int d,int x,int y,int id){
    int len=2*(r[id].u-r[id].x+r[id].v-r[id].y),cur=len-(x-r[id].x+y-r[id].y);
    if(x==r[id].x || y==r[id].v) cur=len-cur;
    int now=(r[id].t+d)%len;
    if(now<=cur) return cur-now;
    else return len+cur-now;
}
pii change(int id,int cur){
    if(id==0) return {gx,gy};
    int x=r[id].x,y=r[id].y;
    y+=min(cur,r[id].v-r[id].y);cur-=min(cur,r[id].v-r[id].y);
    x+=min(cur,r[id].u-r[id].x);cur-=min(cur,r[id].u-r[id].x);
    y-=min(cur,r[id].v-r[id].y);cur-=min(cur,r[id].v-r[id].y);
    x-=min(cur,r[id].u-r[id].x);
    return {x,y};
}
int rechange(int id,int x,int y){
    int len=2*(r[id].u-r[id].x+r[id].v-r[id].y),cur=len-(x-r[id].x+y-r[id].y);
    if(x==r[id].x || y==r[id].v) cur=len-cur;
    return cur;
}

vector<pii> pq[maxL+5];

int dijisktra(){
    dist[0][0]=-1;
    pq[0].push_back({0,0});
    for(int i=0;i<=maxL;i++){
        for(pii X:pq[i]){
            int d=i-1,it=X.fi,cur=X.se;
            if(dist[it][cur]!=d) return 0;
            auto [x,y]=change(it,cur);
            if(x==sx && y==sy) return d;
            for(int t=0;t<4;t++){
                if(binary_search(p[x][y][t].begin(),p[x][y][t].end(),it)){
                    int id=it;
                    int nxt=(cur+1)%r[id].len;
                    if(dist[id][nxt]>d+1){
                        dist[id][nxt]=d+1;
                        if(d+2<=maxL) pq[d+2].push_back({id,nxt});
                    }
                }
                else{
                    for(int id:p[x][y][t]){
                        int nxt=wait(d+1,x,y,id),po=rechange(id,x,y);
                        if(dist[id][po]>d+nxt+1){
                            dist[id][po]=d+nxt+1;
                            if(d+nxt+2<=maxL) pq[d+nxt+2].push_back({id,po});
                        }
                    }
                }
            }
        }
    }
    return -1;
}
signed main(){
    //freopen("04-04.txt","r",stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> m >> gx >> gy >> sx >> sy;
    swap(n,m);swap(gx,gy);swap(sx,sy);
    if(sx==gx && sy==gy){
        cout << 0 << '\n';
        return 0;
    }
    cin >> s;
    for(int i=1;i<=s;i++){
        int x,y,u,v,t;cin >> x >> y >> u >> v >> t;
        swap(x,y);swap(u,v);
        int len=2*(v+u-x-y);
        r[i]={x,y,u,v,t,len};
        update(x,y,u,v,i);
    }
    for(int i=0;i<=s;i++){
        for(int j=0;j<=2*(n+m);j++) dist[i][j]=INT_MAX;
    }
    cout << dijisktra() << '\n';
}
