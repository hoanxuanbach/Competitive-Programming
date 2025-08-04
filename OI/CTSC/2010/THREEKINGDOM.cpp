#include<bits/stdc++.h>
using namespace std; 
#define int long long
#define pii pair<int,int>
#define piii pair<pii,int> 
#define fi first
#define se second
const int inf = 1e18;
const int mod = 998244353;
const int inv2 = (mod+1)/2;
const int maxn = 4e5+5;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}

int fac[maxn],dfac[maxn],inv[maxn];
void combi(int n){
    fac[0]=1;
    for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;
    dfac[n]=power(fac[n],mod-2);
    for(int i=n;i>=1;i--){
        dfac[i-1]=dfac[i]*i%mod;
        inv[i]=dfac[i]*fac[i-1]%mod;
    }
}
int C(int n,int k){
    return fac[n]*dfac[k]%mod*dfac[n-k]%mod;
}

int n;
double p[3][3][7][7];
double dp[(1<<18)+5][3][3][7];

void solve(){   
    cin >> n;
    for(int i=0;i<3;i++) for(int j=i+1;j<3;j++) for(int x=0;x<n;x++) for(int y=0;y<n;y++) cin >> p[i][j][x][y],p[j][i][y][x]=1-p[i][j][x][y];
    
    n--;
    for(int mask=0;mask<(1<<(3*n));mask++) for(int i=0;i<3;i++) for(int j=0;j<3;j++) for(int k=0;k<=n;k++){
        if(i==j) continue;
        if(k<n && (mask>>(i*n+k)&1)) continue;
        //cout << mask << ' ' << i << ' ' << j << ' ' << k << endl;

        int x=i^j^3;
        bool check=false;
        double res=0;
        for(int t=0;t<n;t++) if(mask>>(x*n+t)&1){
            double val=dp[mask^(1<<(x*n+t))][i][x][k]*p[i][x][k][t]+dp[mask^(1<<(x*n+t))][x][i][t]*p[x][i][t][k];
            if(!check) res=val;
            else if(!x) res=max(res,val);
            else res=min(res,val);
            check=true;
        }

        if(!check){
            x=j;
            for(int t=0;t<n;t++) if(mask>>(x*n+t)&1){
                double val=dp[mask^(1<<(x*n+t))][i][x][k]*p[i][x][k][t]+dp[mask^(1<<(x*n+t))][x][i][t]*p[x][i][t][k];
                if(!check) res=val;
                else if(!x) res=max(res,val);
                else res=min(res,val);
                check=true;
            }
        }
        if(!check && i==0) res=1;
        //cout << mask << ' ' << i << ' ' << j << ' ' << k << ' ' << res << endl;
        dp[mask][i][j][k]=res;
    }

    double res=0;
    for(int a=0;a<3;a++){
        int b=(a+1)%3,c=(a+2)%3;
        for(int i=0;i<=1;i++) for(int j=0;j<=1;j++){
            int x=(i?c:b);
            double cur=p[x][b^c^x][n][n];
            int y=(j?a:x);
            cur*=p[y][y^a^x][n][n];
            res+=cur*dp[(1<<(3*n))-1][y][y^a^x][n]/3;
        }
    }
    cout << setprecision(6) << fixed << res << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
/*
3
1.0 0.0 0.5
0.5 1.0 1.0
0.5 0.5 0.5

0.5 0.5 1.0
0.5 0.0 0.5 
0.5 0.5 0.5

0.5 0.0 1.0
0.5 0.5 0.5
0.5 0.5 0.5
*/