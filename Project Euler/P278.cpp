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
    int N;cin >> N;
    vector<int> P,f(N);
    for(int i=2;i<N;i++) if(!f[i]){
        P.push_back(i);
        for(int j=i;j<N;j+=i) f[j]=i;
    }
    int S=(int)P.size(),res=0;
    for(int i=0;i<S;i++) for(int j=i+1;j<S;j++) for(int k=j+1;k<S;k++) res+=2*P[i]*P[j]*P[k]-P[i]*P[j]-P[i]*P[k]-P[j]*P[k];
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
