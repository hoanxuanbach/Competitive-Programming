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
    int n,k,m;cin >> n >> k >> m;
    
    vector<pii> p;
    for(int i=0;i<k;i++){
        int s;cin >> s;
        for(int j=0;j<(2*s);j++){
            int x;cin >> x;
            p.push_back({x+(j&1),i});
        }
    }
    
    vector<array<int,2>> f(1<<k);
    sort(p.begin(),p.end());
    int cur=0,pos=1;
    for(auto [x,i]:p){
        f[cur][0]+=x-pos;
        pos=x;cur^=(1<<i);
        
    }
    f[cur][0]+=n+1-pos;

    for(int x=0;x<k;x++){
        for(int i=0;i<(1<<k);i++) if(i>>x&1){
            int j=(i^(1<<x));
            int T=f[i][0];
            f[i][0]+=f[j][0];
            f[i][1]+=f[j][1];
            f[j][1]+=T;
        }   
    }

    int res=0;
    for(int i=0;i<(1<<k);i++){
        if(f[i][0]+f[i][1]<=n-m) res++;
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}