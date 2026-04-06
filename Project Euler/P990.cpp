#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 1e9+7;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
 
const int maxn = 2e5+5;
const int inf = 1e18;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}

int f[30][30][305];
int g[55][30],C[30][30];
int dp[55][30][30][30];

void solve(){
    int N;cin >> N;
    int M=(N+1)/2;

    for(int x=0;x<=M;x++) for(int y=0;x+y<=M;y++){
        int S=(x+y)*9;
        f[x][y][y*9]=1;
        for(int i=0;i<x;i++){
            for(int k=1;k<=S;k++) (f[x][y][k]+=f[x][y][k-1])%=mod;
            for(int k=S;k>=10;k--) f[x][y][k]=(f[x][y][k]-f[x][y][k-10]+mod)%mod;
        }
        for(int i=0;i<y;i++){
            for(int k=S;k>=0;k--) (f[x][y][k]+=f[x][y][k+1])%=mod;
            for(int k=0;k<=S;k++) f[x][y][k]=(f[x][y][k]-f[x][y][k+10]+mod)%mod;
        }
    }

    g[0][1]=1;
    g[1][0]=-1;
    g[1][1]=-1;
    for(int i=0;i<N;i++) for(int j=0;j<=min(M,N-i);j++){
        if(!g[i][j]) continue;
        (g[i+1][j+1]+=g[i][j])%=mod;
        (g[i+2][j+1]-=g[i][j])%=mod;
        (g[i+2][j]-=g[i][j])%=mod;
    }

    for(int i=0;i<=M;i++){
        C[i][0]=1;
        for(int j=1;j<=i;j++) C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
    }

    for(int i=0;i<=N;i++){
        for(int x=0;x<=M;x++) for(int y=0;x+y<=M;y++) for(int k=0;k<=M;k++) for(int nx=0;nx<x;nx++) (dp[i][nx][y][k]+=dp[i][x][y][k]*C[x][nx])%=mod;
        for(int y=0;y<=M;y++) for(int x=0;x+y<=M;x++) for(int k=0;k<=M;k++) for(int ny=0;ny<y;ny++) (dp[i][x][ny][k]+=dp[i][x][y][k]*C[y][ny])%=mod;
        for(int a=0;a<i;a++){
            int b=i-a-1;
            for(int x=0;x<=min(M,N-i);x++) for(int y=0;y<=min(M,N-i-x);y++){
                (dp[i][x][y][0]+=g[a][x]*g[b][y])%=mod;
            }
        }

        for(int x=0;x<=min(M,N-i);x++) for(int y=0;y<=min(M,N-i-x);y++) if((x+y)) for(int k=0;k<=M;k++){
            if(!dp[i][x][y][k]) continue;
            int s=(10-k%10+y*9)%10;
            for(int d=s;d<=(x+y)*9;d+=10){
                int nk=(k+d-y*9)/10;
                assert(abs(nk)<=M);
                if(nk>=0) (dp[i+x+y][x][y][nk]+=dp[i][x][y][k]*f[x][y][d])%=mod;
                else (dp[i+x+y][y][x][-nk]+=dp[i][x][y][k]*f[x][y][d])%=mod;
            }
        }
    }
    
    int res=0;
    for(int n=1;n<=N;n++) res=(res+dp[n][0][0][0])%mod;
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
