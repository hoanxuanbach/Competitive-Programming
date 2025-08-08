#include<bits/stdc++.h>
using namespace std; 
#define int long long
#define pii pair<int,int>
#define piii pair<pii,int> 
#define fi first
#define se second
const int inf = 1e18;
const int mod = 1e9+7;
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
    if(n<k || k<0 || n<0) return 0;
    return fac[n]*dfac[k]%mod*dfac[n-k]%mod;
}
int sumC(int l,int r,int k){
    l=max(l,k);
    if(l>r) return 0;
    return (C(r+1,k+1)-C(l,k+1)+mod)%mod;
}
int sum2C(int l,int r,int k){
    l=max(l,k);r--;
    if(l>r) return 0;
    int sum=sumC(l+1,r+1,k+1);
    sum=(sum-(r-l+1)*C(l,k+1)%mod+mod)%mod;
    return sum;
}

void solve(){   
    int n,m;cin >> n >> m;
    int res=0;
    
    if(n==3){
        for(int b=0;b<=m/2;b++) if((m-2*b)<b) res=(res+3*b-m)%mod;
    }
    else if(n>=4){
        for(int b=1;b<=m;b++){
            for(int i=0;i<=(m-2*b)/(b+1);i++){
                int X=(m-2*b-i*(b+1))+n-4;
                int val=(sumC(max(0LL,X-b+1),X,n-4)*b%mod-sum2C(max(0LL,X-b+1),X,n-4)+mod)%mod;
                val=val*C(n-3,i)%mod;
                if(i&1) res=(res+mod-val)%mod;
                else res=(res+val)%mod;
            }
        }
        res=res*(n-2)%mod;
    }

    if(n==2){
        for(int b=0;b<=m;b++) if(m-b<b) res=(res+2*b-m)%mod;
    }
    else if(n>=3){
        for(int b=1;b<=m;b++){
            for(int i=0;i<=(m-b)/(b+1);i++){
                int X=(m-b-i*(b+1))+n-3;
                int val=(sumC(max(0LL,X-b+1),X,n-3)*b%mod-sum2C(max(0LL,X-b+1),X,n-3)+mod)%mod;
                val=val*C(n-2,i)%mod;
                if(i&1) res=(res+mod-val)%mod;
                else res=(res+val)%mod;
            }
        }
    }
    cout << (res%mod+mod)%mod << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    combi(400000);
    int test=1;cin >> test;
    while(test--) solve();
}