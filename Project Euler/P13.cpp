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
    int N=100,K=50;
    string res(K,'0');
    for(int i=0;i<N;i++){
        string S;cin >> S;
        reverse(S.begin(),S.end());
        res+='0';
        for(int j=0;j<=i;j++) S+='0';

        int T=0;    
        for(int j=0;j<=K+i;j++){
            T+=S[j]-'0'+res[j]-'0';
            res[j]=char(T%10+'0');
            T/=10;
        }
    }
    while(res.back()=='0') res.pop_back();
    string X;
    for(int i=0;i<10;i++){
        X+=res.back();
        res.pop_back();
    }
    cout << X << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
