#include<bits/stdc++.h>
using namespace std; 
#define int long long
#define pii pair<int,int>
#define piii pair<pii,int> 
#define fi first
#define se second
const int inf = 1e18;
const int mod = 1e9+7;
const int inv2 = (mod+1)/2;
const int maxn = 3e2+5;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}

int fac[maxn],dfac[maxn],inv[maxn];
void combi(int n){
    fac[0]=1;
    for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;
    dfac[n]=power(fac[n],mod-2);
    for(int i=n;i>=1;i--){
        dfac[i-1]=dfac[i]*i%mod;
        inv[i]=dfac[i]*fac[i-1]%mod;
    }
}
int C(int n,int k){
    return fac[n]*dfac[k]%mod*dfac[n-k]%mod;
}

int dp[2][maxn][maxn];

void solve(){   
    int n;cin >> n;

    vector<pii> p;
    for(int i=0;i<n;i++){
        int a,b;cin >> a >> b;
        p.push_back({b,0});
        p.push_back({a,1});
    }
    sort(p.begin(),p.end());

    int t=0,c=0;
    dp[0][0][0]=1;
    for(auto [d,x]:p){
        memset(dp[t^1],0,sizeof(dp[t^1]));
        //cout << '*' << d << ' ' << x << '\n';
        for(int i=0;i<=c;i++) for(int j=0;j<=c+1-i;j++){
            //if(dp[t][i][j]) cout << i << ' ' << j << ' ' << dp[t][i][j] << '\n';
            if(x){
                if(j) (dp[t^1][i][j+1]+=dp[t][i][j])%=mod;
                else (dp[t^1][i+1][j]+=dp[t][i][j])%mod;
            }
            else{
                if(i) (dp[t^1][i-1][j]+=dp[t][i][j]*i)%=mod;
                if(j>1) (dp[t^1][i][j-1]+=dp[t][i][j]*(j-1))%=mod;

                (dp[t^1][i+max(0LL,j-1)][1]+=dp[t][i][j])%=mod;
            }
        }
        c+=x;t^=1;
    }
    int res=0;
    for(int i=0;i<=c;i++) res=(res+dp[t][0][i])%mod;
    cout << res << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
/*
5
4 3
3 1
6 5
2 1
4 2
*/