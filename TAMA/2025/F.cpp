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
const int maxn = 2e6+5;
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

const int root=3;
const int iroot=power(3,mod-2);
void fft(vector<int> &a,bool invert){
    int n=(int)a.size();
    for(int i=1,j=0;i<n;i++){
        int bit=n>>1;
        while(j&bit){j^=bit;bit>>=1;}
        j^=bit;
        if(i<j) swap(a[i],a[j]);
    }
    for(int len=2;len<=n;len<<=1){
        int wn=power((invert?iroot:root),(mod-1)/len);
        for(int i=0;i<n;i+=len){
            int w=1;
            for(int j=0;j<len/2;j++){
                int u=a[i+j],v=a[i+j+len/2]*w%mod;
                a[i+j]=(u+v)%mod;
                a[i+j+len/2]=(u-v+mod)%mod;
                w=w*wn%mod;
            }
        }
    }
    if(invert){
        int dd=power(n,mod-2);
        for(int i=0;i<n;i++) a[i]=a[i]*dd%mod;
    }
    return;
}

void solve(){   
    int n,k;cin >> n >> k;
    vector<int> a(n);
    int pw=1;a[0]=k%mod;
    for(int i=1;i<n;i++){
        pw=pw*2%mod;
        a[i]=(a[i-1]*i+pw+i*i)%mod;
    }

    combi(n);
    vector<int> b(n);
    for(int i=0;i<n;i++) b[i]=C(n-1,i);
    fft(a,false);fft(b,false);

    int d=((__int128)n*k-1)/(n-1),x=((__int128)n*k-1)%(n-1);
    for(int i=0;i<n;i++) a[i]=a[i]*power(b[i],d)%mod;
    fft(a,true);

    int res=0;
    for(int i=0;i<=x;i++){
        res=(res+a[n-i-1]*C(x,i))%mod;
        //for(int j=n-1;j>i;j--) a[j]=(a[j]+a[j-1])%mod;
    }
    cout << res << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}