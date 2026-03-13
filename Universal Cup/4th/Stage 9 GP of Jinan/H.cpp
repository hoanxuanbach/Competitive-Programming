#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
int mod;
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

int f[3005][3005],g[3005];

void solve(){
    int n;cin >> n >> mod;
    for(int i=0;i<=n;i++) f[0][i]=1;
    for(int x=1;x<=n;x++){
        int m=n/x;f[x][0]=1;
        for(int i=1;i<=m;i++) f[x][i]=0;
        for(int i=0;i*2+1<=x;i++){
            for(int k=0;k<=m;k++) g[k]=f[x][k];
            
            for(int k=1;k<=m;k++){
                int val=(i*2+1!=x?f[i][k]*f[x-1-i][k]:f[i][min(2*k,n)])%mod;
                for(int j=k;j<=m;j++) f[x][j]=(f[x][j]+g[j-k]*val)%mod;
            }
        }
    }
    cout << f[n][1] << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}
