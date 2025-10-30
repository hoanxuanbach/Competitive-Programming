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
    vector<vector<int>> a(n,vector<int>(n,0));
    for(int i=0;i<n;i++) for(int j=0;j<n;j++) cin >> a[i][j];

    vector<int> f(1<<n,-inf);f[0]=0;
    for(int i=1;i<(1<<n);i++){
        int x=__builtin_popcount(i)-1;
        for(int j=0;j<n;j++) if(i>>j&1) f[i]=max(f[i],f[i^(1<<j)]+a[x][j]);
    }
    cout << f[(1<<n)-1] << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
