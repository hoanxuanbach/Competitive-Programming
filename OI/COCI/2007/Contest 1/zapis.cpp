#include<bits/stdc++.h>
using namespace std;
#define maxn 205
#define int long long
const int mod=1e5;
int n,dp[maxn][maxn],x[maxn][maxn];
bool check[maxn][maxn],checkx[maxn][maxn];
string s;
int f(int i,int j){
    int x=(int)s[i],y=(int)s[j];
    if(x==40 && (y==41 || y==63)) return 1;
    if(x==91 && (y==93 || y==63)) return 1;
    if(x==123 && (y==125 || y==63)) return 1;
    if(x==63){
        if(y==41 || y==93 || y==125) return 1;
        if(y==63) return 3;
    }
    return 0;
}
void print(int a,bool c){
    if(!c) cout << a << '\n';
    else{
        for(int i=10000;i>0;i/=10) cout << (a/i)%10;
        cout << '\n';
    }
    return;
}
signed main(){
    //freopen("ZAP.INP","r",stdin);
    //freopen("ZAP.OUT","w",stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> s;
    s="$"+s;
    for(int i=n-1;i>=1;i--){
        x[i][i+1]=dp[i][i+1]=f(i,i+1);
        for(int j=i+3;j<=n;j+=2){
            x[i][j]=dp[i][j]=f(i,j)*dp[i+1][j-1];
            if(f(i,j)>0 && (x[i][j]>=100000 || check[i+1][j-1])){check[i][j]=checkx[i][j]=true;}
            dp[i][j]%=mod;x[i][j]%=mod;
            for(int k=i+1;k<j;k+=2){
                if(!x[i][k] && !checkx[i][k]) continue;
                if(!dp[k+1][j] && !check[k+1][j]) continue;
                dp[i][j]+=x[i][k]*dp[k+1][j];
                if(checkx[i][k] || check[k+1][j] || dp[i][j]>=100000) check[i][j]=true;
                dp[i][j]%=mod;
            }
        }
    }
    print(dp[1][n],check[1][n]);
}