#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod = 998244353;
const int L = 30;
const int K = 15;

int f[(1<<K)][L][L],g[(1<<K)][L];

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);


    for(int j=0;j<L;j++) f[0][j][j]=1;
    for(int i=1;i<(1<<K);i++) for(int j=K-1;j>=0;j--) for(int k=j;k<K;k++){
        if(j+1<K) f[i][j][k]=f[i][j+1][k];
        if(i>=(1<<j)) f[i][j][k]=(f[i][j][k]+f[i-(1<<j)][j][k]*(1<<j))%mod;
    }

    for(int i=0;i<L;i++) g[0][i]=1;
    for(int i=1;i<(1<<K);i++) for(int j=L-1;j>=0;j--){
        if(j+1<L) g[i][j]=g[i][j+1];
        if((i<<K)>=(1<<j)){
            int d=(i<<K)-(1<<j);
            int x=d>>K,y=d-(x<<K);
            for(int k=j;k<L;k++) g[i][j]=(g[i][j]+f[y][j][k]*g[x][k]%mod*(1<<j))%mod;
        }
    }

    int T,a,n;cin >> T >> a >> n;
    
    int ans=0;
    for(int i=0;i<T;i++){
        int res=0,x=n>>K,y=n-(x<<K);
        for(int j=0;j<K;j++) res=(res+f[y][0][j]*g[x][j])%mod;
        //cout << n << ' ' << res << ' ' << x << ' ' << y << '\n';
        n=(n+a)%(1<<L);
        ans+=(res^i);
    }
    cout << ans << '\n';
}

