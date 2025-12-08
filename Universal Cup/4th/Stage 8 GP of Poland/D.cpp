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

const int inf = 1e18;
const int maxn = 2e5+5;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}


void solve(){
    int n,SL,SD,SR,SU;
    cin >> n >> SL >> SD >> SR >> SU;
    
    vector<vector<int>> a(n+1,vector<int>(n+1,0)),f(n+1,vector<int>(n+1,0));
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin >> a[i][j];
            f[i][j]=a[i][j]+f[i-1][j]+f[i][j-1]-f[i-1][j-1];
            a[i][j]+=a[i-1][j];
        }
    }

    vector<vector<pii>> pA(n+1,vector<pii>(n+1,{0,0}));
    vector<vector<pii>> pB(n+1,vector<pii>(n+1,{0,0}));
    vector<vector<pii>> pC(n+1,vector<pii>(n+1,{0,0}));
    vector<vector<pii>> pD(n+1,vector<pii>(n+1,{0,0}));

    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++){
        pii X=pA[i-1][j];
        X.first=min(X.first,pA[i][j-1].first+a[i][j]);
        X.second=max(X.second,pA[i][j-1].second+a[i][j]);
        pA[i][j]=X;
    }
    for(int i=1;i<=n;i++) for(int j=n-1;j>=0;j--){
        pii X=pB[i-1][j];
        X.first=min(X.first,pB[i][j+1].first+a[i][j+1]);
        X.second=max(X.second,pB[i][j+1].second+a[i][j+1]);
        pB[i][j]=X;
    }
    for(int i=n-1;i>=0;i--) for(int j=1;j<=n;j++){
        pii X=pC[i+1][j];
        X.first=min(X.first,pC[i][j-1].first+a[n][j]-a[i][j]);
        X.second=max(X.second,pC[i][j-1].second+a[n][j]-a[i][j]);
        pC[i][j]=X;
    }
    for(int i=n-1;i>=0;i--) for(int j=n-1;j>=0;j--){
        pii X=pD[i+1][j];
        X.first=min(X.first,pD[i][j+1].first+a[n][j+1]-a[i][j+1]);
        X.second=max(X.second,pD[i][j+1].second+a[n][j+1]-a[i][j+1]);
        pD[i][j]=X;
    }

    for(int i=0;i<=n;i++) for(int j=0;j<=n;j++){
        int A=f[i][j],B=f[i][n]-f[i][j],C=f[n][j]-f[i][j],D=f[n][n]-A-B-C;

        auto [LA,RA]=pA[i][j];
        auto [LB,RB]=pB[i][j];
        auto [LC,RC]=pC[i][j];
        auto [LD,RD]=pD[i][j];

        int L=LA,R=RA;
        L=max(L,SU-RB);
        R=min(R,SU-LB);
        if(L>R) continue;

        int T=D+B-SR-SU;
        L=max(L,LD-T);
        R=min(R,RD-T);

        if(L>R) continue;
        T=SD-T;
        L=max(L,T-RC);
        R=min(R,T-LC);

        if(L>R) continue;
        cout << "TAK\n";
        
        return;
    }
    cout << "NIE\n";
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}

