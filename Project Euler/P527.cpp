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

#define ld long double
void solve(){
    int N;cin >> N;

    map<int,ld> B;
    function<ld(int)> get = [&](int i){
        if(i<=0) return (ld)0;
        if(B.find(i)!=B.end()) return B[i];
        int x=(i+1)/2,y=i-x;x--;
        return B[i]=i+get(x)+get(y);
    };
    ld fB=get(N);
    auto ff = [&](int n){
        //sum(1/1+...+1/n) with n very large
        ld ret=log(n)+(ld)0.5772156649;
        return ret;
    };
    auto cal = [&](int n){
        ld ret=ff(n+2)+(ld)1/(n+2)-2;
        ret*=(n+1);
        ret*=(n+2);
        return ret;
    };
    ld fR=N+cal(N-1)*2/N;
    ld res=fR-fB;
    cout << setprecision(8) << fixed << res/N << endl;
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
