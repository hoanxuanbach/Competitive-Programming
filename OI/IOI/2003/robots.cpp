#include<bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
#define piii pair<pii,int>
#define fi first
#define se second
const int maxN=405;
const int maxn=25;
int dx[]={0,0,1,-1},
    dy[]={1,-1,0,0};
char C[]={'E','W','S','N'};
const int D=10000;

int dist[maxN][maxN][15];

int n[5],m[5],S[5];
char c[5][maxn][maxn];
bool a[5][maxN][15],b[5][maxN][15][4];

int nxt(int x,int t,int d,int k){
    if(!x) return 0;
    int nk=(k+1)%12;
    int cx=(x-1)/m[t]+dx[d],cy=(x-1)%m[t]+dy[d];
    if(cx<0 || cy<0 || cx>=n[t] || cy>=m[t]) return 0;
    int nx=cx*m[t]+cy+1;

    if(c[t][cx][cy]=='#'){
        if(a[t][x][nk]) return -1;
        else return x;
    }
    else if(a[t][nx][nk] || b[t][x][k][d]) return -1;
    else return nx;
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    for(int t=0;t<=1;t++){
        cin >> n[t] >> m[t];
        for(int i=0;i<n[t];i++) for(int j=0;j<m[t];j++){
            cin >> c[t][i][j];
            if(c[t][i][j]=='X') S[t]=i*m[t]+j+1;
        }
        int k;cin >> k;
        for(int i=1;i<=k;i++){
            int x,y,d,p=0;char dir;
            cin >> x >> y >> d >> dir;x--;y--;
            while(C[p]!=dir) p++;
            for(int j=0;j<12;j++){
                a[t][x*m[t]+y+1][j]=1;
                x+=dx[p];y+=dy[p];
                //cout << x << ' ' << y << '\n';
                b[t][x*m[t]+y+1][j][p^1]=1;
                if((j+1)%(d-1)==0) p^=1;
            }
        }
    }
    memset(dist,-1,sizeof(dist));
    queue<piii> q;
    dist[S[0]][S[1]][0]=0;
    q.push({{S[0],S[1]},0});
    int x=0,y=0,K=-1;
    while(!q.empty()){
        auto [p,k]=q.front();q.pop();
        auto [x,y]=p;
        if(x==0 && y==0){
            K=k;
            break;
        }
        int nk=(k+1)%12;
        for(int t=0;t<4;t++){
            int nx=nxt(x,0,t,k);
            int ny=nxt(y,1,t,k);
            if(nx==-1 || ny==-1) continue;
            if(dist[nx][ny][nk]==-1){
                dist[nx][ny][nk]=(x*D+y)*4+t;
                q.push({{nx,ny},nk});
            }
        }
    }
    if(K==-1){
        //assert(false);
        cout << -1 << '\n';
        return 0;
    }
    string res;
    while(x!=S[0] || y!=S[1] || K!=0){
        int dd=dist[x][y][K];K=(K+11)%12;
        int t=dd%4;dd/=4;
        x=dd/D,y=dd%D;
        res+=C[t];
        //cout << x << ' ' << y << ' ' << t << '\n';
    }
    cout << (int)res.length() << '\n';
    while(!res.empty()){
        cout << res.back() << '\n';
        res.pop_back();
    }
}
