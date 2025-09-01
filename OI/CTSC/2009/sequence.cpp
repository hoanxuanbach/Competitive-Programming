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

void solve(){   
    int n,mx,A,B;cin >> n >> mx >> A >> B;
    int res=0;
    vector<int> x(n),f(n);
    for(int i=0;i<n;i++){
        cin >> x[i];
        if(x[i]<=A*i) res+=A*i+1-x[i],x[i]=A*i+1;
    }
    priority_queue<int> L;
    priority_queue<int,vector<int>,greater<int>> R;
    L.push(x[0]);R.push(x[0]);
    int tl=0,tr=0;f[0]=x[0];
    for(int i=1;i<n;i++){
        tl+=A,tr+=B;
        int l=L.top()+tl,r=R.top()+tr;
        if(x[i]<l) L.pop(),L.push(x[i]-tl),L.push(x[i]-tl),R.push(l-tr);
        else if(r<x[i]) R.pop(),R.push(x[i]-tr),R.push(x[i]-tr),L.push(r-tl);
        else L.push(x[i]-tl),R.push(x[i]-tr);
        f[i]=min(mx,max(A*i+1,L.top()+tl));
    }
    for(int i=n-2;i>=0;i--) f[i]=max(min(f[i],f[i+1]-A),f[i+1]-B);
    for(int i=0;i<n;i++) res+=abs(x[i]-f[i]);
    cout << res << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}