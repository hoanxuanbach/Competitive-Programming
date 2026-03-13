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

    int S=n/3+1;
    vector<int> f(S);
    for(int i=2;i<S;i++) if(!f[i]){
        for(int j=i;j<S;j+=i) f[j]=i;
    }

    map<int,int> mp;
    auto g = [&](int m){
        if(mp.find(m)!=mp.end()) return mp[m];
        int cnt=0;

        /*
        3*a+2*x+y
        a>=1,x>=0,y>=0
        */
        for(int a=1;3*a<=m;a++){
            int d=m-3*a,k=d/2;
            cnt+=(k+1)*d-(k+1)*k+k+1;
        }

        /*
        a<=b, a+b<=c 
        a+b+c<=m
        4*a+2*x+y
        */

        for(int a=1;4*a<=m;a++){
            int d=m-4*a,k=d/2;
            cnt-=(k+1)*d-(k+1)*k+k+1;
        }

        return mp[m]=cnt;
    };

    int res=0;
    for(int i=1;i<S;i++){
        int k=1,x=i;
        while(x>1){
            int j=f[x];k*=-1;
            if((x/j)%j==0) k=0;
            while(x%j==0) x/=j;
        }
        if(k) res+=k*g(n/i);
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
