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
    auto f = [&](int k,int i){
        int b=(4-k)*i,a=2*(k-2)*i+1;
        int A=a*a,B=(b*b*(k-2)+b*(4-k))/2;
        return pii{A,B};
    };  
    int res=0;
    for(int k=3;;k+=2){
        auto [A,B]=f(k,1);
        if(max(A,B)>N) break;
        res+=A+B;
        for(int i=2;;i++){
            tie(A,B)=f(k,i);
            if(max(A,B)>N) break;
            res+=A+B;
        }
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
