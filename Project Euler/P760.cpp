#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 1e9+7;
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
    
    int nn=N%mod;
    int res=nn*(nn+1)%mod*(nn+2)%mod;
    res=res*power(3,mod-2)%mod;

    vector<int> f(3),g(3);f[0]=1;
    for(int i=60;i>=0;i--){
        vector<int> ff(3),gg(3);
        for(int x=0;x<=2;x++) for(int a=0;a<=1;a++) for(int b=0;b<=1;b++){
            int nx=min(x*2+(N>>i&1)-a-b,2LL);
            if(nx<0) continue;
            ff[nx]=(ff[nx]+f[x])%mod;
            gg[nx]=(gg[nx]+g[x]*2+f[x]*(a^b))%mod;
        }
        swap(f,ff);swap(g,gg);
    }
    res=(res+g[0]+g[1]+g[2])%mod;
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
