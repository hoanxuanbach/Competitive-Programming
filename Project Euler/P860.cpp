#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 989898989;
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
    vector<vector<int>> C(n+1,vector<int>(n+1,0));
    for(int i=0;i<=n;i++){
        C[i][0]=1;
        for(int j=1;j<=i;j++) C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
    }

    int res=0;
    for(int x=0;x<=n;x++) for(int d=0;2*x+d<=n;d+=2){
        int y=x+d;
        int s=n-x-y;
        int a=(2*s-d/2)/4;
        if(a<0) continue;
        if(4*a+d/2!=2*s) continue;
        int b=s-a;
        //cout << x << ' ' << y << ' ' << a << ' ' << b << '\n';
        int val=C[n][x]*C[n-x][y]%mod*C[n-x-y][a]%mod;
        if(!d) res=(res+val)%mod;
        else res=(res+2*val)%mod;
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
