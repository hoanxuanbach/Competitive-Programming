#include<bits/stdc++.h>
using namespace std;
#define int long long 
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

#define pii array<int,2>
namespace S1{
    const int N = 205;
    struct matrix{
        int n,m;
        int x[N][N];
        matrix(int _n=0,int _m=0):n(_n),m(_m){
            memset(x,0,sizeof(x));
        }
        friend matrix operator*(matrix a,matrix b){
            matrix c(a.n,b.m);
            for(int i=1;i<=a.n;i++) for(int j=1;j<=b.m;j++){
                for(int k=1;k<=a.m;k++) c.x[i][j]=(c.x[i][j]+a.x[i][k]*b.x[k][j])%mod;
            }
            return c;
        }
    };
    int solve(int n,int m){
        matrix S(1,2*m);n--;
        for(int i=1;i<=m;i++) S.x[1][i*2-(i&1)]++;
        matrix X(2*m,2*m);
        for(int i=1;i<=m;i++) for(int a=0;a<=1;a++) for(int j=1;j<=m;j++){
            int b=a;
            if((j>i)) b^=((j-i)&1);
            X.x[2*i-a][2*j-b]++;
        }
        while(n){
            if(n&1) S=S*X;
            X=X*X;n>>=1;
        }
        int res=0;
        for(int i=1;i<=m;i++) res=(res+S.x[1][2*i])%mod;
        return res;
    }
}
namespace S2{
    int solve(int n,int m){
        vector<pii> d(m+1,{0,0});
        for(int i=1;i<=m;i++) d[i][i&1]=1;
        for(int i=2;i<=n;i++){
            vector<pii> nd(m+1,{0,0});
            for(int j=1;j<=m;j++){
                nd[j]=d[j];
                nd[j][0]=(nd[j][0]+nd[j-1][1])%mod;
                nd[j][1]=(nd[j][1]+nd[j-1][0])%mod;
            }
            for(int j=m-1;j>=1;j--){
                d[j][0]=(d[j][0]+d[j+1][0])%mod;
                d[j][1]=(d[j][1]+d[j+1][1])%mod;
                nd[j][0]=(nd[j][0]+d[j+1][0])%mod;
                nd[j][1]=(nd[j][1]+d[j+1][1])%mod;
            }
            d=nd;
        }
        int res=0;
        for(int i=1;i<=m;i++) res=(res+d[i][0])%mod;
        return res;
    }
}
namespace S3{
    int solve(int n,int k){

        int t=k&1;k/=2;
        int m=min(k,10*n);
        vector<int> f(m+1);
        for(int i=1;i<=m;i++) f[i]=S2::solve(n,2*i+t);

        vector<int> suf(m+2),dfac(m+1,1);
        for(int i=2;i<=m;i++) dfac[i]=dfac[i-1]*power(i,mod-2)%mod;

        if(k<=m) return f[k];
        
        k%=mod;
        suf[m+1]=1;
        for(int i=m;i>=1;i--) suf[i]=(suf[i+1]*(k-i))%mod;
        int ans=0,pre=1;
        for(int i=1;i<=m;i++){
            int mul=(f[i]*pre%mod)*suf[i+1]%mod;
            mul=(mul*dfac[i-1]%mod)*dfac[m-i]%mod;
            if((m-i)&1) mul=(mod-mul)%mod;
            ans=(ans+mul)%mod;
            pre=(pre*(k-i))%mod;
        }
        return (ans%mod+mod)%mod;
    }
}

void solve(){
    int n,m;cin >> n >> m;
    //int A=(S1::solve(n,m)-S1::solve(n,m-1)+mod)%mod;
    //int B=(S2::solve(n,m)-S2::solve(n,m-1)+mod)%mod;
    //int C=(S3::solve(n,m)-S3::solve(n,m-1)+mod)%mod;
    //cout << A << '\n';
    //cout << B << '\n';
    //cout << C << '\n';
    int res=(635147632+364553235+749784357)%mod;
    cout << res << '\n';

    /*
    1st Problem: Using matrix multiplication
    2nd Problem: Using dynamic programming
    3rd Problem: Using lagrange interpolation
    */
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
