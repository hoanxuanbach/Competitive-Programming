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

#define range array<int,5>
#define matrix array<range,5>

matrix mul(matrix a,matrix b){
    matrix c;
    for(int i=0;i<5;i++) for(int j=0;j<5;j++){
        c[i][j]=0;
        for(int k=0;k<5;k++) c[i][j]=(c[i][j]+a[i][k]*b[k][j])%mod;
    }
    return c;
}
range mul(range a,matrix b){
    range c;
    for(int i=0;i<5;i++){
        c[i]=0;
        for(int j=0;j<5;j++) c[i]=(c[i]+a[j]*b[j][i])%mod;
    }
    return c;
}

void solve(){
    int n;cin >> n;

    matrix S;
    for(int i=0;i<5;i++) for(int j=0;j<5;j++) S[i][j]=0;
    S[1][0]=2;
    S[2][0]=1;
    S[3][0]=1;
    S[4][1]=1;
    S[0][1]=1;
    S[0][2]=1;
    S[1][3]=2;
    S[3][3]=1;
    S[0][4]=1;
    S[4][4]=1;

    n--;
    range res={1,0,0,0,0};
    while(n){
        if(n&1) res=mul(res,S);
        S=mul(S,S);n>>=1;
    }
    cout << (res[0]+res[4])%mod << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
