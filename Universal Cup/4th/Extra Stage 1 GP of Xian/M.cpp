#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 1e9+7;
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
    int n,m;cin >> n >> m;

    bool A=false,B=false,C=false;

    vector<int> a(n);
    int res=1,cnt=0;
    for(int i=0;i<n;i++){
        cin >> a[i];
        if(a[i]==-1) res=res*m%mod,cnt++;
        else if(a[i]==1) A=true;
        else if(a[i]<n) B=true;
        else C=true;
    }
    if(!B){
        if(!C && (n&1)) res=(res+mod-1)%mod;
        if(m>=n){
            int val=1;
            for(int i=0;i<cnt;i++) val=val*(m-n+1)%mod;
            if(!A) res=(res+mod-val)%mod;
            if(a[0]!=1 && a[n-1]!=1){
                int inv=power(m-n+1,mod-2);
                
                int lst=0,sum=0;
                vector<int> dp(n);
                for(int i=1;i<n-1;i++){
                    if(a[i]!=-1 && a[i]!=1) continue;
                    dp[i]=(sum-dp[i-1]+mod)%mod;
                    if(!lst) dp[i]=(dp[i]+1)%mod;
                    if(a[i]==-1){
                        dp[i]=dp[i]*inv%mod;
                        sum=(sum+dp[i])%mod;
                    }
                    else lst=i,sum=dp[i];
                }
                res=(res+mod-val*sum%mod)%mod;
            }
        }
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
