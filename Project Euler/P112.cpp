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

    int cnt=0;
    for(int i=1;i<=N;i++){
        string s=to_string(i);

        bool inc=true,dec=true;
        for(int j=1;j<(int)s.length();j++){
            if(s[j]>s[j-1]) dec=false;
            else if(s[j]<s[j-1]) inc=false;
        }
        if(!inc && !dec) cnt++;

        if(cnt*100>=i*99){
            cout << i << '\n';
            return;
        }
    }
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
