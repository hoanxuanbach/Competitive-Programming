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

#define ld long double

void solve(){
    int S=5;
    map<vector<int>,ld> mp;
    function<ld(vector<int>)> f = [&](vector<int> x){
        if(mp.find(x)!=mp.end()) return mp[x];
        int cnt=0;
        for(int i=0;i<S;i++) cnt+=x[i];
        if(!cnt) return (ld)0;

        ld res=(cnt==1);
        for(int i=0;i<S;i++) if(x[i]){
            ld p=(ld)x[i]/cnt;
            vector<int> nx=x;nx[i]--;
            for(int j=i+1;j<S;j++) nx[j]++;
            res+=p*f(nx);
        }
        return mp[x]=res;
    };
    ld res=f({1,0,0,0,0})-2; 
    cout << setprecision(6) << fixed << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
