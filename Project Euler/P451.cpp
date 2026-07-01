#include<bits/stdc++.h>
using namespace std;

#define int long long 
#define pii pair<int,int>
int power(int a,int n,int mod){
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

    vector<int> p(N+1,0),h(N+1,1);
    for(int i=2;i<=N;i++){
        if(!p[i]) for(int j=i;j<=N;j+=i) p[j]=i;
        if((i/p[i])%p[i]==0) h[i]=h[i/p[i]]*p[i];
        else h[i]=h[i/p[i]]*(p[i]-1);
    }

    vector<int> f(N+1);
    iota(f.begin(),f.end(),-1);
    auto cal = [&](int x,int y){
        int g=__gcd(x,y);
        if(g>2) return inf;
        x/=g;y/=g;
        int k=2/g;
        int a=k*power(x,h[y]-1,y)%y;
        if(a*x<=k) a+=y;
        if(a*x<=k) a+=y;
        return a*x*g - 1;
    };
    int res=0;
    for(int x=1;x<=N;x++){
        if(x%10000==0) cout << x << endl;
        for(int y=1;x*y<=N;y++) f[x*y]=min(f[x*y],cal(x,y));
        if(x>2){
            res+=x-f[x];
        }
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
