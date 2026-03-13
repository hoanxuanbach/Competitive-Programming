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

int C[25][25];

int f[15][25][75];

void solve(){
    int N,K,S,T;cin >> N >> K >> S >> T;

    for(int i=0;i<=N;i++){
        C[i][0]=1;
        for(int j=1;j<=i;j++) C[i][j]=C[i-1][j]+C[i-1][j-1];
    }

    f[K][0][0]=1;
    for(int i=K;i>=1;i--) for(int j=0;j<=N;j++) for(int s=0;s<=S;s++){
        if(!f[i][j][s]) continue;
        for(int d=0;j+d<=N;d++){
            int k=min(max(0LL,T-j),d);
            int mul=C[j+d][d],ns=s+k*i;
            if(ns<=S) f[i-1][j+d][ns]+=f[i][j][s]*mul;
        }
    }
    cout << f[0][N][S] << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
