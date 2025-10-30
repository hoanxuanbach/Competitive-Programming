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
    int N=1000000,cnt=0;
    vector<int> fac(10,1);
    for(int i=1;i<10;i++) fac[i]=fac[i-1]*i;

    vector<int> f(10*N);
    for(int i=1;i<10*N;i++){
        string s=to_string(i);
        int j=0;
        for(char c:s) j+=fac[c-'0'];
        f[i]=j;
    }
    for(int i=1;i<N;i++){
        cout << i << endl;
        int x=i;
        set<int> ss;
        while(ss.find(x)==ss.end()){
            assert(x<10*N);
            ss.insert(x);
            x=f[x];
        }
        if((int)ss.size()==60) cnt++;
    }
    cout << cnt << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
