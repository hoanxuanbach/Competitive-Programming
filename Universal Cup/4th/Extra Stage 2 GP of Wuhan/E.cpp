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

    int fs=0,ft=0;
    bool cs=false,ct=false;

    vector<int> S(n);
    for(int i=0;i<n;i++){
        cin >> S[i];
        if(S[i]&1) fs++;
    }
    sort(S.begin(),S.end());

    vector<int> T(n);
    for(int i=0;i<n;i++){
        cin >> T[i];
        if(T[i]&1) ft++;
    }
    sort(T.begin(),T.end());
    if(S==T){
        cout << "Yes\n";
        return;
    }
    for(int i=1;i<n;i++){
        if(T[i-1]+1==T[i]) ct=true;
        if(S[i-1]+1==S[i]) cs=true;
    }
    if(!ct || !cs || fs!=ft) cout << "No\n";
    else cout << "Yes\n";
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}
