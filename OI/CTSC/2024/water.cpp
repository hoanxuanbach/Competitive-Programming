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
const int maxn = 5e5+5;
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

const int LG = 20;
int n,a[maxn];
int L[maxn][LG],R[maxn][LG];

void solve(){   
    cin >> n;
    for(int i=1;i<=n;i++) cin >> a[i];
    for(int i=2;i<n;i++){
        L[i][0]=-inf;R[i][0]=inf;
        if(a[i]>=max(a[i-1],a[i+1])) L[i][0]=a[i]+min(a[i-1],a[i+1]);
        if(a[i]<=min(a[i-1],a[i+1])) R[i][0]=a[i]+max(a[i-1],a[i+1]);
    }
    for(int j=1;j<LG;j++){
        for(int i=2;i<=(n-(1<<j));i++){
            L[i][j]=max(L[i][j-1],L[i+(1<<(j-1))][j-1]);
            R[i][j]=min(R[i][j-1],R[i+(1<<(j-1))][j-1]);
        }
    }
    int res=0;
    for(int i=1;i<n;i++){
        int j=i+1,l=-inf,r=inf;
        for(int k=LG-1;k>=0;k--){
            if((j+(1<<k))>n) continue;
            int nl=max(l,L[j][k]),nr=min(r,R[j][k]);
            if(nl<nr) l=nl,r=nr,j+=(1<<k);
        }
        res+=j-i;
    }
    cout << res << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}