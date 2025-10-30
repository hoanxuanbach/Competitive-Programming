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

int f[35][2][3];

int g(int n,int x,int y){
    if(!n){
        return ((x^y)==0);
    }
    if(f[n][x][y]!=-1) return f[n][x][y];
    int res=0;
    for(int i=0;i<=1;i++){
        int nx=2*i+x,ny=3*i+y;
        if((nx&1)^(ny&1)^i) continue;
        res+=g(n-1,nx/2,ny/2);
    }
    return f[n][x][y]=res;
};

void solve(){
    int n;cin >> n;
    memset(f,-1,sizeof(f));
    cout << g(n,0,0) << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
