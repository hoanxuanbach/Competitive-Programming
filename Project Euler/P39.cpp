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
    int N=1000;
    vector<int> f(N*N);
    for(int i=1;i<N;i++) f[i*i]=i;

    vector<int> cnt(N+1);
    for(int c=1;c<N;c++){
        for(int b=1;b<c && b+c<N;b++){
            int a=f[c*c-b*b];
            if(!a || a>=b) continue;
            if(a+b+c<=N) cnt[a+b+c]++;
        }
    }

    int x=0;
    for(int i=1;i<=N;i++) if(cnt[i]>cnt[x]) x=i;
    cout << x << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
