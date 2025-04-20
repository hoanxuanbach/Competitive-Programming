#include<bits/stdc++.h>
using namespace std;
const int maxn = 1000005;
int dp[maxn][3][3];

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int n,m;cin >> n >> m;
    for(int i=0;i<=2;i++) for(int j=0;j<=i;j++) dp[n][i][j]=1;
    for(int i=n-1;i>=1;i--) for(int j=0;j<=2;j++) for(int k=0;k<=j;k++){
        for(int x:{-1,1}){
            int nk=k+x,nj=j;
            if(nk<0) nj-=nk,nk=0;
            nj=max(nj,nk);
            if(nj<=2) dp[i][j][k]=(dp[i][j][k]+dp[i+1][nj][nk])%m;
        }
    }
    int total=1,j=0,k=0;
    for(int i=1;i<=n;i++){
        char c;cin >> c;
        for(char cc:{'L','P'}){
            int x=(cc=='L'?-1:1);
            int nk=k+x,nj=j;
            if(nk<0) nj-=nk,nk=0;
            nj=max(nj,nk);
            if(nj>2) continue;
            if(cc==c){
                j=nj,k=nk;
                break;
            }
            else total=(total+dp[i][nj][nk])%m;
        }
        //cout << j << ' ' << k << ' ' << total << '\n';
    }
    cout << total << '\n';
}
