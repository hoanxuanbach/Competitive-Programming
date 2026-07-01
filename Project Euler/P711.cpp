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
 
const int maxn = 2e5+5;
const int inf = 1e18;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}

void solve(){
    int N;cin >> N;
    int res=power(2,N);
    
    N/=2;
    int T=1;
    for(int k=0;k<=N;k++){
        res=(res+T-1)%mod;
        cout << T-1 << '\n';
        if(k!=N){
            res=(res+2*T-1)%mod;
            cout << 2*T-1 << '\n';
        }
        T=T*4%mod;
    }

    cout << res << '\n';

    T=1;
    int cnt=0,sum=0;
    for(int i=0;i<N;i++){
        cout << sum << ' ' << cnt << '\n';
        res=(res+T*cnt+sum)%mod;
        sum=(sum*3+4*T*cnt+T-1)%mod;
        cnt=(cnt*3+1)%mod;
        T=T*4%mod;
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
