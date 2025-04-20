#include<bits/stdc++.h>
using namespace std;
const int maxn = 1005;
const int inf = 1e9;

int n,m,a,b,c,d,p[maxn][maxn];
int mn[maxn][maxn],nw[maxn];

int f(int x,int y,int u,int v){
    return p[u][v]-p[x-1][v]-p[u][y-1]+p[x-1][y-1];
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> m >> a >> b >> c >> d;
    for(int i=1;i<=m;i++) for(int j=1;j<=n;j++) cin >> p[j][i];
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) p[i][j]+=p[i-1][j]+p[i][j-1]-p[i-1][j-1];
    for(int i=c;i<=n;i++) for(int j=d;j<=m;j++) mn[i][j]=f(i-c+1,j-d+1,i,j);
    int A=a-c-1,B=b-d-1;
    for(int i=1;i<=n;i++){
        deque<int> dq;
        //cout << i << endl;
        for(int j=1;j<=m;j++){
            while(!dq.empty() && mn[i][dq.back()]>mn[i][j]) dq.pop_back();
            dq.push_back(j);

            if(dq.front()<=j-B) dq.pop_front();
            nw[j]=mn[i][dq.front()];
        }
        for(int j=1;j<=m;j++) mn[i][j]=nw[j];
    }
    for(int i=1;i<=m;i++){
        deque<int> dq;
        for(int j=1;j<=n;j++){
            while(!dq.empty() && mn[dq.back()][i]>mn[j][i]) dq.pop_back();
            dq.push_back(j);
            if(dq.front()<=j-A) dq.pop_front();
            nw[j]=mn[dq.front()][i];
        }
        for(int j=1;j<=n;j++) mn[j][i]=nw[j];
    }
    int res=-1,x=-1,y=-1;
    for(int i=a;i<=n;i++){
        for(int j=b;j<=m;j++){
            int val=f(i-a+1,j-b+1,i,j)-mn[i-1][j-1];
            //cout << val << ' ';
            if(val>res) res=val,x=i,y=j;
        }
        //cout << '\n';
    }
    res=inf;
    int u=-1,v=-1;
    for(int i=x-A;i<x;i++) for(int j=y-B;j<y;j++) if(f(i-c+1,j-d+1,i,j)<res) res=f(i-c+1,j-d+1,i,j),u=i,v=j;
    cout << x-a+1 << ' ' << y-b+1 << ' ' << u-c+1 << ' ' << v-d+1 << '\n';
}
