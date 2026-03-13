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

const int inv2=(mod+1)/2;
void solve(){
    int n,m;cin >> n >> m;

    if(n==1){
        cout << 1 << '\n';
        return;
    }

    vector<vector<int>> a(n,vector<int>(n));
    for(int i=0;i<m;i++){
        int u,v;cin >> u >> v;u--;v--;
        a[u][v]=a[v][u]=1;
    }
    
    vector<int> bcnt(1<<n);
    for(int i=0;i<(1<<n);i++) bcnt[i]=__builtin_popcount(i);
    
    vector<int> T(1<<n);
    for(int s=1;s<n;s++){
        vector<vector<int>> g(1<<s,vector<int>(s));
        for(int i=0;i<s;i++) if(a[s][i]) g[1<<i][i]=1;
        for(int mask=0;mask<(1<<s);mask++) for(int x=0;x<s;x++) if(g[mask][x]){
            for(int y=0;y<s;y++) if(!(mask>>y&1) && a[x][y]) (g[mask|(1<<y)][y]+=g[mask][x])%=mod;
        }
        for(int i=0;i<s;i++) if(a[s][i]) for(int mask=0;mask<(1<<s);mask++) (T[mask|(1<<s)]+=g[mask][i]*(bcnt[mask]>1?inv2:1))%=mod;
    }

    

    vector<vector<int>> gg(1<<n);
    for(int mask=1;mask<(1<<n);mask++){
        int M=mask;
        while(M){
            gg[mask].push_back(M);
            M=(M-1)&mask;
        }
    }

    vector<int> b(1<<n),f(1<<n);
    for(int s=1;s<n;s++){
        for(int mask=1;mask<(1<<s);mask++) if(T[mask|(1<<s)]){
            int cycle=mask|(1<<s);
            int M=mask^((1<<s)-1);
            
            b[0]=1;
            for(int x:gg[M]) b[x]=0;
            for(int i=0;i<=s;i++) if(cycle>>i&1) for(int x=M;x;x=(x-1)&M){
                for(int y=x;y;y=(y-1)&x) b[x]=(b[x]+f[y|(1<<i)]*b[x^y])%mod;
            }
            
            f[cycle]=(f[cycle]+T[cycle])%mod;
            for(int x:gg[M]) f[cycle|x]=(f[cycle|x]+T[cycle]*b[x])%mod;
        }
    }
    cout << f[(1<<n)-1] << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
