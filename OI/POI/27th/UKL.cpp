#include<bits/stdc++.h>
using namespace std;
#define maxn 1005
#define right 0
#define up 1
#define left 2
#define down 3
int dx[]={0,-1,0,1},
    dy[]={1,0,-1,0};
int c[maxn][maxn];
bool vis[maxn][maxn];
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    int n,m,k;cin >> n >> m >> k;
    if(k<n+m-2 || k>=n*m){
        cout << "NIE\n";
        return 0;
    }
    if(k==n+m-2 && n%2==0 && m%2==0){
        cout << "NIE\n";
        return 0;
    }
    cout << "TAK\n";
    if(k==n+m-2){
        if(n%2==1){
            for(int i=1;i<=n;i++){
                for(int j=1;j<=m;j++){
                    if(i==n/2+1){
                        if(j==1) c[i][j]=-1;
                        else c[i][j]=left;
                    }
                    else if(i<=n/2) c[i][j]=down;
                    else c[i][j]=up;
                }
            }
        }
        else{
            for(int i=1;i<=n;i++){
                for(int j=1;j<=m;j++){
                    if(j==m/2+1){
                        if(i==1) c[i][j]=-1;
                        else c[i][j]=up;
                    }
                    else if(j<=m/2) c[i][j]=right;
                    else c[i][j]=left;
                }
            }
        }
    }
    else if(k<=2*n+m-3){
        if(m>=3){
            int d=(k-m+3)/2;
            for(int i=1;i<d;i++){
                for(int j=1;j<=m;j++) c[i][j]=down;
            }
            c[d][1]=-1;
            for(int j=2;j<=m;j++) c[d][j]=left;
            for(int i=d+1;i<=n;i++){
                for(int j=1;j<=m;j++) c[i][j]=up;
            }
            if(d*2+m-3<k) c[1][2]=left;
        }
        else{
            k-=n+1;c[1][1]=-1;
            for(int i=2;i<=n;i++) c[i][1]=up;
            c[1][2]=left;
            for(int i=2;i<=k+1;i++) c[i][2]=up;
            for(int i=k+2;i<=n;i++) c[i][2]=left;
        }
    }
    else{
        int sx=n,sy=m,t=1;
        c[sx][sy]=-1;
        while(k>0){
            vis[sx][sy]=true;k--;
            int nx=sx+dx[t],ny=sy+dy[t];
            if(nx<=0 || ny<=0 || nx>n || ny>m || vis[nx][ny]) t=(t+1)%4;
            sx+=dx[t];sy+=dy[t];
            c[sx][sy]=t^2;
        }
        vis[sx][sy]=true;
        int nx=sx+dx[t],ny=sy+dy[t];
        if(nx<=0 || ny<=0 || nx>n || ny>m || vis[nx][ny]) t=(t+1)%4;
        t=(t+1)%4;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(vis[i][j]) continue;
                c[i][j]=t;
            }
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(c[i][j]==-1) continue;
            int t=c[i][j];
            cout << i << ' ' << j << ' ' << i+dx[t] << ' ' << j+dy[t] << '\n';
        }
    }
}
