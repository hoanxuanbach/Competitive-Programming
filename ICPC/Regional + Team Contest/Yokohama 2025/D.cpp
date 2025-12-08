#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 1e9+7;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}

const int inf = 1e18;
const int maxn = 2e5+5;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}


void solve(){
    int n;cin >> n;
    string res;

    int d=1;
    while(d<n){
        int x=n-d,k=1;
        while(k*10<=x) k*=10;
        int a=min(d*10-1,n-k);
        string cur=to_string(a)+to_string(n-a);
        if((int)cur.length()>(int)res.length()) res=cur;
        else res=max(res,cur);
        d*=10;
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}


