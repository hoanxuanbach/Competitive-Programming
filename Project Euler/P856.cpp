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

#define ld long double
bool vis[15][15][15][15][5];
ld f[15][15][15][15][5];

ld g(int a,int b,int c,int d,int k){
    if(vis[a][b][c][d][k]) return f[a][b][c][d][k];
    vector<int> X={13-a-b-c-d,a,b,c,d};
    vis[a][b][c][d][k]=true;
    int cnt=52;
    for(int i=1;i<=4;i++) cnt-=X[i]*i;
    if(!cnt) return 0;

    ld res=1;
    for(int i=0;i<=3;i++){
        if(!X[i]) continue;
        int val=(4-i)*(X[i]-(i==k));
        X[i]--;X[i+1]++;
        res+=(ld)val/cnt*g(X[1],X[2],X[3],X[4],i+1);
        X[i]++;X[i+1]--;
    }

    return f[a][b][c][d][k]=res;
}

void solve(){
    ld res=1+g(1,0,0,0,1);
    cout << setprecision(8) << fixed << res << '\n'; 
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
