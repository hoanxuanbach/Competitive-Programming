#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 10000000000000000;
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
    int N,S=0;cin >> N;
    vector<int> f(N),X;
    for(int i=2;i<N;i++) if(!f[i]){
        X.push_back(i);S+=i;
        for(int j=i;j<N;j+=i) f[j]=1;
    }

    cout << (int)X.size() << ' ' << S << '\n';
    f.assign(S+1,0);f[0]=f[1]=1;
    for(int i=2;i<=S;i++) if(!f[i]){
        for(int j=i*2;j<=S;j+=i) f[j]=1;
    }

    vector<int> g(S+1,0);g[0]=1;S=0;
    for(int x:X){
        for(int i=S;i>=0;i--) g[i+x]=(g[i+x]+g[i])%mod;
        S+=x;
    }
    int res=0;
    for(int i=2;i<=S;i++) if(!f[i]) res=(res+g[i])%mod;
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
