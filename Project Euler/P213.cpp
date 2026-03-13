#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 998244353;
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

double f[35][35];

double A[35][35],B[35][35];

void solve(){
    int n,k;cin >> n >> k;
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) f[i][j]=1;

    for(int x=1;x<=n;x++) for(int y=1;y<=n;y++){

        for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) A[i][j]=0;
        A[x][y]=1;

        for(int t=0;t<k;t++){
            for(int i=1;i<=n;i++) for(int j=1;j<=n;j++){
                int d=2;
                if(i>1 && i<n) d++;
                if(j>1 && j<n) d++;
                A[i][j]/=d;
            }
            for(int i=1;i<=n;i++) for(int j=1;j<=n;j++){
                B[i][j]=0;
                if(i>1) B[i][j]+=A[i-1][j];
                if(i<n) B[i][j]+=A[i+1][j];
                if(j>1) B[i][j]+=A[i][j-1];
                if(j<n) B[i][j]+=A[i][j+1];
            }   
            for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) A[i][j]=B[i][j];
        }

        for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) f[i][j]*=(1-A[i][j]);
    }

    double res=0;
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) res+=f[i][j];
    cout << setprecision(6) << fixed << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
