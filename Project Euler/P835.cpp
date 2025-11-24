#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 1234567891;
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

#define ld long double
#define range array<int,3>
#define matrix array<range,3> 

range mul(range a,matrix b){
    range c;
    for(int i=0;i<=2;i++){
        c[i]=0;
        for(int j=0;j<=2;j++) c[i]=(c[i]+a[j]*b[j][i])%mod;
    }
    return c;
}
matrix mul(matrix a,matrix b){
    matrix c;
    for(int i=0;i<=2;i++) for(int j=0;j<=2;j++){
        c[i][j]=0;
        for(int k=0;k<=2;k++) c[i][j]=(c[i][j]+a[i][k]*b[k][j])%mod;
    }
    return c;
}
void solve(){
    int N;cin >> N;

    int n=5*power(10,N/2-1)%mod;
    int res=n*(n+1)%mod*(4*n-1)%mod*power(3,mod-2)%mod;

    ld sq=sqrtl(2);
    int m=(int)((N+log10(2*sq))/log10(3+2*sq));

    range A = {0,2,0};
    matrix X = {range{0,mod-1,0},range{1,6,1},range{0,0,1}};

    while(m){
        if(m&1) A=mul(A,X);
        X=mul(X,X);m>>=1;
    }

    res=(res+A[2]+mod-16)%mod;
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
