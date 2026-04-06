#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 1e9;
const int phi = 4e8;
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

int C(int n,int k){
    if(n<k || k<0 || n<0) return 0;
    int res=1,d2=0,d5=0,dd=1;
    for(int i=0;i<k;i++){
        int x=n-i;
        while(x%2==0) x/=2,d2++;
        while(x%5==0) x/=5,d5++;
        res=res*x%mod;
        x=i+1;
        while(x%2==0) x/=2,d2--;
        while(x%5==0) x/=5,d5--;
        dd=dd*x%mod;
    }
    for(int i=0;i<d2;i++) res=res*2%mod;
    for(int i=0;i<d5;i++) res=res*5%mod;
    res=res*power(dd,phi-1)%mod;
    return res;
}

void solve(){
    int N;cin >> N;
    vector<int> g(N),S={2,3,5,7};

    vector<int> T(5);T[0]++;
    for(int i=1;i<N;i++){
        vector<int> f(5);
        for(int x:S) if(i>=x) f[g[i-x]]++;
        while(f[g[i]]) g[i]++;
        T[g[i]]++;
    }
    
    vector<int> A(8);
    for(int i=0;i<=4;i++) for(int j=0;j<=4;j++) (A[i^j]+=T[i]*T[j])%=mod;
    
    int K;cin >> K;
    vector<int> dp(8);
    dp[0]=1;
    
    for(int i=1;i<=K;i++){
        vector<int> ndp(8);
        for(int x=0;x<8;x++) for(int d=0;d<8;d++) (ndp[x^d]+=dp[x]*A[d])%=mod;
        swap(dp,ndp);
    }
    int res=0;
    for(int i=1;i<8;i++) res=(res+dp[i])%mod;
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
