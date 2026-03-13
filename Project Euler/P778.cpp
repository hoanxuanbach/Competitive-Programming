#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 1e9+9;
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


const int K=6;
const int S=10;

void solve(){
    int N,M;cin >> N >> M;
    
    vector<vector<int>> d(K,vector<int>(S,0));
    for(int i=0;i<=M;i++){
        int x=i;
        for(int j=0;j<K;j++) d[j][x%S]++,x/=S;
    }

    int dd=1,res=0;
    for(int x=0;x<K;x++){
        auto mul = [&](vector<vector<int>> a,vector<vector<int>> b){
            vector<vector<int>> c(S,vector<int>(S,0));
            for(int i=0;i<S;i++) for(int j=0;j<S;j++) for(int k=0;k<S;k++) c[i][j]=(c[i][j]+a[i][k]*b[k][j])%mod;
            return c;
        };
        
        vector<vector<int>> f(S,vector<int>(S,0));
        for(int i=0;i<S;i++) for(int k=0;k<S;k++) f[i][(i*k)%S]+=d[x][k];

        vector<vector<int>> g(S,vector<int>(S,0));
        for(int i=0;i<S;i++) g[i][i]=1;
        
        int n=N;
        while(n){
            if(n&1) g=mul(g,f);
            f=mul(f,f);n>>=1;
        }
        for(int i=0;i<S;i++) res=(res+g[1][i]*i*dd)%mod;
        dd*=10;
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
