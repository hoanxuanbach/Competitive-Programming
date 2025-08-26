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
    int n,m,q;cin >> n >> m >> q;

    vector<vector<int>> T(n,vector<int>(n,0));
    for(int i=0;i<m;i++){
        int a,b,t;cin >> a >> b >> t;a--;b--;
        T[a][b]+=t;
    }

    vector<vector<int>> dp(1<<n);
    for(int x=0;x<(1<<n);x++) dp[x].assign(1<<__builtin_popcount(x),-1);
    dp[0][0]=0;

    vector<vector<int>> C(1<<n,vector<int>(1<<n,0));
    for(int x=0;x<(1<<n);x++){
        int Y=(1<<n)-1-x;
        for(int y=Y;y;y=(y-1)&Y){
            int val=0;
            for(int i=0;i<n;i++){
                if(!(y>>i&1)) continue;
                for(int j=0;j<n;j++){
                    if(y>>j&1) val+=T[i][j];
                    else if(x>>j&1) val+=T[i][j]+2*T[j][i];
                }
            }
            for(int i=0;i<(int)dp[x].size();i++){
                if(dp[x][i]<0) continue;
                int nx=x|y,ni=2*i+__builtin_popcount(y);
                dp[nx][ni]=max(dp[nx][ni],dp[x][i]*2+val);
            }
        }
    }

    auto g = [&](pii a,pii b){
        if(a.first*b.second>a.second*b.first) return a;
        else return b;
    };

    vector<pii> f(1<<n,{0,1});
    for(int x=0;x<(1<<n);x++){
        for(int i=1;i<(int)dp[x].size();i++) f[x]=g(f[x],{dp[x][i],i});
        for(int i=0;i<n;i++) if(x>>i&1) f[x]=g(f[x],f[x^(1<<i)]);
    }
    for(int i=0;i<q;i++){
        string s;cin >> s;
        int x=0;
        for(int j=0;j<n;j++) x+=(s[j]-'0')<<j;
        int g=__gcd(f[x].first,f[x].second);
        cout << f[x].first/g << '/' << f[x].second/g << '\n';
    }
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
