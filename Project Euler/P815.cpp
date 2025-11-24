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

ld f[65][65][65][65];

void solve(){
    int n;cin >> n;
    ld res=0,pre=0;
    vector<array<int,4>> ord;
    for(int a=0;a<=n;a++) for(int b=0;a+b<=n;b++) for(int c=0;a+b+c<=n;c++) for(int d=0;a+b+c+d<=n;d++) ord.push_back({a,b,c,d});
    sort(ord.begin(),ord.end(),[&](array<int,4> x,array<int,4> y){
        int X=x[1]+x[2]*2+x[3]*3+(n-x[0]-x[1]-x[2]-x[3])*4;
        int Y=y[1]+y[2]*2+y[3]*3+(n-y[0]-y[1]-y[2]-y[3])*4;
        return X<Y;
    });
    for(int mx=1;mx<=n;mx++){
        for(auto [a,b,c,d]:ord) f[a][b][c][d]=0;
        f[n][0][0][0]=1;
        for(auto [a,b,c,d]:ord){
            if(b+c+d>mx) continue;
            int e=n-a-b-c-d;
            int T=4*n-(b+2*c+3*d+4*e);
            if(a){
                f[a-1][b+1][c][d]+=f[a][b][c][d]*(ld)(4*a)/T;
            }
            if(b){
                f[a][b-1][c+1][d]+=f[a][b][c][d]*(ld)(3*b)/T;
            }
            if(c){
                f[a][b][c-1][d+1]+=f[a][b][c][d]*(ld)(2*c)/T;
            }
            if(d){
                f[a][b][c][d-1]+=f[a][b][c][d]*(ld)(d)/T;
            }
        }
        ld val=f[0][0][0][0];
        res+=(val-pre)*mx;pre=val;
    }
    cout << setprecision(12) << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
