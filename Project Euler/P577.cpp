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

//https://oeis.org/A236770
int get0(int n){
    n/=3;
    return n*(n+1)*(3*n*n+3*n-2)/8;
}
//https://oeis.org/A228317
int get1(int n){
    n/=3;
    return n*(n+1)*(n+2)*(3*n+1)/8;
}
//https://oeis.org/A000914 *3
int get2(int n){
    n/=3;
    return n*(n+1)*(n+2)*(3*n+5)/8;
}

void solve(){
    int N;cin >> N;
    //https://oeis.org/A011779
    int res=0;
    for(int n=3;n<=N;n++){
        if(n%3==0) res+=get0(n);
        else if(n%3==1) res+=get1(n);
        else res+=get2(n);
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
