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
    int n;cin >> n;

    auto check = [&](int a,int b){
        vector<int> X,Y;
        for(int i=0;i<n;i++) if(a>>i&1) X.push_back(i);
        for(int i=0;i<n;i++) if(b>>i&1) Y.push_back(i);
        if((int)X.size()!=(int)Y.size()) return false;

        int all=0;
        for(int i=0;i<(int)X.size();i++){
            if(X[i]<Y[i]) all|=1;
            else all|=2;
        }
        return (all==3);
    };

    int cnt=0;
    for(int i=1;i<(1<<n);i++){
        int mask=((1<<n)-1)^i;
        for(int j=mask;j;j=(j-1)&mask) if(check(i,j)) cnt++;
    }
    cout << cnt/2 << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
