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
    int N=2000000,X=-1,A=-1;
    auto add = [&](int x,int val){
        if(abs(N-X)>abs(N-x)) X=x,A=val;
    };
    for(int a=1;a*(a+1)/2<=N;a++){
        int d=N/(a*(a+1)/2);
        int b=sqrtl(2*d);
        while((b+1)*(b+2)/2<=d) b++;
        add(a*(a+1)/2*b*(b+1)/2,a*b);
        b++;
        add(a*(a+1)/2*b*(b+1)/2,a*b);
    }
    cout << X << ' ' << A << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
