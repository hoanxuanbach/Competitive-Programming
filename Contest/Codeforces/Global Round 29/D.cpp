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

    int sum=0;
    map<int,int> mp;
    for(int i=0;i<n;i++){
        int x;cin >> x;
        sum+=x;
        if(x&1) sum--,mp[x]++;
    }
    vector<int> P;
    for(auto [x,d]:mp) P.push_back(d);
    sort(P.begin(),P.end(),greater<int>());
    int A=sum/2,B=sum/2;
    for(int i=0;i<(int)P.size();i++){
        if(i&1) B+=P[i];
        else A+=P[i];
    }
    cout << A << ' ' << B << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}
