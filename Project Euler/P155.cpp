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
    vector<vector<pii>> f(n+1);
    f[1]={pii{1,1}};
    for(int i=2;i<=n;i++){
        for(int j=1;j<=i/2;j++){
            for(auto x:f[j]) for(auto y:f[i-j]){
                pii z={x.first*y.second+y.first*x.second,x.second*y.second};
                int g=__gcd(z.first,z.second);
                f[i].push_back({z.first/g,z.second/g});
                z.second=x.first*y.first;
                swap(z.first,z.second);
                g=__gcd(z.first,z.second);
                f[i].push_back({z.first/g,z.second/g});
            }
        }
        sort(f[i].begin(),f[i].end());
        f[i].erase(unique(f[i].begin(),f[i].end()),f[i].end());
        cout << i << ' ' << (int)f[i].size() << endl;
    }
    vector<pii> F;
    for(int i=1;i<=n;i++) for(auto x:f[i]) F.push_back(x);
    sort(F.begin(),F.end());
    F.erase(unique(F.begin(),F.end()),F.end());
    cout << (int)F.size() << '\n'; 
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
