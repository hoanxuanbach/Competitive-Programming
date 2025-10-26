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
    int N=1000;
    int mx=-1,val=-1;
    for(int d=2;d<N;d++){
        int p=0,x=1;
        map<int,int> mp;
        while(true){
            x*=10;p++;
            int k=x/d;
            if(mp.find(x)!=mp.end()){
                int c=p-mp[x];
                if(c>mx) mx=c,val=d;
                break;
            }
            mp[x]=p;x%=d;
        }
    }
    cout << val << ' ' << mx << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
