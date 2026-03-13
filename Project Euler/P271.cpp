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

    int n=N;
    vector<int> X;
    for(int i=2;i*i<=n;i++){
        if(n%i==0){
            int k=0;
            while(n%i==0) n/=i,k++;
            X.push_back(i);
        }
    }
    if(n>1) X.push_back(n);
    
    int sz=(int)X.size();
    vector<vector<int>> F(sz);
    for(int j=0;j<sz;j++){
        int x=X[j];
        for(int i=1;i<x;i++) if((i*i*i)%x==1) F[j].push_back(i);
    }
    int res=0;
    function<void(int,int,int)> dfs = [&](int i,int x,int d){
        if(i==sz){
            res+=x;
            return;
        }
        for(int k:F[i]){
            int nx=x;
            while(nx%X[i]!=k) nx+=d;
            dfs(i+1,nx,d*X[i]);
        }
    };
    dfs(0,0,1);
    cout << res-1 << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
