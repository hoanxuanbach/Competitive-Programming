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
    int n,h;cin >> n >> h;
    if(h<2*n-1 || h>n*n || h==(n*n-2)){
        cout << "impossible\n";
        return;
    }
    vector<int> res;
    while(n>1 && h-(2*n-1)>=2*n-3){
        res.push_back(2*n-1);
        h-=(2*n-1);n--;
    }
    if((h-(2*n-1))&1){
        int x=(h-(2*n-1)+1)/2;
        for(int i=1;i<=n;i++) if(i!=x) res.push_back(2*i-1);
        res.push_back(2*x-1);
    }
    else if((h-(2*n-1))==0){
        for(int i=1;i<=n;i++) res.push_back(2*i-1);
    }
    else if((h-(2*n-1))!=2){
        int x=(h-2*n+1)/2;
        for(int i=2;i<=n;i++) if(i!=x) res.push_back(2*i-1);
        res.push_back(2*x-1);res.push_back(1);
    }
    else{
        assert(n>=4);
        for(int i=1;i<n;i++) if(i!=2) res.push_back(2*i-1);
        res.push_back(3);
        res.push_back(2*n-1);
    }
    while(!res.empty()){
        int x=res.back();
        cout << x << ' ';
        res.pop_back();
    }
    cout << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
