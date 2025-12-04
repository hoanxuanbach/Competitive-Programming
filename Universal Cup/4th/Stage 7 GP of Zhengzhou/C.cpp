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

int fac[maxn],dfac[maxn];
void combi(int n){
    fac[0]=1;
    for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;
    dfac[n]=power(fac[n],mod-2);
    for(int i=n;i>=1;i--) dfac[i-1]=dfac[i]*i%mod;
}
int C(int n,int k){
    if(n<0 || k<0 || n<k) return 0;
    return fac[n]*dfac[k]%mod*dfac[n-k]%mod;
}

vector<int> lagrange_interpolation(vector<int> X,vector<int> Y){
    int n=(int)X.size();
    vector<int> f(n+1),a(n);
    
    f[0]=1;
    for(int i=0;i<n;i++){
        for(int j=i;j>=0;j--) f[j+1]=(f[j+1]+f[j])%mod,f[j]=f[j]*(mod-X[i])%mod;
    }

    for(int i=0;i<n;i++){
        int mul=1;
        for(int j=0;j<n;j++) if(i!=j) mul=mul*(X[i]-X[j])%mod;
        mul=power(mul,mod-2);
        mul=mul*Y[i]%mod;

        int d=f[n];
        for(int j=n-1;j>=0;j--){
            a[j]=(a[j]+d*mul)%mod;
            d=(f[j]+d*X[i])%mod;
        }
    }

    for(int i=0;i<n;i++) a[i]=(a[i]+mod)%mod;
    return a;
}

void solve(){
    int n;cin >> n;combi(n);

    vector<int> Q(n+1);
    for(int i=1;i<=n;i++) cin >> Q[i];
    vector<vector<int>> g(n+1);
    for(int i=1;i<n;i++){
        int u,v;cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<int> ord,sz(n+1);
    function<void(int,int)> dfs = [&](int u,int p){
        sz[u]=1;
        if(p) g[u].erase(find(g[u].begin(),g[u].end(),p));
        for(int v:g[u]) dfs(v,u),sz[u]+=sz[v];
        ord.push_back(u);
    };
    dfs(1,0);

    vector<vector<int>> dp(n+1,vector<int>(n+1,0)),f(n+1,vector<int>(n+1,0));
    for(int x=0;x<=n;x++){
        for(int u:ord){
            
            vector<int> tmp(sz[u]+1);
            int s=0;tmp[0]=1;

            for(int v:g[u]){
                for(int i=s;i>=0;i--){
                    for(int j=1;j<=sz[v];j++) tmp[i+j]=(tmp[i+j]+tmp[i]*dp[v][j])%mod;
                    tmp[i]=tmp[i]*dp[v][0]%mod;
                }
                s+=sz[v];
            }

            dp[u][0]=0;
            for(int i=0;i<=s;i++){
                dp[u][0]=(dp[u][0]+tmp[i])%mod;
                dp[u][i+1]=tmp[i]*x%mod;
            }

            for(int i=1;i<=sz[u];i++) f[u][x]=(f[u][x]+dp[u][i]*Q[i])%mod;
        }
    }


    for(int u=1;u<=n;u++){
        vector<int> X(sz[u]+1),Y(sz[u]+1);
        for(int i=0;i<=sz[u];i++) X[i]=i,Y[i]=f[u][i];
        
        X=lagrange_interpolation(X,Y);

        for(int k=1;k<=n;k++){
            int res=0;
            for(int i=1;i<=min(k,sz[u]);i++){
                if(sz[u]-i>n-k) continue;
                res=(res+X[i]*dfac[k-i]%mod*dfac[n-k-sz[u]+i])%mod;
            }
            res=res*fac[k-1]%mod*fac[n-k]%mod*fac[n-sz[u]]%mod;
            cout << res << ' ';
        }
        cout << '\n';
    }
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
