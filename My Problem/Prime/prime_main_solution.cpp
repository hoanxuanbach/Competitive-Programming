#include<bits/stdc++.h>
using namespace std;
const int mod=998244353;
const int maxn=1e6+5;
const int maxa=1e6;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=1LL*res*a%mod;
        a=1LL*a*a%mod;n>>=1;
    }
    return res;
}
int prime[maxa+5],inv[maxn],fac[maxn],dfac[maxn];
vector<int> num[maxa+5];
int C(int k,int n){
    return 1LL*fac[n]*dfac[k]%mod*dfac[n-k]%mod;
}
int cal(int n){
    //0*nC0+1*nC1+...+n*nCn=n*2^(n-1)
    return 1LL*n*power(2,n-1)%mod;
}
int n;
void pre_cal(){
    for(int i=2;i<=maxa;i++){
        if(prime[i]==0){
            for(int j=i;j<=maxa;j+=i) prime[j]=i;
            int cur=1,cnt=0;
            while(cur<=maxa/i){cur*=i;cnt++;}
            num[i].assign(cnt+1,0);num[i][0]=n;
        }
    }
    inv[0]=inv[1]=fac[0]=fac[1]=dfac[0]=dfac[1]=1;
    for(int i=2;i<=n;i++){
        fac[i]=1LL*fac[i-1]*i%mod;
        inv[i]=mod-1LL*(mod/i)*inv[mod%i]%mod;
        dfac[i]=1LL*dfac[i-1]*inv[i]%mod;
    }
}
int add(int a,int b){
    return ((a+=b)>=mod?a-mod:a);
}
int sub(int a,int b){
    return ((a-=b)<0?a+mod:a);
}
int s[maxn];
int cal2(int p){
    sort(num[p].begin(),num[p].end(),greater<int>());
    int pre=0,sum=1;
    for(int i=(int)num[p].size()-1;i>=1;i--){
        int cur=0;
        for(int j=0;j<=num[p][i];j++){
            cur=add(cur,C(j,num[p][i]));
            if(j<pre) s[j]=1LL*s[j]*cur%mod;
            else s[j]=1LL*sum*cur%mod;
        }
        pre=num[p][i];sum=1LL*sum*cur%mod;
    }
    int cur=0,ans=0,total=cal(num[p][0]);
    for(int i=0;i<=pre;i++){
        cur=add(cur,C(i,num[p][0]))%mod;
        s[i]=1LL*s[i]*cur%mod;
        if(i>=1) ans=add(ans,1LL*sub(s[i],s[i-1])*i%mod);
        total=sub(total,1LL*i*C(i,num[p][0])%mod);
    }
    ans=add(ans,1LL*total*sum%mod);
    return ans;
}
void solve(){
    cin >> n;
    pre_cal();
    for(int i=1;i<=n;i++){
        int a;cin >> a;
        while(a>1){
            int j=prime[a],cnt=0;
            while(prime[a] == j){a/=j;cnt++;}
            num[j][cnt]++;num[j][0]--;
        }
    }
    int ans=0,total=cal(n);
    for(int i=2;i<=maxa;i++){
        if(num[i].empty()) continue;
        if(num[i][0]==n) continue;
        ans=sub(add(ans,total),cal2(i));
    }
    cout << ans << '\n';
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
