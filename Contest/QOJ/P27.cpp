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

const int L = 60;
void solve(){
    int n;cin >> n;
    vector<int> a(n),f(n);
    for(int i=0;i<n;i++) cin >> a[i],f[i]=a[i];

    function<void(int,vector<int>)> dfs = [&](int k,vector<int> ord){
        if(k<0 || ord.empty()) return;
        vector<int> X,Y;
        for(int x:ord){
            if(a[x]>>k&1) Y.push_back(x);
            else X.push_back(x);
        }
        dfs(k-1,X);dfs(k-1,Y);
        int j=0;
        for(int i:Y){
            while(j<(int)X.size() && a[X[j]]<(a[i]^(1LL<<k))) j++;
            swap(f[X[j]],f[i]);
        }
    };

    vector<int> ord(n);
    iota(ord.begin(),ord.end(),0);
    sort(ord.begin(),ord.end(),[&](int x,int y){
        return a[x]<a[y];
    });
    dfs(L-1,ord);
    for(int i=0;i<n;i++) cout << f[i] << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
