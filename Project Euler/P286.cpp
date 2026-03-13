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

ld P[55];

void solve(){
    int n,S;cin >> n >> S;
    int T=100;
    ld l=50,r=100;
    while(T--){
        ld q=(l+r)/2;

        for(int i=0;i<=S;i++) P[i]=0;
        P[0]=1;

        for(int x=1;x<=n;x++){
            ld A=(ld)x/q,B=1-A;
            for(int i=S;i>=0;i--){
                P[i+1]+=P[i]*B;
                P[i]*=A;
            }
        }
        cout << q << ' ' << P[S] << '\n';
        if(P[S]*100>2) l=q;
        else r=q;
    }
    cout << setprecision(10) << fixed << (l+r)/2 << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
