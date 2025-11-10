#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
int power(int a,int n,int mod){
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
    int X=1777;

    vector<int> T;
    pii P={8,8};
    while(P.first+P.second){
        int val=1;
        for(int i=1;i<=P.first;i++) val*=2;
        for(int i=1;i<=P.second;i++) val*=5;
        T.push_back(val);

        if(P.first) P.first--;
        if(P.second){
            P.second--;
            P.first+=2;
        }
    }

    int A=1;
    while(!T.empty()){
        int D=T.back();T.pop_back();
        A=power(X,A,D);
    }
    cout << A << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
