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

int f[65][65][2],g[65][65][2],cnt[65][65][2];

void solve(){
    int n;cin >> n;
    
    vector<int> X;
    while(n) X.push_back(n&1),n>>=1;
    reverse(X.begin(),X.end());
    n=(int)X.size();

    f[0][0][0]=0;
    g[0][0][0]=0;
    cnt[0][0][0]=1;

    for(int i=0;i<n;i++) for(int x=0;x<=i;x++){
        for(int k=0;k<=1;k++) for(int d=0;d<=1;d++){
            int nk=k,nx=x+d;
            if(!k){
                if(d>X[i]) continue;
                else if(d<X[i]) nk=1;
            }
            (f[i+1][nx][nk]+=f[i][x][k]*4+4*d*g[i][x][k]+cnt[i][x][k]*d*d)%=mod;
            (g[i+1][nx][nk]+=g[i][x][k]*2+cnt[i][x][k]*d)%=mod;
            (cnt[i+1][nx][nk]+=cnt[i][x][k])%=mod;
        }
    }
    int res=0;
    for(int x=1;x<=n;x++){
        int val=(f[n][x][0]+f[n][x][1])%mod;
        res=(res+val*x*x)%mod;
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
