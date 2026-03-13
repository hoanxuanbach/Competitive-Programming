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
    int m;cin >> m;
    vector<int> b(m);
    for(int i=0;i<m;i++) cin >> b[i];
    int n;cin >> n;
    for(int i=0;i<n;i++){
        int k;cin >> k;
        vector<int> f(m);
        for(int j=0;j<k;j++){
            int x;cin >> x;
            
            int id=0;
            while(id<m && b[id]!=x) id++;
            if(id==m) continue;
            if(id==0) f[id]++;
            else if(f[id-1]) f[id-1]--,f[id]++;
        }
        cout << f[m-1] << '\n';
    }
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
