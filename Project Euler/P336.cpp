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
    int n;cin >> n;

    vector<string> X;

    string S(n,'.');
    vector<int> P(n);
    iota(P.begin(),P.end(),0);

    function<void(int)> dfs = [&](int x){
        if(x+2==n){
            S[P[n-1]]=char('A'+x);
            S[P[n-2]]=char('A'+x+1);
            X.push_back(S);
            return;
        }
        for(int i=x+1;i+1<n;i++){
            S[P[i]]=char('A'+x);
            reverse(P.begin()+i,P.end());
            reverse(P.begin()+x,P.end());
            dfs(x+1);
            reverse(P.begin()+x,P.end());
            reverse(P.begin()+i,P.end());
        }
    };
    dfs(0);
    
    sort(X.begin(),X.end());
    int id;cin >> id;id--;
    cout << X[id] << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
