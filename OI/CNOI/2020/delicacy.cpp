#include<bits/stdc++.h>
using namespace std; 
#define int long long
#define pii pair<int,int>
#define piii pair<pii,int> 
#define fi first
#define se second
const int inf = 1e18;
const int mod = 998244353;
const int inv2 = (mod+1)/2;
const int maxn = 4e5+5;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}

int fac[maxn],dfac[maxn],inv[maxn];
void combi(int n){
    fac[0]=1;
    for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;
    dfac[n]=power(fac[n],mod-2);
    for(int i=n;i>=1;i--){
        dfac[i-1]=dfac[i]*i%mod;
        inv[i]=dfac[i]*fac[i-1]%mod;
    }
}
int C(int n,int k){
    return fac[n]*dfac[k]%mod*dfac[n-k]%mod;
}

struct matrix{
    int x[255][255],n,m;
    matrix(){}
    void init(int _n,int _m){
        n=_n;m=_m;
        for(int i=0;i<n;i++) for(int j=0;j<m;j++) x[i][j]=-inf;
    };
    friend matrix operator*(matrix a,matrix b){
        matrix c;c.init(a.n,b.m);
        for(int i=0;i<a.n;i++) for(int j=0;j<b.m;j++) for(int k=0;k<a.m;k++) c.x[i][j]=max(c.x[i][j],a.x[i][k]+b.x[k][j]);
        return c;
    }
}S,X[35];

void solve(){   
    int n,m,T,k;cin >> n >> m >> T >> k;
    vector<int> c(n);
    for(int i=0;i<n;i++) cin >> c[i];

    int N=n*5;
    S.init(1,N);
    X[0].init(N,N);

    S.x[0][0]=c[0];
    while(m--){
        int u,v,w;cin >> u >> v >> w;u--;v--;
        X[0].x[u*5+w-1][v*5]=max(X[0].x[u*5+w-1][v*5],c[v]);
    }
    for(int i=0;i<n;i++) for(int j=0;j<4;j++) X[0].x[i*5+j][i*5+j+1]=0;
    for(int i=1;i<30;i++) X[i]=X[i-1]*X[i-1];

    vector<array<int,3>> event;
    for(int i=0;i<k;i++){
        int t,x,y;cin >> t >> x >> y;x--;
        event.push_back({t,x,y});
    }
    event.push_back({T,0,0});
    sort(event.begin(),event.end());

    int lst=0;
    for(auto [t,x,y]:event){
        if(lst<t){
            int d=t-lst;
            for(int i=29;i>=0;i--) if(d>>i&1) S=S*X[i];
            lst=t;
        }
        S.x[0][x*5]+=y;
    }
    cout << max(S.x[0][0],-1LL) << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}