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

void solve(){
    int n;cin >> n;
    vector<vector<int>> g(n+1,vector<int>(n+1,0));
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) g[i][j]=__gcd(i,j);

    vector<int> f(10*n*n);
    for(int i=1;i*i<10*n*n;i++) f[i*i]=1;

    int cnt=0;
    for(int a=1;a<=n;a++) for(int b=1;b<=n;b++) for(int c=1;c<=n;c++) for(int d=1;d<=n;d++){
        int area=(a+c)*(b+d)/2;
        int side=g[a][b]+g[b][c]+g[c][d]+g[d][a];
        int point=area+1-side/2;
        if(f[point]) cnt++;
    }
    cout << cnt << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
