#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 1307674368000;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=(__int128)res*a%mod;
        a=(__int128)a*a%mod;n>>=1;
    }
    return res;
}
 
const int maxn = 2e5+5;
const int inf = 1e18;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}

#define range array<int,3>
#define matrix array<range,3>

range mul(range a,matrix b){
    range c;
    for(int i=0;i<=2;i++){
        c[i]=0;
        for(int j=0;j<=2;j++) c[i]=(c[i]+(__int128)a[j]*b[j][i]%mod)%mod;
    }
    return c;
}
matrix mul(matrix a,matrix b){
    matrix c;
    for(int i=0;i<=2;i++) for(int j=0;j<=2;j++){
        c[i][j]=0;
        for(int k=0;k<=2;k++) c[i][j]=(c[i][j]+(__int128)a[i][k]*b[k][j]%mod)%mod;
    }
    return c;
}


void solve(){    
    int n;cin >> n;

    int res=0;
    int L,R;cin >> L >> R;
    for(int x=L;x<=R;x++){
        range S={0,x,1};
        matrix X={range{0,x*x,0},range{1,x,0},{0,x,1}};
        int m=n-1;
        while(m){
            if(m&1) S=mul(S,X);
            X=mul(X,X);m>>=1;
        }
        res=(res+S[1])%mod;
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
