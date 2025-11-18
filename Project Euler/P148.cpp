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

    int S=7;
    vector<int> X;
    while(N) X.push_back(N%S),N/=S;
    int T=(int)X.size();
    vector<vector<int>> dp(T+1,vector<int>(2,-1));
    function<int(int,int)> cal = [&](int i,int k){
        if(i==T) return k;
        if(dp[i][k]!=-1) return dp[i][k];
        int res=0;
        for(int x=0;x<S;x++){
            if(!k && x>X[i]) res+=cal(i+1,k)*(x+1);
            if(x==X[i]) res+=cal(i+1,k)*(x+1);
            if(!k && x<X[i]) res+=(cal(i+1,1)+cal(i+1,0))*(x+1);
        }
        //cout << i << ' ' << k << ' ' << res << '\n';
        return dp[i][k]=res;
    };
    cout << cal(0,0) << '\n';
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
