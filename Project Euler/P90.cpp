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
    vector<string> S = {"01","04","09","16","25","36","49","64","81"};
    int cnt=0;
    for(int x=0;x<(1<<10);x++) for(int y=0;y<(1<<10);y++){
        if(__builtin_popcount(x)!=6 || __builtin_popcount(y)!=6) continue;
        int X=x,Y=y;
        if(X>>6&1) X|=(1<<9);
        if(X>>9&1) X|=(1<<6);
        if(Y>>6&1) Y|=(1<<9);
        if(Y>>9&1) Y|=(1<<6);
        bool check=true;
        for(auto x:S){
            int a=x[0]-'0',b=x[1]-'0';
            if((X>>a&1) && (Y>>b&1)) continue;
            if((X>>b&1) && (Y>>a&1)) continue;
            check=false;
        }
        if(check) cnt++;
    }
    cout << cnt/2 << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
