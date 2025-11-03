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
    int S;cin >> S;S++;
    vector<int> p(S),phi(S);
    int res=0;
    phi[1]=1;
    for(int i=2;i<S;i++){
        if(!p[i]){
            for(int j=i;j<S;j+=i) p[j]=i;
        }
        phi[i]=phi[i/p[i]];
        if((i/p[i])%p[i]==0) phi[i]*=p[i];
        else phi[i]*=(p[i]-1);
        res+=phi[i];
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
