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
    vector<vector<int>> d(N+1);
    for(int i=2;i<=N;i+=2) for(int j=i;j<=N;j+=i) d[j].push_back(i);
    
    vector<int> f(N+1);
    for(int x=2;x<=N;x+=2){
        int cnt=0;
        for(int a:d[x]){
            int b=x/a;
            if(b<=a || (b&1)) continue;
            int p=(a+b)/2,q=(b-a)/2;
            cnt++;
        }
        f[cnt]++;
    }
    int T=0;
    for(int i=1;i<=10;i++) T+=f[i];
    cout << T << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
