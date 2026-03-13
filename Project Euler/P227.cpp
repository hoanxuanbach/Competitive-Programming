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

#define ld long double
const ld eps = 1e-6;
void solve(){
    int N=100,S=N/2;
    vector<vector<ld>> f;
    for(int i=1;i<=S;i++){
        int x=1,y=i+1;
        vector<ld> g(S+1);g[i-1]=1;g[S]=1;
        for(int a=-1;a<=1;a++) for(int b=-1;b<=1;b++){
            int nx=x+a,ny=y+b;
            ld p=(ld)1/36;
            if(!a) p=p*4;
            if(!b) p=p*4;
            if(nx>ny) swap(nx,ny);
            if(nx==ny) continue;
            int d=min(ny-nx,N-(ny-nx));
            g[d-1]-=p;
        }
        f.push_back(g);
    }
    for(int x=0;x<S;x++){
        //for(int i=x;i<S;i++) if(abs(f[i][x])>eps) swap(f[i],f[x]);
        for(int i=x+1;i<S;i++){
            ld k=f[i][x]/f[x][x];
            for(int j=x;j<=S;j++) f[i][j]-=f[x][j]*k;
        }
    }
    ld res=f[S-1][S]/f[S-1][S-1];
    cout << setprecision(10) << fixed << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
