#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 14348907;
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

int f[50][1000],g[50][1000];

void solve(){
    int n;cin >> n;
    vector<int> pw(n,1);
    for(int i=1;i<n;i++) pw[i]=pw[i-1]*10%mod;

    f[0][0]=0;g[0][0]=1;
    for(int i=0;i<=n/2;i++) for(int j=0;j<=9*i;j++){
        for(int k=0;k<=9;k++){
            (f[i+1][j+k]+=f[i][j]*10+k*g[i][j])%=mod;
            (g[i+1][j+k]+=g[i][j])%=mod;
        }
    }
    auto cal = [&](int m,int d,int t){
        int total=0,cnt=0;
        for(int i=t;i<=9;i++){
            int c=d-i;
            if(c<0) continue;
            int val=(f[m-1][c]+g[m-1][c]*i*pw[m-1])%mod;
            total=(total+val)%mod;cnt=(cnt+g[m-1][c])%mod;
        }
        return pii{total,cnt};
    };
    int res=45;
    for(int m=2;m<=n;m++){
        int d=m/2;
        for(int i=0;i<=9*d;i++){
            auto [fa,ga]=cal(d,i,1);
            auto [fb,gb]=cal(d,i,0);
            fa=fa*pw[m-d]%mod;
            if(m&1){
                fa=(fa*10+ga*45*pw[d])%mod;
                ga=ga*10%mod;
            }
            int total=(fa*gb+ga*fb)%mod;
            res=(res+total)%mod;
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
