#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 1e9;
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
    vector<int> f(N+1);f[1]=1;
    for(int i=2;i<=N;i++) f[i]=f[i-1]+f[i-2];
    int S=f[N];

    vector<int> X;
    vector<int> p(S+1);
    for(int i=2;i<=S;i++) if(!p[i]){
        X.push_back(i);
        for(int j=i;j<=S;j+=i) p[j]=1;
    }
    
    vector<int> g(S+1);g[0]=1;
    for(int x:X) for(int i=x;i<=S;i++) (g[i]+=g[i-x]*x)%=mod;
    int res=0;
    for(int i=2;i<=N;i++) res=(res+g[f[i]])%mod;
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
