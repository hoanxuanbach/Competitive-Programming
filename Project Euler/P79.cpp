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
    int N=50;
    set<string> ss;
    for(int i=0;i<50;i++){
        string S;cin >> S;
        if(S.back()=='0') S.pop_back();
        if(S[0]=='7') S=S.substr(1,(int)S.size()-1);
        if(S[0]=='3') S=S.substr(1,(int)S.size()-1);
        if(S.empty()) continue;
        if(S[0]=='1') S=S.substr(1,(int)S.size()-1);
        if((int)S.size()<=1) continue;
        ss.insert(S);
    }
    for(string s:ss) cout << s << '\n';
    //73162890
}
 
signed main(){
    freopen("79.txt","r",stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
