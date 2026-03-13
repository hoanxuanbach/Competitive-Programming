#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 1000267129;
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
    int N,S=10;cin >> N;
    
    vector<int> d(1<<S),f(1<<S);
    for(int x=1;x<S;x++) f[1<<x]++,d[1<<x]++;
    for(int i=1;i<N;i++){
        vector<int> g(1<<S);
        for(int x=0;x<(1<<S);x++) for(int k=0;k<S;k++) (g[x|(1<<k)]+=f[x])%=mod;
        for(int x=0;x<(1<<S);x++) d[x]=(d[x]+g[x])%mod;
        swap(f,g);
    }
    
    int res=0;
    for(int x=0;x<(1<<S);x++) for(int y=0;y<(1<<S);y++) if((x&y)) res=(res+d[x]*d[y])%mod;
    
    int val=1;
    for(int i=0;i<N;i++) val=val*10%mod;
    res=(res+mod-val+1)%mod;
    res=(res*(mod+1)/2)%mod;
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
