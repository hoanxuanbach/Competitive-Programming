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
    vector<int> P(2*n-1);
    iota(P.begin(),P.end(),1);
    P.insert(P.begin(),2*n);
    string res;
    do{ 
        int X=-1;
        vector<array<int,3>> S;
        for(int i=0;i<n;i++){
            int T=P[i]+P[n+i]+P[n+(i+1)%n];
            if(X==-1 || X==T) X=T;
            else X=-2;
            S.push_back({P[i],P[n+i],P[n+(i+1)%n]});
        }
        if(X==-2) continue;
        int id=0;
        for(int i=1;i<n;i++) if(S[i][0]<S[id][0]) id=i;
        string K;
        for(int j=0;j<n;j++) for(int i=0;i<=2;i++) K+=to_string(S[(id+j)%n][i]);
        res=max(res,K);
    }while(next_permutation(P.begin(),P.end()));
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
