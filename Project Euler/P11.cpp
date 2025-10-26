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
    int N=20,K=4;
    vector<vector<int>> a(N,vector<int>(N));
    int res=0;
    for(int i=0;i<N;i++) for(int j=0;j<N;j++){
        cin >> a[i][j];
        if(i>=K-1){
            int cur=1;
            for(int x=0;x<K;x++) cur*=a[i-x][j];
            res=max(res,cur);
        }
        if(j>=K-1){
            int cur=1;
            for(int x=0;x<K;x++) cur*=a[i][j-x];
            res=max(res,cur);
        }
        if(i>=K-1 && j>=K-1){
            int cur=1;
            for(int x=0;x<K;x++) cur*=a[i-x][j-x];
            res=max(res,cur);
        }
        if(i>=K-1 && j+K<=N){
            int cur=1;
            for(int x=0;x<K;x++) cur*=a[i-x][j+x];
            res=max(res,cur);
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
