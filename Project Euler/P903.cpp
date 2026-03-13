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
    int n;cin >> n;
    
    vector<int> f(n+1);f[n]=1;
    for(int i=n-1;i>=1;i--) f[i]=f[i+1]*(n-i)%mod;

    vector<int> inv(n+1),fac(n+1,1);
    for(int i=1;i<=n;i++) inv[i]=power(i,mod-2),fac[i]=fac[i-1]*i%mod;
    int cnt=fac[n];


    /*
            B = (i<j)(j-2)*f[i]
            A = (i<j)(n-i-2)*f[i]
            C = (i<j)(i-1)*f[i]
            D = (i<j)(n-j)*f[i]
    */

    int A=0,B=0,C=0,D=0,sum=0;
    for(int i=1;i<n;i++){
        A=(A+(n-i-1)*f[i]%mod*(n-i))%mod;
        if(i>1) B=(B+(i-2)*sum)%mod;
        C=(C+(i-1)*f[i]%mod*(n-i))%mod;
        D=(D+(n-i)*sum)%mod;
        sum=(sum+f[i])%mod;
    }
    if(n>1) B=(B+(n-2)*sum)%mod;

    vector<int> p(n+1);
    for(int i=2;i<=n;i++) if(!p[i]){
        for(int j=i;j<=n;j+=i) p[j]=i;
    }

    vector<vector<int>> g(n+1);
    for(int i=1;i<=n;i++){
        for(int j=i;j<=n;j+=i) g[i].push_back(inv[j]);
        for(int j=1;j<(int)g[i].size();j++) g[i][j]=(g[i][j]+g[i][j-1])%mod;
    }

    auto calg = [&](int mx,int x){
        vector<int> S;
        while(x>1){
            int j=p[x];
            while(x%j==0) x/=j;
            S.push_back(j);
        }
        int m=(int)S.size(),ret=0;
        for(int mask=0;mask<(1<<m);mask++){
            int val=1,mul=1;
            for(int i=0;i<m;i++) if(mask>>i&1) val*=S[i],mul*=-1;
            if(val<=mx) ret=(ret+mul*g[val][mx/val-1])%mod;
        }
        return (ret+mod)%mod;
    };
    auto cal = [&](int mx,int x){
        vector<int> S;
        while(x>1){
            int j=p[x];
            while(x%j==0) x/=j;
            S.push_back(j);
        }
        int m=(int)S.size(),ret=0;
        for(int mask=0;mask<(1<<m);mask++){
            int val=1,mul=1;
            for(int i=0;i<m;i++) if(mask>>i&1) val*=S[i],mul*=-1;
            ret=(ret+mul*(mx/val))%mod;
        }
        return (ret+mod)%mod;
    };


    int res=cnt;
    for(int g=1;g<=n;g++) for(int x=g;x<=n;x+=g){
        int k=x/g-1;
        int val=(C+D)*k%mod*fac[n-3]%mod*inv[x]%mod;
        
        int mx=(n-x)/g;
        val=val*calg(mx,x/g)%mod;
        res=(res+val)%mod;
    }

    for(int g=1;g<=n;g++) for(int x=g;x<=n;x+=g){
        int mx=(n-x)/g;
        int val=(cnt-1)*fac[n-2]%mod*inv[2]%mod*inv[x]%mod;
        res=(res-val*calg(mx,x/g)%mod*(x/g-1)%mod+mod)%mod;
        res=(res+val*(x-1)%mod*cal(mx,x/g))%mod;
    }

    for(int x=2;x<=n;x++){
        int mul=inv[x];

        int total=0;
        if(x%2==0){
            int d=x/2;
            int k=x-2;
            total=(total+(cnt-1)*fac[n-2])%mod;
            int val=(cnt-1)*k%mod*fac[n-2]%mod*inv[2]%mod;
            total=(total+val)%mod;
        }

        int k=x-3;
        int val=(A+B)*fac[n-3]%mod;
        val=(val+(cnt-1)*k%mod*fac[n-2]%mod*inv[2]%mod)%mod;

        int dd=(x-1)-(x%2==0);
        total=(total+val*dd)%mod;
        res=(res+total*mul)%mod;
    }
    
    res=res*cnt%mod;
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
