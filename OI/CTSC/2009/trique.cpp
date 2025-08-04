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

int s[maxn];

void solve(){   
    int n;cin >> n;
    for(int i=n;i>=1;i--) cin >> s[i];
    int l=1,r=n,res=0;
    while(l<=n && s[l]==1) l++;
    while(r>=l && s[r]!=1) r--,res++;
    if(r<l) cout << res << '\n';
    else{
        n=r-l+1;
        for(int i=l;i<=r;i++) s[i-l]=s[i];
        auto calc = [&](int x){

            //cout << "*" << x << '\n';

            int p=n,q=-1;
            for(int i=n-1;i>=0;i--) if(s[i]==x) p=i;
            for(int i=0;i<n;i++) if(s[i]==x) q=i;

            int cnt=n-p;
            
            int A=0,all=p;
            for(int i=p;i<n;i++) all+=(s[i]!=x),A+=(s[i]==1);
            int B=0;
            for(int i=0;i<p;i++) B+=(s[i]==(x^1));
            cnt+=2*all-max(A,B);

            //cout << cnt << ' ' << all << ' ' << A << ' ' << B << '\n';

            if(p==n) return cnt;

            int X=0;
            for(int i=q;i<n;i++) X+=(s[i]==1);
            cnt-=max(0LL,2*(n-q-1-X)-X);

            return cnt;
        };
        cout << res+min(calc(2),calc(3)) << '\n';
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}