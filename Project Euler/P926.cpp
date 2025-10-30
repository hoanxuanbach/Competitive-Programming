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

    vector<int> p(N+1),prime;
    for(int i=2;i<=N;i++) if(!p[i]){
        prime.push_back(i);
        for(int j=i*i;j<=N;j+=i) p[j]=i;
    }
    int S=10000;
    vector<int> cnt(S),f(S,1);

    vector<int> g(N+1,1),inv(N+1,1);
    for(int i=2;i<=N;i++) inv[i]=(mod-(mod/i)*inv[mod%i]%mod)%mod;
    for(int x:prime){
        int d=N,k=0;
        while(d) d/=x,k+=d;

        if(k<S) cnt[k]++;

        int s=sqrtl(k),t=1;
        for(int i=1;i<s;i++){
            int l=k/(i+1),r=k/i;
            g[i]=g[i]*(r+1)%mod*inv[l+1]%mod;
        }
        for(int i=1;i<=k/s;i++){
            int d=k/i;
            g[d]=g[d]*(i+1)%mod*inv[i]%mod;
        }
    }

    int res=0;
    for(int i=N-1;i>=1;i--){
        g[i]=(g[i]*g[i+1])%mod;
        res=(res+(g[i]-g[i+1]+mod)*i)%mod;
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
