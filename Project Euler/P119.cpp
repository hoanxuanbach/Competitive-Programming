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
    int N=1e16;
    auto cal = [&](int x){
        int d=0;
        while(x) d+=x%10,x/=10;
        return d;
    };
    vector<int> X;
    for(int s=2;s<200;s++){
        int x=s;
        while(x<=N){
            if(x>=10 && cal(x)==s) X.push_back(x);
            x*=s;
        }
    }
    sort(X.begin(),X.end());
    cout << X[1] << ' ' << X[9] << ' ' << X[29] << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
