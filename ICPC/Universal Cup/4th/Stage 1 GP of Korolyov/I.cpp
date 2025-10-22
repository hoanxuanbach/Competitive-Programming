#include<bits/stdc++.h>
using namespace std;
const int inf = 1e9;
const int K = 7;
const int S = 4;

void solve(){
    int n;cin >> n;
    
    vector<int> a(n+1);
    for(int i=0;i<n;i++) cin >> a[i];
    a[n]=inf;

    int pos=n;
    while(pos && a[pos-1]<=a[pos]) pos--;
    if(!pos){
        cout << 0 << '\n';
        return;
    }
    
    vector<vector<vector<int>>> mex(S,vector<vector<int>>(S,vector<int>(S)));
    for(int a=0;a<S;a++) for(int b=0;b<S;b++) for(int c=0;c<S;c++){
        while(mex[a][b][c]==a || mex[a][b][c]==b || mex[a][b][c]==c) mex[a][b][c]++;
    } 

    vector<vector<vector<int>>> g(1<<S,vector<vector<int>>(1<<S,vector<int>(1<<S,0)));
    for(int x=0;x<(1<<S);x++) for(int y=0;y<(1<<S);y++) for(int z=0;z<(1<<S);z++){
        for(int a=0;a<S;a++) for(int b=0;b<S;b++) for(int c=0;c<S;c++) if((x>>a&1) && (y>>b&1) && (z>>c&1)){
            g[x][y][z]|=1<<mex[a][b][c];
        }
    }

    vector<vector<int>> f(n,vector<int>(K,0));
    for(int i=n-1;i>=0;i--){
        f[i][0]=1<<min(a[i],S-1);
        for(int j=1;j<K;j++){
            if(i+2*j+1>n) continue;
            for(int x=0;x<j;x++) for(int y=0;x+y<j;y++){
                int z=j-1-x-y;
                f[i][j]|=g[f[i][x]][f[i+2*x+1][y]][f[i+2*x+1+2*y+1][z]];
                if(f[i][j]==(1<<S)-1) break;
            }
        }
    }

    vector<vector<int>> dp(n+1,vector<int>(S,inf));
    dp[0][0]=0;
    for(int i=0;i<n;i++) for(int j=0;j<S;j++){
        for(int x=0;x<3*K;x++){
            if(i+2*x+1>n || (x==0 && a[i]>=S)) continue;
            int mask=(x<K?f[i][x]:(1<<S)-1);
            for(int k=j;k<S;k++) if(mask>>k&1){
                dp[i+2*x+1][k]=min(dp[i+2*x+1][k],dp[i][j]+x);
            }
        }
    }

    int res=inf;
    for(int i=pos;i<=n;i++) for(int j=0;j<S;j++) if(j<=a[i]) res=min(res,dp[i][j]);
    cout << (res==inf?-1:res) << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}