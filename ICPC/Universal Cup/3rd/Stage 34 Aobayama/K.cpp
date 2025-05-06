#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod = 998244353;
const int maxn = 2e5+5;

int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}

int fac[maxn],dfac[maxn],inv[maxn],p2[maxn];
 
void combi(int n){
    fac[0]=p2[0]=1;
    for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod,p2[i]=p2[i-1]*2%mod;
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

int f[maxn];

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);

    int n;cin >> n;
    vector<int> a(2*n);
    for(int i=0;i<2*n;i++) cin >> a[i];
    sort(a.begin(),a.end());
    combi(2*n);

    for(int i=0;i<=2*n;i++){
        f[i]=C(2*n,i);
        if(i>1) f[i]=(f[i]+f[i-2])%mod;
    }

    int lst=0,sum=0;
    for(int t=0;t<2*n;t++){
        int cnt=a[t]-lst,m=2*n-t;lst=a[t];
        
        int l=max(t-m,0LL),r=t;
        int val=n*(C(2*n,m+l)-C(2*n,m+r+1))%mod;
        
        if(l>=r-3){
            for(int i=l;i<=r;i++){
                int s=(i+1)/2;
                int num=C(2*n,m+i)-C(2*n,m+i+1);
                (val-=s*num)%=mod;
            }
        }
        else{
            if(!(l&1)) (val-=((l+1)/2)*(C(2*n,m+l)-C(2*n,m+l+1)))%=mod,l++;
            if(r&1) (val-=((r+1)/2)*(C(2*n,m+r)-C(2*n,m+r+1)))%=mod,r--;
            
            {
                (val-=((l+1)/2)*C(2*n,m+l))%=mod;
                (val+=((r+1)/2)*C(2*n,m+r+1))%=mod;

                val=(val-f[m+r-1]+f[m+l])%mod;

                //for(int i=l+2;i<=r;i+=2) (val-=C(2*n,m+i))%=mod;   
            }
        }

        val=(val+mod)%mod;
        sum=(sum+val*cnt%mod*power(C(2*n,m),mod-2))%mod;
    }

    cout << sum << '\n';
}