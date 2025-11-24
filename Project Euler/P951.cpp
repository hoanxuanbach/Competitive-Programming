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

map<pii,int> dp[30][30];

pii add(pii a,pii b){
    __int128 X = (__int128)a.first*b.second+(__int128)a.second*b.first;
    __int128 Y = (__int128)a.second*b.second; 
    __int128 g=__gcd(X,Y);
    X/=g;Y/=g;
    return {(int)X,(int)Y};
}
pii mul(pii a,pii b){
    __int128 X = (__int128)a.first*b.first;
    __int128 Y = (__int128)a.second*b.second; 
    __int128 g=__gcd(X,Y);
    X/=g;Y/=g;
    return {(int)X,(int)Y};
}

void solve(){
    int n;cin >> n;

    vector<pii> f(n+1);
    f[0]={0,1};f[1]={1,1};
    for(int i=2;i<=n;i++){
        pii a=f[i-1],b=f[i-2];
        a.first=a.second-a.first;
        b.first=b.second-b.first;
        pii x = add(a,b);
        f[i]=mul(x,{1,2});
    }
    dp[0][0][{0,1}]=1;
    vector<pii> P;
    for(int i=1;i<=n;i++) for(int j=0;j<=n;j++) P.push_back({i,j});
    sort(P.begin(),P.end(),[&](pii a,pii b){
        return a.first+a.second<b.first+b.second;
    });
    for(auto [i,j]:P){
        for(int k=1;k<=i;k++){
            pii a=f[k],b=f[k];
            b.first=b.second-b.first;
            for(auto [x,d]:dp[j][i-k]){
                pii y=x;y.first=y.second-y.first;
                pii T=add(mul(a,y),mul(b,x));
                dp[i][j][T]+=d;
            }
        }
    }

    cout << 2*dp[n][n][{1,2}] << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
