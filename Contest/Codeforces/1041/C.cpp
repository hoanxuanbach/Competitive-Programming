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
    int n,k;cin >> n >> k;
    vector<vector<int>> x(2,vector<int>(2,-inf));
    
    int total=0;
    vector<int> a(n),b(n);
    for(int i=0;i<n;i++) cin >> a[i];
    for(int i=0;i<n;i++) cin >> b[i];
    for(int i=0;i<n;i++){
        total+=abs(a[i]-b[i]);
        if(a[i]>b[i]) swap(a[i],b[i]);
    }
    vector<int> ord(n);
    iota(ord.begin(),ord.end(),0);
    sort(ord.begin(),ord.end(),[&](int x,int y){
        return a[x]<a[y];
    });

    int res=inf;
    for(int i=1;i<n;i++){
        int x=ord[i-1],y=ord[i];
        int cur=abs(a[x]-b[x])+abs(a[y]-b[y]);
        vector<int> v={a[x],b[x],a[y],b[y]};
        sort(v.begin(),v.end());
        res=min(res,v[2]+v[3]-v[0]-v[1]-cur);
    }
    cout << total+res << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}