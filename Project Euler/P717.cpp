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

int cal(int x){
    int d=power(2,x,x*(x-1));
    int k=(d+x*(x-2))%(x*(x-1));
    d=power(2,d,x*x);
    k=power(2,k,x*x);
    d/=x;k/=x;
    d=(d-2*k+2*x)%x;
    return d;
}

void solve(){
    int N;cin >> N;

    int res=0;
    vector<int> p(N);
    for(int i=2;i<N;i++) if(!p[i]){
        for(int j=i;j<N;j+=i) p[j]=1;
        if(i>2) res+=cal(i);
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
