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
    vector<int> p(N+1,1);
    p[0]=p[1]=0;

    vector<int> prime;
    for(int i=2;i<=N;i++) if(p[i]){
        prime.push_back(i);
        for(int j=i*i;j<=N;j+=i) p[j]=0;
    }

    vector<vector<int>> f(N+1);
    for(int x:prime) f[x].push_back(1);

    int T=0;
    vector<int> g(N+1),h(N+1);
    for(int i=1;i<=N;i++){
        int val=1;
        for(int x:prime){
            int n=i;
            while(n%x==0) g[x]+=n/x,h[x]++,n/=x;
            while(n) g[x]+=n/x,n/=x;

            int k=(i+1)*h[x]-2*g[x];
            while((int)f[x].size()<=k) f[x].push_back((f[x].back()*x+1)%mod);
            val=val*f[x][k]%mod;
            //cout << i << ' ' << x << ' ' << k << ' ' << f[x][k] << '\n';
        }
        T=(T+val)%mod;
    }
    cout << T << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
