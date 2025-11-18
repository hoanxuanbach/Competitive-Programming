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
    int N=1e6;
    vector<int> f(N+1);
    for(int i=1;i*i<=N;i++) f[i*i]=1;

    for(int a=3;;a++){
        cout << '*' << a << endl;
        for(int b=(a&1?1:2);b<a;b+=2){
            int x=(a*a+b*b)/2;
            int y=a*a-x;
            if(x<=y) break;
            for(int c=sqrt(x)+1;;c++){
                int z=c*c-x;
                if(y<=z) break;
                if(f[x-z] && f[y-z] && f[y+z]){
                    cout << x+y+z << '\n';
                    return;
                }
            }
        }
    }
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
