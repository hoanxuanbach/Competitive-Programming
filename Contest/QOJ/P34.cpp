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
    int n,p,q;cin >> n >> p >> q;
    if(p==1){
        for(int i=0;i<n;i++) cout << i << ' ';
        cout << '\n';
    }
    else if(q==1){
        for(int i=0;i<n;i++) cout << n-1-i << ' ';
        cout << '\n';
    }
    else{
        int k=n%(p+q);
        if(__gcd(p,q)>1 || (k>1 && k<p+q-1)) cout << -1 << '\n';
        else{
            vector<bool> f(n);
            int x=(k<=1?0:p-1);

            cout << x << ' ';
            for(int i=1;i<n;i++){
                f[x]=1;
                if(x>=q && !f[x-q]) x-=q;
                else x+=p;
                cout << x << ' ';
            }
            cout << '\n';
        }
    }
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}
