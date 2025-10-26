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
    int N=1000000;
    vector<int> p(N),prime;
    prime.push_back(0);
    for(int i=2;i<N;i++){
        if(!p[i]){
            prime.push_back(i);
            for(int j=i*2;j<N;j+=i) p[j]=true;
        }
    }
    int sz=(int)prime.size(),ans=0,X=-1;
    for(int i=1;i<sz;i++) prime[i]+=prime[i-1];
    for(int i=0;i<sz;i++){
        for(int j=i+ans+1;j<sz && (prime[j]-prime[i])<N;j++){
            if(!p[prime[j]-prime[i]]) X=prime[j]-prime[i],ans=j-i;
        }
    }
    cout << X << ' ' << ans << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
