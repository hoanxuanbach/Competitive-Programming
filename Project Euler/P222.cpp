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
void solve(){
    int M=21;
    vector<int> r(M);
    for(int i=0;i<M;i++) r[i]=30+i;
    
    vector<vector<ld>> f((1<<M),vector<ld>(M,inf));
    for(int i=0;i<M;i++) f[(1<<i)][i]=r[i];

    for(int mask=1;mask<(1<<M);mask++){
        for(int i=0;i<M;i++) if(mask>>i&1){
            if(f[mask][i]==inf) continue;
            for(int j=0;j<M;j++) if(!(mask>>j&1)){
                ld a=r[i]+r[j],b=100-(r[i]+r[j]);
                ld w=sqrtl(a*a-b*b);
                f[mask^(1<<j)][j]=min(f[mask^(1<<j)][j],f[mask][i]+w);
            }
        }
    }

    ld res=inf;
    for(int i=0;i<M;i++) res=min(res,f[(1<<M)-1][i]+r[i]);
    cout << setprecision(6) << fixed << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
