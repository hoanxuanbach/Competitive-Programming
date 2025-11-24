#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 999676999;
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
    vector<int> p(N+1),d(N+1,1);
    for(int i=2;i<=N;i++){
        if(!p[i]){
            for(int j=i;j<=N;j+=i) p[j]=i;
        }
        d[i]=0;
        int x=i;
        while(x>1){
            int j=p[x];
            d[i]+=(i/j);
            x/=j;
        }
    }
    vector<int> f(N+1);f[0]=1;
    for(int x=1;x<=N;x++){
        for(int i=x;i<=N;i++) f[i]=(f[i]+f[i-x]*d[x])%mod;
    }
    int res=0;
    for(int i=1;i<=N;i++) res=(res+f[i])%mod;
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
