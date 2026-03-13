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

const int T=200;
int f[20][205][405];

void solve(){
    int n;cin >> n;
    
    int K=137;
    f[0][0][T]=1;
    for(int i=0;i<n;i++) for(int x=0;x<K;x++) for(int d=0;d<=2*T;d++){
        if(!f[i][x][d]) continue;
        for(int a=0;a<=9;a++){
            int b=(a*K+x)%10;
            int nx=(a*K+x)/10;
            f[i+1][nx][d+a-b]+=f[i][x][d];
        }
    }

    int res=0;
    for(int x=0;x<K;x++){
        int s=x,d=T;
        while(s) d+=s%10,s/=10;
        res+=f[n][x][d];
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
