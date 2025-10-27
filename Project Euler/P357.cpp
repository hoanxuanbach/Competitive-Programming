#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 998244353;
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
    vector<int> p(n+2,1);
    p[0]=p[1]=0;
    for(int i=2;i<=n+1;i++) if(p[i]){
        for(int j=i*i;j<=n+1;j+=i) p[j]=0;
    }

    vector<int> f(n+1,1);
    for(int i=1;i<=n;i++) for(int j=i*i;j<=n;j+=i) if(!p[j/i+i]) f[j]=0;

    int sum=0;
    for(int i=1;i<=n;i++) sum+=f[i]*i;
    cout << sum << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
