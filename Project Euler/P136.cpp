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
    int N=50000000,res=0;
    vector<int> cnt(N);
    for(int a=1;a<N;a++){
        for(int n=a;n<N;n+=a){
            int b=n/a;
            int d=(a+b);
            if(d%4!=0) continue;
            d/=4;
            if(a<=d) continue;
            int x=a-d;
            cnt[n]++;
        }
    }
    for(int i=1;i<N;i++) res+=(cnt[i]==1);
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
