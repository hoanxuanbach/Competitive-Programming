#include<bits/stdc++.h>
using namespace std;
#define maxn 15
#define maxd 35
const int mod=11380;
int dp[maxn][maxn][maxn][maxd][2];
bool check[maxn][maxn][maxn][maxd][2];
int solve(int x,int y,int z,int d,int f){
    if(x==0 && y==0 && z==0) return 1;
    if(check[x][y][z][d][f]) return dp[x][y][z][d][f];
    check[x][y][z][d][f]=true;
    int res=0;
    if(x>=1 && d>=1 && y==0 && z==0) res+=solve(x-1,y,z,d-1,0);
    if(y>=1 && d>=1 && z==0) res+=solve(x,y-1,z,d-1,0);
    if(z>=1 && d>=1) res+=solve(x,y,z-1,d-1,0);
    res%=mod;
    if(f==0){
        for(int i=0;i<=x;i++){
            for(int j=0;j<=y;j++){
                for(int k=0;k<=z;k++){
                    if(i+j+k==0 || i+j+k==x+y+z) continue;
                    res+=solve(i,j,k,d,1)*solve(x-i,y-j,z-k,d,0);
                    res%=mod;
                }
            }
        }
    }
    return dp[x][y][z][d][f]=res;
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    auto st=clock();
    int l1,l2,l3,d;cin >> l3 >> l2 >> l1 >> d;
    int res=solve(l1,l2,l3,d,0);
    if(d>=1) res=(res-solve(l1,l2,l3,d-1,0)+mod)%mod;
    cout << res << '\n';
}