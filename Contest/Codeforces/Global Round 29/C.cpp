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
    int n;string s;cin >> n >> s;
    s="1"+s+"1";n+=2;
    vector<int> dir(n);
    for(int i=0;i+1<n;i++) if(s[i]=='1' && s[i+1]=='1'){
        if(i>0) dir[i-1]|=1;
        if(i+2<n) dir[i+2]|=2;
    }
    for(int i=0;i<n;i++){
        if(s[i]=='0' && dir[i]==3){
            cout << "NO\n";
            return;
        }
        if(s[i]=='1') continue;
        if(i+2<n && dir[i]!=0 && s[i+1]=='1' && s[i+2]=='0') dir[i+2]|=(dir[i]^3);
    }

    cout << "YES\n";
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}
