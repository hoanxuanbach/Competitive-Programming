#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5+5;
const int inf = 1e9;

int dp[2][4][4][4][4];
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
    for(int a=0;a<=3;a++) for(int b=0;b<=3;b++) for(int c=0;c<=3;c++) for(int d=0;d<=3;d++) dp[0][a][b][c][d]=-inf;
    dp[0][0][0][0][0]=0;
    C['M']=1;C['B']=2;C['F']=3;

    int t=0;
    for(int i=0;i<n;i++){
        for(int a=0;a<=3;a++) for(int b=0;b<=3;b++) for(int c=0;c<=3;c++) for(int d=0;d<=3;d++) dp[t^1][a][b][c][d]=-inf;

        char c;cin >> c;
        int x=C[c];
        for(int a=0;a<=3;a++) for(int b=0;b<=3;b++) for(int c=0;c<=3;c++) for(int d=0;d<=3;d++){
            if((a && !b) || (c && !d)) continue;
            int val=dp[t][a][b][c][d];
            dp[t^1][b][x][c][d]=max(dp[t^1][b][x][c][d],val+f(a,b,x));
            dp[t^1][a][b][d][x]=max(dp[t^1][a][b][d][x],val+f(c,d,x));
        }
        t^=1;
    }

    int res=0;
    for(int a=0;a<=3;a++) for(int b=0;b<=3;b++) for(int c=0;c<=3;c++) for(int d=0;d<=3;d++) res=max(res,dp[t][a][b][c][d]);
    cout << res << '\n';
}
