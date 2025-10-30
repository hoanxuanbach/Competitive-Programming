#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int mod = 1123581313;
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

#define matrix array<array<int,2>,2>
#define pii array<int,2>

matrix mul(matrix a,matrix b){
    matrix c;
    for(int i=0;i<=1;i++) for(int j=0;j<=1;j++){
        c[i][j]=0;
        for(int k=0;k<=1;k++) (c[i][j]+=a[i][k]*b[k][j])%=mod;
    }
    return c;
}
pii mul2(pii a,matrix b){
    pii c={0,0};
    for(int i=0;i<=1;i++) for(int j=0;j<=1;j++) c[j]=(c[j]+a[i]*b[i][j])%mod;
    return c;
}

void solve(){
    int n;cin >> n;

    vector<matrix> A(n+1),B(n+1);
    A[0]=B[0]={pii{1,0},pii{0,1}};
    A[1]={pii{1,3},pii{1,2}};
    B[1]={pii{mod-1,1},pii{1,2}};
    for(int i=2;i<=n;i++){
        A[i]=mul(A[i-1],A[i-2]);
        B[i]=mul(B[i-1],B[i-2]);
    }
    int res=0;
    for(int i=2;i<=n;i++){
        pii x={0,1};
        x=mul2(x,A[i]);
        x[1]=(x[1]+2*(mod-x[0]))%mod;
        swap(x[0],x[1]);
        for(int j=2;j<=n;j++){
            pii y=mul2(x,B[j]);
            res=(res+y[1])%mod;
        }
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
