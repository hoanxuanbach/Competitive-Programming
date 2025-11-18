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

    int S=1000000;
    vector<int> X;

    vector<int> p(S);
    for(int i=2;i<S;i++) if(!p[i]){
        X.push_back(i);
        for(int j=i;j<S;j+=i) p[j]=i;
    }
    auto cal = [&](int l,int r,int x){
        l/=x;r/=x;
        return (r*(r+1)-l*(l+1))/2*x;
    };

    int res=0;
    for(int i=0;i+1<(int)X.size();i++){
        int l=X[i]*X[i],r=min(X[i+1]*X[i+1]-1,N);
        if(l>r) break;
        res+=cal(l,r,X[i+1])+cal(l,r,X[i]);
        res-=2*cal(l,r,X[i]*X[i+1]);
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
