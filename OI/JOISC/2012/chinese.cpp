#include<bits/stdc++.h>
using namespace std; 
#define int long long
#define pii pair<int,int>
#define piii pair<pii,int> 
#define fi first
#define se second
const int inf = 1e18;
const int mod = 998244353;
const int inv2 = (mod+1)/2;
const int maxn = 4e5+5;
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

void solve(){   
    int n;cin >> n;
    vector<bool> f(n);
    for(int i=2;i<=n;i++){
        int a;cin >> a;
        f[(a-i+n)%n]=1;
    }
    vector<int> ans(n,n);
    int mn=2*n,cur=2*n;
    for(int i=2*n-1;i>=0;i--){
        if(f[(i+1)%n]) cur=n-1;
        else cur--;
        mn=min(mn+1,cur);
        ans[i%n]=min(ans[i%n],mn);
    }
    mn=2*n,cur=2*n;
    for(int i=0;i<2*n;i++){
        if(f[(i+n-1)%n]) cur=n-1;
        else cur--;
        mn=min(mn+1,cur);
        ans[i%n]=min(ans[i%n],mn);
    }
    for(int i=0;i<n;i++) cout << ans[i]+min(i,n-i) << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}