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
    auto ask = [&](int c){
        cout << "? " << c << endl;
        int x=0;cin >> x;
        return x;
    };
    int X=ask(0),L=30;
    vector<int> A;A.push_back(X);
    function<void(int,int)> dfs = [&](int x,int k){
        int d=x;
        for(int i=k;i<L;i++) d^=(1<<i);
        int y=ask(d)^d;
        if(x==y) return;
        A.push_back(y);
        if((int)A.size()==n) return;
        while(!((x^y)>>k&1)) k--;
        dfs(y,k);dfs(x,k);
    };
    dfs(X,L);

    sort(A.begin(),A.end());
    cout << "! ";
    for(int x:A) cout << x << ' ';
    cout << endl;
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}