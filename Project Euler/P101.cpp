#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 1000000000000000003;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=(__int128)res*a%mod;
        a=(__int128)a*a%mod;n>>=1;
    }
    return res;
}

vector<int> cal(vector<int> f,int n,int m){
    vector<int> g(m);
    for(int i=1;i<=n;i++) g[i]=f[i];

    vector<int> fac(n+1,1);
    for(int i=1;i<=n;i++) fac[i]=(__int128)fac[i-1]*i%mod;
    for(int i=1;i<=n;i++) fac[i]=power(fac[i],mod-2);
    for(int k=n+1;k<m;k++){
        vector<int> suf(n+2,1);
        for(int i=n;i>=1;i--) suf[i]=(__int128)suf[i+1]*(k-i)%mod;
        int res=0,pre=1;
        for(int i=1;i<=n;i++){
            int mul=(__int128)f[i]*pre%mod*suf[i+1]%mod;
            mul=(__int128)mul*fac[i-1]%mod*fac[n-i]%mod;
            if((n-i)&1) mul=(mod-mul)%mod;
            res=(res+mul)%mod;
            pre=(__int128)pre*(k-i)%mod;
        }   
        g[k]=res;
    }
    return g;   
}

void solve(){
    int N;cin >> N;
    vector<int> f(2*N);
    for(int i=1;i<2*N;i++){
        int x=1;
        for(int j=0;j<=N;j++){
            if(j&1) f[i]-=x;
            else f[i]+=x;
            x*=i;
        }
    }
    int T=0;
    for(int i=1;i<=N;i++){
        vector<int> g=cal(f,i,2*N);
        int j=i+1;
        while(j<2*N && f[j]==g[j]) j++;
        assert(j<2*N);
        T+=g[j];
        cout << g[j] << '\n';
    }
    cout << T << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
