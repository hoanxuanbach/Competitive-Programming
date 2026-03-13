#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 1e8;
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

const int N = 35;
int A[N][N],B[N][N],C[N][N];

void solve(){
    int n;cin >> n;
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++){
        if(i==1 || j==1) A[i][j]=1;
        else A[i][j]=(A[i-1][j]+A[i][j-1])%mod;
    }

    for(int i=0;i<=n;i++) for(int j=0;j<=n;j++){
        if(i>j) B[i][j]=B[j][i];
        else if(i==0) B[i][j]=A[j][n];
        else{
            B[i][j]=(B[i-1][j]+B[i][j-1])%mod;
            for(int k=1;k<n;k++) B[i][j]=(B[i][j]+A[i][k]*A[j][n-k])%mod;
        }
    }

    for(int i=0;i<=n;i++) for(int j=0;j<=n;j++){
        if(i>j) C[i][j]=C[j][i];
        else if(i==0) C[i][j]=B[j][n];
        else{
            C[i][j]=(C[i-1][j]+C[i][j-1]+A[i][n]*A[j][n])%mod;
            for(int k=1;k<n;k++) C[i][j]=(C[i][j]+A[i][k]*B[n-k][j]+B[i][k]*A[n-k][j])%mod;
        }
    }

    int res=(C[n-1][n-1]+A[n-1][n]*A[n][n])%mod;
    for(int i=1;i<n;i++) res=(res+A[n-1][i]*B[n-i][n]+B[n-1][i]*A[n-i][n])%mod;
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
