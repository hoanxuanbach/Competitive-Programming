#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 250;
const int MOD = 1e16;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}

void solve(){
    int N=250250,S=250;
    vector<int> f(S);f[0]=1;
    for(int i=1;i<=N;i++){
        int x=power(i,i);
        vector<int> g=f;
        for(int k=0;k<S;k++) (g[(k+x)%S]+=f[k])%=MOD;
        swap(f,g);
    }
    int res=(f[0]+MOD-1)%MOD;
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
