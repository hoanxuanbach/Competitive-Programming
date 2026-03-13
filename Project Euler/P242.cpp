#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 998244353;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a;
        a=a*a;n>>=1;
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

    auto g = [&](int n,int k){
        if((n&k)==k) return 1;
        else return 0;
    };

    N=(N-1)/4;

    int cnt=0,res=0;
    for(int i=40;i>=0;i--){
        if(N>>i&1){
            res+=power(2,cnt)*power(3,i);
            cnt++;
        }
    }
    res+=power(2,cnt);
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
