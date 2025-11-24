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
    vector<int> p(N+1),phi(N+1,1);
    int res=0;
    for(int i=2;i<=N;i++){
        if(!p[i]){
            for(int j=i;j<=N;j+=i) p[j]=i;
        }
        int x=p[i];
        if((i/x)%x==0) phi[i]=phi[i/x]*x;
        else phi[i]=phi[i/x]*(x-1);
        res+=(i-phi[i]);
    }
    cout << 6*res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
