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

    vector<int> X;
    for(int a=0;a<=2*n;a++) for(int b=0;b<=2*n;b++){
        int x=1;
        for(int i=1;i<=a;i++) x*=2;
        for(int i=1;i<=b;i++) x*=5;
        X.push_back(x);
    }
    sort(X.begin(),X.end());

    int res=0;
    map<int,int> mp;
    for(int i=0;i<(int)X.size();i++) for(int j=0;j<=i;j++){
        __int128 d=X[i]+X[j];
        __int128 m=(__int128)X[i]*X[j];
        __int128 k=__gcd(d,m);m/=k;d/=k;
        
        int f2=0,f5=0;
        while(m%2==0) m/=2,f2++;
        while(m%5==0) m/=5,f5++;
        if(max(f2,f5)>n) continue;
        int mul=n-max({1LL,f2,f5})+1;

        while(d%2==0) d/=2;
        while(d%5==0) d/=5;

        if(mp.find(d)!=mp.end()) res+=mp[d]*mul;
        else{
            int cnt=0;
            for(int x=1;x*x<=d;x++){
                if(d%x==0){
                    cnt++;
                    if(x*x!=d) cnt++;
                }
            }
            mp[d]=cnt;
            res+=cnt*mul;
        }
        //cout << X[i] << ' ' << X[j] << ' ' << d << ' ' << mp[d] << '\n';
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
