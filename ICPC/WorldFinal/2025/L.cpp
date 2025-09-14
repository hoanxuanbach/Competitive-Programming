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
    int n,a,b,c,d;cin >> n >> a >> b >> c >> d;
    
    int res=0;
    map<int,int> cnt;
    for(int i=0;i<n;i++){
        int t,x,y;cin >> t >> x >> t >> y;
        x=max(x,d);y=min(y,b);
        if(x>y) continue;
        cnt[x]++;cnt[y]--;
    }
    if(b>d){
        int k=0;
        for(auto [p,x]:cnt){
            if(!k) res+=p-d;
            d=p;k+=x;
        }
        res+=b-d;
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
