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

const int N = 70;
int C[N+5][N+5];

void solve(){
    for(int i=0;i<=N;i++){
        C[i][0]=1;
        for(int j=1;j<=i;j++) C[i][j]=min(inf,C[i-1][j]+C[i-1][j-1]);
    }

    int T;cin >> T;T--;
    int res=T*5;
    
    int X=0;
    while(T){
        cout << X << endl;
        int cnt=0;
        for(int i=0;4*i<=X;i++) cnt+=C[X-3*i][i];
        int k=min(cnt,T);
        res+=k*X;
        X++;T-=k;
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
