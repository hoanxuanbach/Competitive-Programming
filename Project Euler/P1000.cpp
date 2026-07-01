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

int I(int n){
    vector<int> f(20);
    for(int i=1;i<=n;i++) for(int j=0;j<20;j++) f[j]+=(i>>j&1);
    int res=0;
    for(int i=0;i<20;i++){
        int k=f[i]/2;
        res+=(1LL<<i)*k*(f[i]-k);
    }
    return res;
}
int C(int n){
    int res=0;
    for(int a=0;a<n;a++) for(int b=0;b<n;b++) for(int c=(a^b)+1;c<n;c++) if((c^a)<b && (c^b)<a) res++;
    return res;
}

const int S = (1<<20);

int X(int n){
    vector<int> f(n+1);
    vector<vector<pii>> g(S);
    for(int i=1;i<=n;i++) for(int j=i+1;j<=n;j++) g[(i*i)^(j*j)].push_back({i,j});
    for(int i=1;i<S;i++){
        if(g[i].empty()) continue;
        for(auto [x,y]:g[i]){
            int fx=f[x],fy=f[y];
            f[x]=max(f[x],fy+i);
            f[y]=max(f[y],fx+i);
        }
    }
    int res=0;
    for(int i=1;i<=n;i++) res=max(res,f[i]);
    return res;
}

void solve(){
    int n;cin >> n;
    vector<int> M(n+1);
    M[0]=I(n)%mod;
    M[1]=X(n)%mod;
    M[2]=C(n)%mod;
    for(int i=3;i<=n;i++) M[i]=M[i-1]*M[i-2]%mod*M[i-3]%mod;
    cout << M[n] << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
