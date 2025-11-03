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
    int S=sqrtl(N);
    vector<int> X;
    
    vector<int> p(S+1);
    for(int i=2;i<=S;i++) if(!p[i]){
        X.push_back(i);
        for(int j=i;j<=S;j+=i) p[j]=1;
    }

    vector<int> f(N+1);
    for(int x:X){
        for(int y:X){
            if(x*x+y*y*y>N) break;
            for(int z:X){
                if(x*x+y*y*y+z*z*z*z>N) break;
                f[x*x+y*y*y+z*z*z*z]=1;
            }
        }
    }

    int cnt=0;
    for(int i=1;i<=N;i++) cnt+=f[i];
    cout << cnt << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
