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
ld f[105][105][2];

void solve(){
    int N;cin >> N;
    for(int i=0;i<=N;i++) f[i][0][0]=f[i][0][1]=1;
    for(int x=1;x<=N;x++) for(int y=1;y<=N;y++){
        for(int t=0;(1<<t)<=y*2;t++){
            int ny=max(0LL,y-(1<<t)),nd=(1<<(t+1));
            ld cur=(f[x-1][y][1]*nd+f[x][ny][0])/(nd+1);
            f[x][y][0]=max(f[x][y][0],cur);
            f[x][y][1]=max(f[x][y][1],f[x][ny][0]/nd+f[x][y][0]*(nd-1)/nd);
        }
    }
    cout << setprecision(8) << fixed << f[N][N][0] << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
