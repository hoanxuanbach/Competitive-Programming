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

int f[maxn],dfac[maxn],suf[maxn];
int cal(int k,int n){
    dfac[0]=1;
    for(int i=1;i<=n+2;i++) dfac[i]=(dfac[i-1]*power(i,mod-2))%mod;
    for(int i=1;i<=n+2;i++) f[i]=(f[i-1]+power(i,n))%mod;
    if(k<=n+2) return f[k];
    
    n+=2;
    k%=mod;
    suf[n+1]=1;
    for(int i=n;i>=1;i--) suf[i]=(suf[i+1]*(k-i))%mod;
    int ans=0,pre=1;
    for(int i=1;i<=n;i++){
        int mul=(f[i]*pre%mod)*suf[i+1]%mod;
        mul=(mul*dfac[i-1]%mod)*dfac[n-i]%mod;
        if((n-i)&1) mul=(mod-mul)%mod;
        ans=(ans+mul)%mod;
        pre=(pre*(k-i))%mod;
    }
    ans=(ans%mod+mod)%mod;
    return ans;
}

void solve(){
    int N;cin >> N;

    int LIM=1,M=100,K=-1;
    vector<int> p(M),X;
    for(int i=2;i<M;i++) if(!p[i]){
        if(LIM>N/i){
            K=i;
            break;
        }
        X.push_back(i);LIM*=i;
        for(int j=i;j<M;j+=i) p[j]=i;
    }

    int res=N%mod;
    for(int k=1;k<K;k++){
        vector<int> f(K);

        int fact=1;
        for(int i=2;i<=k;i++){
            fact=fact*i%mod;

            int x=i;
            while(x>1){
                int j=p[x];
                while(x%j==0) x/=j,f[j]++;
            }
        }

        int T=1;
        bool ok=true;
        for(int x:X){
            if(!f[x]) continue;
            int d=(f[x]-1)/k+1;
            for(int i=0;i<d;i++){
                if(T>N/x) ok=false;
                else T*=x;
            }
        }
        if(!ok) continue;

        int n=N-k;
        int mul=power(T%mod,k)*power(fact,mod-2)%mod;
        if(k&1) mul=(mod-mul)%mod;
        res=(res+mul*cal(n/T,k))%mod;
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
