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

void solve(){
    int m;cin >> m;
    int n=m*(m+1)/2;
    vector<int> A(n+1);
    for(int i=1;i<=n;i++) A[i]=i+1;
    for(int i=1;i<=m;i++) A[i*(i+1)/2]=i*(i-1)/2+1;

    vector<int> B(n+1);
    for(int i=1;i<=n;i++) B[i]=(i*mod%n)+1;

    vector<int> C(n+1);
    for(int i=1;i<=n;i++) C[B[i]]=i;

    vector<int> P(n+1);
    for(int i=1;i<=n;i++) P[i]=C[A[B[i]]];

    vector<vector<int>> S;

    vector<int> vis(n+1,1);
    for(int i=1;i<=n;i++) if(vis[i]){
        int x=i;
        vector<int> v;
        while(vis[x]){
            v.push_back(x);
            vis[x]=false;x=P[x];
        }
        S.push_back(v);
    }
    
    vector<int> f(n+1);f[n]=1;
    for(int i=n-1;i>=1;i--) f[i]=f[i+1]*(n-i)%mod;

    vector<int> inv(n+1);
    for(int i=1;i<=n;i++) inv[i]=power(i,mod-2);

    int cnt=1;
    for(int i=1;i<=m;i++) cnt=cnt*i%mod;

    int res=cnt;
    for(auto fx:S) for(auto fy:S){
        int sx=(int)fx.size(),sy=(int)fy.size();
        int g=__gcd(sx,sy);
        vector<vector<int>> X(g),Y(g);
        for(int i=0;i<sx;i++) X[i%g].push_back(fx[i]);
        for(int i=0;i<sy;i++) Y[i%g].push_back(fy[i]);

        int dd=inv[sx]*inv[sy]%mod*g%mod;
        for(int d=0;d<g;d++){
            int a=0,b=0;
            for(int i=0;i<g;i++){
                int j=(i+d)%g;
                for(int x:X[i]) for(int y:Y[j]){
                    (a+=f[x]*(x<y))%=mod;
                    b+=(x>y);
                }
            }
            a=a*b%mod;
            res=(res+cnt*dd%mod*a)%mod;
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
