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
    vector<int> rad(N,1),p(N);
    for(int i=2;i<N;i++){
        if(!p[i]){
            for(int j=i;j<N;j+=i) rad[j]*=i,p[j]=i;
        }
    }
    int res=0;
    for(int a=1;a<N;a++){
        if(a%1000==0) cout << a/1000 << endl;
        int d=(a&1?1:2);
        for(int b=a+1;a+b<N;b+=d){
            int c=a+b;
            if(rad[a]*rad[b]*rad[c]>=c) continue;
            if(__gcd(a,b)==1) res+=c;
        }
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
