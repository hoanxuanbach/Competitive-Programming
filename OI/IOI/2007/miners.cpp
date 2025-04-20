#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5+5;
const int inf = 1e9;

int dp[maxn][4][4][4][4];
int C[256];

int f(int x,int y,int z){
    if(!x){
        if(!y) return 1;
        else return 1+(y!=z);
    }
    else{
        if(x==y && y==z) return 1;
        else if(x^y^z) return 2;
        else return 3;
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int n;cin >> n;
    for(int i=0;i<=n;i++) for(int a=0;a<=3;a++) for(int b=0;b<=3;b++) for(int c=0;c<=3;c++) for(int d=0;d<=3;d++) dp[i][a][b][c][d]=-inf;
    dp[0][0][0][0][0]=0;
    C['M']=1;C['B']=2;C['F']=3;
    for(int i=0;i<n;i++){
        char c;cin >> c;
        int x=C[c];
        for(int a=0;a<=3;a++) for(int b=0;b<=3;b++) for(int c=0;c<=3;c++) for(int d=0;d<=3;d++){
            if((a && !b) || (c && !d)) continue;
            int val=dp[i][a][b][c][d];
            dp[i+1][b][x][c][d]=max(dp[i+1][b][x][c][d],val+f(a,b,x));
            dp[i+1][a][b][d][x]=max(dp[i+1][a][b][d][x],val+f(c,d,x));
        }
    }

    int res=0;
    for(int a=0;a<=3;a++) for(int b=0;b<=3;b++) for(int c=0;c<=3;c++) for(int d=0;d<=3;d++) res=max(res,dp[n][a][b][c][d]);
    cout << res << '\n';
}
