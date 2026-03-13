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
    int S=sqrtl(N),res=0;

    int T=max(S,N/S)+1;
    vector<int> A(T,-1),B(T,-1);

    function<int(int)> g = [&](int x){
        int n=N/x;
        if(x<=S){
            if(A[x]!=-1) return A[x];
        }
        else if(B[n]!=-1) return B[n];

        int cnt=((__int128)n*(n+1)/2)%mod,s=sqrtl(n);
        for(int i=1;i<s;i++){
            int l=n/(i+1),r=n/i;
            cnt-=(__int128)(r-l)*g(x*r)%mod;
        }
        for(int i=2;i<=n/s;i++) cnt-=g(x*i);
        cnt=(cnt%mod+mod)%mod;
        if(x<=S) return A[x]=cnt;
        else return B[n]=cnt;
    };
    for(int i=1;i<S;i++){
        int l=N/(i+1),r=N/i;
        res+=((__int128)r*(r+1)/2-(__int128)l*(l+1)/2)*g(r)%mod;
    }
    for(int i=1;i<=N/S;i++) res+=i*g(i)%mod;
    res%=mod;
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
