#include "coprobber.h"
#include<bits/stdc++.h>
using namespace std;
const int maxn = 505;
#define pii pair<int,int>
#define piii pair<pii,int>
#define fi first
#define se second
int w[maxn][maxn][2],cnt[maxn],cc[maxn][maxn];
int nxt[maxn][maxn];

int start(int n, bool a[MAX_N][MAX_N])
{
    for(int i=0;i<n;i++) for(int j=0;j<n;j++) cnt[i]+=a[i][j];

    queue<piii> q;
    for(int i=0;i<n;i++) for(int j=0;j<2;j++){
        w[i][i][j]=1;
        q.push({{i,i},j});
    }
    while(!q.empty()){
        auto [P,t]=q.front();q.pop();
        auto [u,v]=P;
        for(int x=0;x<n;x++){
            if(t && (x==u || a[x][u]) && !w[x][v][0]){
                w[x][v][0]=1;
                nxt[x][v]=u;
                q.push({{x,v},0});
            }
            else if(!t && a[x][v] && !w[u][x][1] && (++cc[u][x]>=cnt[x])){
                w[u][x][1]=1;
                q.push({{u,x},1});
            }
        }
    }
    for(int i=0;i<n;i++) if(!w[0][i][0]) return -1;
    return 0;
}

int p=0;
int nextMove(int R)
{
    return p=nxt[p][R];
}
