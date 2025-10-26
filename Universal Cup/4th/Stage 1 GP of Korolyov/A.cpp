#include<bits/stdc++.h>
using namespace std; 
#define int long long 
const int mod = 1e9+9;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}

const int w=884618610;
void solve(){
    int n,m,k;cin >> n >> m >> k;

    int T=max(n,m);
    vector<int> fac(T+1),dfac(T+1);
    fac[0]=1;
    for(int i=1;i<=T;i++) fac[i]=fac[i-1]*i%mod;
    dfac[T]=power(fac[T],mod-2);
    for(int i=T;i>=1;i--) dfac[i-1]=dfac[i]*i%mod;

    array<int,3> A={k+1,0,0};
    if((k+1)%3==1) A[1]=A[2]=1;
    else if((k+1)%3==2) A[1]=1+w,A[2]=mod-w;

    vector<vector<int>> f(3,vector<int>(m+1,1));
    for(int i=0;i<=2;i++) for(int j=1;j<=m;j++) f[i][j]=f[i][j-1]*A[i]%mod;

    int res=0;

    for(int x=0;x<=m;x++) for(int y=0;x+y<=m;y++){
        int z=m-x-y;
        
        int mul=fac[m]*dfac[x]%mod*dfac[y]%mod*dfac[z]%mod;

        array<int,3> B={x,y,z};        
        
        int val=0;
        for(int i=0;i<=2;i++){
            int cur=1;
            for(int j=0;j<=2;j++) cur=cur*f[(i+j)%3][B[j]]%mod;
            val=(val+cur)%mod;
        }
        val=power(val,n);
        res=(res+mul*val)%mod;
    }

    int mul=power(power(3,n+m),mod-2);
    res=res*mul%mod;
    cout << res << '\n';
}   

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}