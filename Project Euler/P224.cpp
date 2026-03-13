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
    int res=1;
    queue<array<int,3>> q;
    q.push({2,2,3});
    auto add = [&](int a,int b,int c){
        if(a+b+c<=N) q.push({a,b,c}),res++;
    };
    while(!q.empty()){
        auto [a,b,c]=q.front();q.pop();
        add(a-2*b+2*c,2*a-b+2*c,2*a-2*b+3*c);
        if(a!=b) add(-a+2*b+2*c,-2*a+b+2*c,-2*a+2*b+3*c);
        add(2*a+b+2*c,a+2*b+2*c,2*a+2*b+3*c);
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
