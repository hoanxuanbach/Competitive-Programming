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
    int n;cin >> n;
    n=(n+3)/2;
    int k=(n%3)^3;

    int res=0,m=n;
    vector<int> P;
    for(int i=2;i*i<=m;i++){
        if(m%i==0){
            P.push_back(i);
            while(m%i==0) m/=i;
        }
    }
    if(m>1) P.push_back(m);
    
    int sz=(int)P.size();
    for(int mask=0;mask<(1<<sz);mask++){
        int x=1,mul=1;
        for(int i=0;i<sz;i++) if(mask>>i&1) x*=P[i],mul*=-1;
        if(x%3==0) continue;
        int d=(x%3);
        if(k==2) d^=3;
        res+=mul*((n/x)+3-d)/3;
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
