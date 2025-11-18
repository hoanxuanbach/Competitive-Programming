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
    vector<int> d(N+1);
    for(int i=1;i<=N;i++) for(int j=i;j<=N;j+=i) d[j]+=i;
    for(int i=1;i<=N;i++) d[i]+=d[i-1];
    int T=0,res=0;
    for(int a=1;a*a<=N;a++){
        for(int b=0;a*a+b*b<=N;b++){
            if(__gcd(a,b)!=1) continue;
            int k=a*a+b*b,mul=(1+(b>0));
            res+=d[N/k]*a*mul;
        }
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
