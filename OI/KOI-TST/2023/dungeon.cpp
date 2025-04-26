#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int maxn = 1005;
const int inf = 2e9;
int n;
ll res=-inf;
ll a[maxn][maxn],c[maxn][maxn];
ll d[4][maxn][maxn];

void cal(){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            d[0][i][j]=-inf;
            if(i>1) d[0][i][j]=max(d[0][i][j],d[0][i-1][j]);
            if(j>1) d[0][i][j]=max(d[0][i][j],d[0][i][j-1]);
            if(i==1 && j==1) d[0][i][j]=0;
            d[0][i][j]+=a[i][j];
        }
        for(int j=n;j>=1;j--){
            d[1][i][j]=-inf;
            if(i>1) d[1][i][j]=max(d[1][i][j],d[1][i-1][j]);
            if(j<n) d[1][i][j]=max(d[1][i][j],d[1][i][j+1]);
            if(i==1 && j==n) d[1][i][j]=0;
            d[1][i][j]+=a[i][j];
        }
    }
    for(int i=n;i>=1;i--){
        for(int j=1;j<=n;j++){
            d[2][i][j]=-inf;
            if(i<n) d[2][i][j]=max(d[2][i][j],d[2][i+1][j]);
            if(j>1) d[2][i][j]=max(d[2][i][j],d[2][i][j-1]);
            if(i==n && j==1) d[2][i][j]=0;
            d[2][i][j]+=a[i][j];
        }
        for(int j=n;j>=1;j--){
            d[3][i][j]=-inf;
            if(i<n) d[3][i][j]=max(d[3][i][j],d[3][i+1][j]);
            if(j<n) d[3][i][j]=max(d[3][i][j],d[3][i][j+1]);
            if(i==n && j==n) d[3][i][j]=0;
            d[3][i][j]+=a[i][j];
        }
    }
    for(int i=0;i<=n+1;i++){
        for(int t=0;t<4;t++) d[t][0][i]=d[t][i][0]=d[t][i][n+1]=d[t][n+1][i]=-inf;
        c[0][i]=c[i][0]=c[i][n+1]=c[n+1][i]=-inf;
    }
    d[0][0][1]=d[0][1][0]=0;
    d[1][0][n]=d[1][1][n+1]=0;
    d[2][n][0]=d[2][n+1][1]=0;
    d[3][n+1][n]=d[3][n][n+1]=0;
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++){
        c[i][j]=-inf;
        c[i][j]=max(c[i][j],c[i-1][j]+a[i][j]);
        res=max(res,c[i][j]+d[2][i+1][j]+d[3][i][j+1]);
        res=max(res,c[i][j]+d[2][i][j-1]+d[3][i][j+1]);
        res=max(res,c[i][j]+d[2][i][j-1]+d[3][i+1][j]);

        c[i][j]=max(c[i][j],a[i][j]+d[0][i][j-1]+d[1][i-1][j]);
        c[i][j]=max(c[i][j],a[i][j]+d[0][i][j-1]+d[1][i][j+1]);
        c[i][j]=max(c[i][j],a[i][j]+d[0][i-1][j]+d[1][i][j+1]);

        res=max(res,d[0][i][j-1]+d[1][i-1][j]+a[i][j]+d[2][i+1][j]+d[3][i][j+1]);
    }
}

int max_item_sum (std::vector<std::vector<int>> V) {
    n=(int)V.size();
    for(int i=0;i<n;i++) for(int j=0;j<n;j++) a[i+1][j+1]=V[i][j];
    cal();
    for(int i=1;i<=n;i++) for(int j=i+1;j<=n;j++) swap(a[i][j],a[j][i]);
    cal();
    return res;
}