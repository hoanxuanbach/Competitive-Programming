#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 1234567891011;
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

#define range array<int,2>
#define matrix array<range,2>

range mul(range a,matrix b){
    range c;
    for(int i=0;i<=1;i++){
        c[i]=0;
        for(int j=0;j<=1;j++) c[i]=(c[i]+(__int128)a[j]*b[j][i]%mod)%mod;
    }
    return c;
}
matrix mul(matrix a,matrix b){
    matrix c;
    for(int i=0;i<=1;i++) for(int j=0;j<=1;j++){
        c[i][j]=0;
        for(int k=0;k<=1;k++) c[i][j]=(c[i][j]+(__int128)a[i][k]*b[k][j]%mod)%mod;
    }
    return c;
}

matrix T[105];

void init_fib(){
    T[0]={range{0,1},range{1,1}};
    for(int i=1;i<=60;i++) T[i]=mul(T[i-1],T[i-1]);
}
int cal_fib(int n){
    range S={1,0};
    for(int i=0;i<60;i++) if(n>>i&1) S=mul(S,T[i]);
    return S[1];
}


void solve(){
    init_fib();
    int L,res=0;cin >> L;
    int S=10000000,T=100000;

    vector<int> f(S),g(S);
    for(int i=2;i<S;i++) if(!f[i]){
        for(int j=i;j<S;j+=i) f[j]=1;
        int lt=((L+i-1)/i)*i;
        for(int j=lt;j<L+S;j+=i) g[j-L]=1;
    }
    for(int i=0;i<S;i++){
        if(!g[i]){
            res=(res+cal_fib(L+i))%mod;
            T--;
        }
        if(!T) break;
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
