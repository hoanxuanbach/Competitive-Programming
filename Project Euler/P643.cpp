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
    int N;cin >> N;

    int S=1e7;
    vector<int> p(S),phi(S),f(S);
    phi[1]=f[1]=1;
    for(int i=2;i<S;i++){
        if(!p[i]){
            for(int j=i;j<S;j+=i) p[j]=i;
        }
        phi[i]=phi[i/p[i]];
        if((i/p[i])%p[i]==0) phi[i]*=p[i];
        else phi[i]*=(p[i]-1);
        f[i]=(f[i-1]+phi[i])%mod;
    }

    int T=1e6;
    vector<int> g(T,-1);
    function<int(int)> get = [&](int x){
        if(N/x<S) return f[N/x];
        else if(g[x]!=-1) return g[x];
        int n=N/x;
        g[x]=((__int128)n*(n+1)/2)%mod;

        int s=sqrtl(n);
        for(int i=1;i<s;i++){
            int cnt=(n/i-n/(i+1))%mod;
            g[x]=(g[x]-cnt*f[i]%mod+mod)%mod;
        }
        for(int i=2;i<=n/s;i++) g[x]=(g[x]-get(x*i)+mod)%mod;
        return g[x];
    };
    int res=0;
    for(int x=2;x<=N;x*=2) res=(res+get(x)+mod-1)%mod;
    cout << res << '\n';
    
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
