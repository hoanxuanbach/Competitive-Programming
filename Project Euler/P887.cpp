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

const int D = 100;
const int K = 100;

void solve(){
    int N=1;
    for(int x=1;x<=10;x++) N*=7;

    vector<vector<int>> f(K,vector<int>(D+1,1));
    for(int k=1;k<K;k++){
        f[k][0]=f[k-1][0]+1;
        for(int d=1;d<=D;d++) f[k][d]=min(inf,f[k-1][d-1]+f[k-1][min(D,d+f[k-1][d-1]-1)]);
    }

    cout << N << '\n';
    int res=N*(N-1)/2;
    for(int d=1;d<=7;d++){
        for(int k=1;k<K;k++){
            cout << f[k-1][d] << ' ';
            if(f[k-1][d]>N) break;
            res+=(min(f[k][d],N)-f[k-1][d])*k;
        }
        cout << endl;
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
