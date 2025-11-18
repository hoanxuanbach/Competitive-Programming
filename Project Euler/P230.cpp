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

string A = "1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679";

string B = "8214808651328230664709384460955058223172535940812848111745028410270193852110555964462294895493038196";

void solve(){
    int N=1e18;
    vector<int> F={100,100};
    while(F.back()<=N){
        int X=F.end()[-2]+F.back();
        F.push_back(X);
    }
    int S=(int)F.size();

    int res=0,mul=1,val=1;
    for(int d=0;d<=17;d++){
        int n=(127+19*d)*val,x=0;
        while(F[x]<n) x++;
        while(x>1){
            if(n>F[x-2]) n-=F[x-2],x--;
            else x-=2;
        }
        int k=(x?B[n-1]-'0':A[n-1]-'0');
        res+=k*mul;
        mul*=10;val*=7;
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
