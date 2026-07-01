#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 1e9;
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

int f(int x){
    return (x*x)%mod;
}

array<int,4> g[10005][3][3];

array<int,4> add(array<int,4> A,array<int,4> B){
    for(int i=0;i<4;i++) (A[i]+=B[i])%=mod;
    return A;
}

void build(int n){
    g[1][0][1]={1,0,0,0};
    g[1][0][2]={1,1,0,0};
    g[1][1][0]={0,0,1,0};
    g[1][1][2]={0,1,0,0};
    g[1][2][0]={0,0,1,1};
    g[1][2][1]={0,0,0,1};

    for(int i=2;i<=n;i++){
        for(int x=0;x<=2;x++) for(int y=0;y<=2;y++) if(x!=y){
            int z=3^x^y;
            g[i][x][y]=add(add(add(add(g[i-1][x][z],g[1][z][x]),g[1][x][y]),g[1][y][z]),g[i-1][z][y]);
        }
        auto [a,b,c,d]=g[i][0][2];
        if(a!=b || c!=d || a!=(c+1)%mod){
            cout << i << ' ' << a << ' ' << b << ' ' << c << ' ' << d << '\n';
        }
    }
}


int E(int n,int K,int A,int B,int C){

    vector<int> d(4);
    d[0]=(f(B-1)-f(A-1)+mod)%mod;
    d[1]=(f(C-1)-f(B-1)+mod)%mod;
    d[2]=(f(K-A)-f(K-B)+mod)%mod;
    d[3]=(f(K-B)-f(K-C)+mod)%mod;
    int ret=d[2];
    for(int i=0;i<4;i++) ret=(ret+d[i]*g[n][0][2][i])%mod;
    return ret;
}


void solve(){
    int N;cin >> N;
    build(N);
    int K=1,A=1,B=1,C=1;
    int res=0;
    for(int n=1;n<=N;n++){
        K=K*10%mod;
        A=A*3%mod;
        B=B*6%mod;
        C=C*9%mod;
        res=(res+E(n,K,A,B,C))%mod;
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
