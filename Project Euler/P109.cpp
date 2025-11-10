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
    vector<pii> P;
    for(int i=1;i<=20;i++) for(int j=1;j<=3;j++) P.push_back({i,j});
    P.push_back({25,1});
    P.push_back({25,2});

    int S=100,cnt=0;
    for(auto z:P) if(z.second==2){
        int val=z.first*z.second;
        if(val<S) cnt++;
        for(auto x:P){
            int nval=val+x.first*x.second;
            if(nval<S) cnt++;
            for(auto y:P) if(x<=y){
                int mval=nval+y.first*y.second;
                if(mval<S) cnt++;
            }
        }
    }
    cout << cnt << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
