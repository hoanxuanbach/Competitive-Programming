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
    int k,x;cin >> k >> x;
    int y=(1LL<<(k+1))-x;
    vector<int> s;
    while(x!=y){
        if(x>y) s.push_back(2),x-=y,y*=2;
        else s.push_back(1),y-=x,x*=2;
    }
    reverse(s.begin(),s.end());
    cout << (int)s.size() << '\n';
    for(int x:s) cout << x << ' ';
    cout << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}
