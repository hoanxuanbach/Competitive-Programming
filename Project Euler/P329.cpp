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

pii add(pii x,pii y){
    __int128 a=(__int128)x.first*y.second+(__int128)y.first*x.second;
    __int128 b=(__int128)x.second*y.second;
    __int128 g=__gcd(a,b);
    return pii{a/g,b/g};
}
pii mul(pii x,pii y){
    __int128 a=(__int128)x.first*y.first;
    __int128 b=(__int128)x.second*y.second;
    __int128 g=__gcd(a,b);
    return pii{a/g,b/g};
}


void solve(){
    int N=500;
    vector<int> p(N+1);p[0]=p[1]=1;
    for(int i=2;i<=N;i++) if(!p[i]){
        for(int j=i*2;j<=N;j+=i) p[j]=1;
    }

    vector<pii> f(N+1);
    for(int i=1;i<=N;i++) f[i]={1,N};

    string S;cin >> S;
    int n=(int)S.length();
    for(int id=0;id<n;id++){
        int k=(S[id]=='N');
        vector<pii> g(N+1,{0,1});
        for(int i=1;i<=N;i++){
            pii x=f[i];
            if(p[i]==k) x=mul(x,pii{2,3});
            else x=mul(x,pii{1,3});
            if(i==1) g[i+1]=add(g[i+1],x);
            else if(i==N) g[i-1]=add(g[i-1],x);
            else{
                x=mul(x,pii{1,2});
                g[i+1]=add(g[i+1],x);
                g[i-1]=add(g[i-1],x);
            }
        }
        swap(f,g);
    }
    pii res={0,1};
    for(int i=1;i<=N;i++) res=add(res,f[i]);
    cout << res.first << '/' << res.second << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
