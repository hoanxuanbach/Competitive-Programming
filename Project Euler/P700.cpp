#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
int power(int a,int n,int mod){
    int res=1;
    while(n){
        if(n&1) res=(__int128)res*a%mod;
        a=(__int128)a*a%mod;n>>=1;
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
    int A=1504170715041707;
    int M=4503599627370517;

    int a=A;
    for(int i=2;i*i<=a;i++){
        if(a%i==0){
            int k=0;
            while(a%i==0) k++,a/=i;
            cout << i << ' ' << k << '\n';
        }
    }
    if(a>1) cout << a << ' ' << 1 << '\n';

    a=M;
    for(int i=2;i*i<=a;i++){
        if(a%i==0){
            int k=0;
            while(a%i==0) k++,a/=i;
            cout << i << ' ' << k << '\n';
        }
    }
    if(a>1) cout << a << ' ' << 1 << '\n';

    int X=A,S=A,d=A;
    for(int i=2;i<=50000000;i++){
        d=(d+A)%M;
        if(X>d){
            X=d;
            S+=d;
        }
    }
    cout << X << ' ' << S << '\n';

    int lst=M,inv=power(A,M-2,M);

    int k=0;
    for(int i=1;i<X;i++){
        k=(k+inv)%M;
        if(k<lst) S+=i,lst=k;
    }

    cout << lst << ' ' << S << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
