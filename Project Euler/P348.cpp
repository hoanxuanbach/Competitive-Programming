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

    map<int,int> mp;
    for(int x=2;x*x<=N;x++){
        cout << x << endl;
        for(int y=2;x*x+y*y*y<=N;y++){
            string s=to_string(x*x+y*y*y),t=s;
            reverse(t.begin(),t.end());
            if(s==t) mp[x*x+y*y*y]++;
        }
    }

    for(auto [x,d]:mp) if(d==4){
        cout << x << '\n';
    }
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
