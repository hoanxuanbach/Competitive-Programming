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

    vector<int> fac(n+1,1),dfac(n+1,1),inv(n+1,1);
    for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;
    dfac[n]=power(fac[n],mod-2);
    for(int i=n;i>=1;i--){
        dfac[i-1]=dfac[i]*i%mod;
        inv[i]=dfac[i]*fac[i-1]%mod;
    }

    auto C = [&](int N,int K){
        if(N<K || N<0 || K<0) return 0LL;
        return fac[N]*dfac[N-K]%mod*dfac[K]%mod;
    };

    vector<int> g(n),s(n);
    g[0]=s[0]=1;
    for(int i=1;i<n;i++){
        g[i]=s[i-1];
        for(int j=1;j<=i;j++) s[i]=(s[i]-g[j]*s[i-j]%mod*C(i-1,j-1)%mod+mod)%mod;
    }

    vector<int> p(m+1,1);
    p[0]=p[1]=0;
    
    vector<int> prime;
    for(int i=2;i<=m;i++) if(p[i]){
        prime.push_back(i);
        for(int j=i*i;j<=m;j+=i) p[j]=0; 
    }

    vector<int> cc(m+1);
    for(int x:prime){
        int i=m;
        while(i) i/=x,cc[x]+=i;
    }

    /*
    int M=m;
    for(int i=2;i<=M;i++){
        while(M%i==0) cc[i]++,M/=i;
    }
    */

    vector<int> f(2*m,0);f[0]=1;

    auto add = [&](int d){
        //cout << "add " << d << endl;
        for(int i=d;i<2*m;i++) f[i]=(f[i]+f[i-d])%mod;
    };
    auto del = [&](int d){
        //cout << "del " << d << endl;
        for(int i=2*m-1;i>=d;i--) f[i]=(f[i]-f[i-d]+mod)%mod;
    };

    vector<int> X;
    int res=0;

    vector<int> cnt(n);
    auto cal = [&](){

        int val=fac[n];
        for(int x:prime){
            val=val*f[cc[x]]%mod;
        }
        for(int x:X){
            val=val*g[x]%mod;
            val=val*dfac[x]%mod;
            cnt[x]++;
            val=val*inv[cnt[x]]%mod;
            //cout << g[x] << ' ' << dfac[x] << ' ' << inv[cnt[x]] << '\n';
        }
        for(int x:X) cnt[x]=0;
        res=(res+val)%mod;
    };
    function<void(int,int)> dfs = [&](int x,int d){
        d=min(d,x);
        //if(x>1) d=min(d,x-1);
        if(!x){
            cal();
            return;
        }

        X.push_back(d);
        add(d);
        dfs(x-d,d);
        X.pop_back();
        del(d);

        if(d>1) dfs(x,d-1);
    };
    dfs(n,n);
    res=res*dfac[n]%mod;
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
