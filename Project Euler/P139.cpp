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
    int total=0;
    for(int s=3;s*s<N;s++){
        for(int n=1;2*n<s;n++){
            int m=s-n;
            if(__gcd(n,m)!=1 || (n&1)==(m&1)) continue;
            int a=m*m-n*n,b=2*m*n,c=m*m+n*n;
            if(a>b) swap(a,b);
            int sum=(a+b+c);
            if(c%(b-a)!=0) continue;
            total+=N/sum;
        }
    }
    cout << total << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
