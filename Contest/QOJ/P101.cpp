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
    string S;cin >> S;
    int n=(int)S.length();
    reverse(S.begin(),S.end());
    
    int res=0;
    vector<pii> P;
    vector<int> f(26,-1);
    P.push_back({0,-1});
    for(int i=0;i<n;i++){
        int x=S[i]-'a',lst=-1,pos=-1;
        while(!P.empty() && P.back().second>=f[x]){
            tie(lst,pos)=P.back();
            P.pop_back();
        }
        res=max(res,lst+1);
        P.push_back({lst,pos});
        P.push_back({lst+1,i});
        f[x]=i;
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
