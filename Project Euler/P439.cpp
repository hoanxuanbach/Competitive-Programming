#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 1e9;
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
    int N;cin >> N;

    int S=1e6;
    vector<int> f(S,-1),g(S,-1);
    function<int(int)> cal = [&](int x){
        if(x>N) return 0LL;
        if(N/x<S){
            if(f[N/x]!=-1) return f[N/x];
        }
        else if(g[x]!=-1) return g[x];

        int d=N/x,s=sqrtl(d);
        int res=0,sum=d;
        for(int i=1;i<s;i++){
            int l=d/(i+1),r=d/i;
            int ss=((__int128)(r-l)*(r+l+1)/2)%mod;
            sum=(sum+i*ss)%mod;
            res=(res+ss*cal(N/i))%mod;
        }
        for(int i=2;i<=d/s;i++){
            sum=(sum+i*(d/i))%mod;
            res=(res+i*cal(x*i))%mod;
        }
        //cout << d << ' ' << sum << ' ' << res << '\n';
        res=(sum*sum+mod-res)%mod;
        if(N/x<S) return f[N/x]=res;
        else return g[x]=res;
    };
    cout << cal(1) << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
