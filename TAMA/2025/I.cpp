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
const int maxn = 4e6+5;
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
int CC(int n,int k){
    return fac[n]*dfac[k]%mod*dfac[n-k]%mod;
}

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}
/*
4000000000000000 3000000000000000 7000000000000000 8000000000000000 1000000
*/
void solve(){   
    int tA,tB,tC,tD,tK;cin >> tA >> tB >> tC >> tD >> tK;

    __int128 A=tA,B=tB,C=tC,D=tD,K=tK;
    __int128 Y=min({D,B,C/2}),X=min({C,A,D/2});
    
    __int128 N=0;
    if(C-2*B>=0 && D>=B){
        __int128 T=min(C-2*B,(D-B)/2);
        N+=T*B;
    }
    if(2*D>=C){
        auto get = [&](__int128 T){
            if(T==0) return (__int128)0;
            __int128 res=0;
            if((T&1)!=(C&1)) res+=(C-T)/2,T--;
            if(T==0) return (__int128)0;
            __int128 l=(C-T)/2,r=(C-1)/2;
            if(C&1) res+=r,r--;
            if(l<=r) res+=(r-l+1)*(l+r);
            return res;
        };
        __int128 L=max(C-2*B,(__int128)0);
        __int128 R=(2*D-C)/3;
        N+=get(R)-get(L);
    }
    {
        __int128 L=max(max((2*D-C)/3,(D-B)/2),(__int128)0);
        __int128 R=X;
        N+=D*(R-L)-(R-L)*(L+1+R);
    }

    //for(int i=1;i<=X;i++) N+=min({B,(C-i)/2,D-2*i});

    __int128 M=8*N+2*(X+Y);
    __int128 S=4*N+2*(X+Y)+1;

    int res=0,cur=1,x=1;
    for(int i=0;i<=min(K+1,S/2);i++){
        res=(res+cur)%mod;
        cur=(S-x+1)%mod*cur%mod*power(x,mod-2)%mod;x++;
        cur=(S-x+1)%mod*cur%mod*power(x,mod-2)%mod;x++;
    }
    res=res*power(2,(4*N)%(mod-1))%mod*power(3,M%(mod-1))%mod;
    int ans=res;
    cout << ans << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}