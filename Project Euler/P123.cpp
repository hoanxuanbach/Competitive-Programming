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
    int N=100000000;
    vector<int> X;
    vector<int> p(N);
    for(int i=2;i<N;i++) if(!p[i]){
        X.push_back(i);
        for(int j=i*i;j<N;j+=i) p[j]=1;
    }
    int L=10000000000;
    for(int n=1;n<=(int)X.size();n+=2){
        int x=X[n-1];
        int val=2*x*n%(x*x);
        if(val>L){
            cout << n << '\n';
            return;
        }
    }
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
