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
    int n,k;cin >> n >> k;
    vector<int> d(n+1);
    for(int i=1;i<=n;i++) for(int j=i;j<=n;j+=i) d[j]++;

    int res=0;
    deque<int> v;
    for(int i=1;i<=n;i++){
        while(!v.empty() && d[v.back()]<=d[i]) v.pop_back();
        v.push_back(i);
        if(v.front()<=i-k) v.pop_front();
        if(i>=k) res+=d[v.front()];
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
