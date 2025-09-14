#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int inf = 1e18;
const int mod = 998244353;
const int maxn = 1005;

int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}

int fac[maxn],dfac[maxn],inv[maxn];
int C(int n,int k){
    if(n<k || k<0 || n<0) return 0;
    return fac[n]*dfac[n-k]%mod*dfac[k]%mod;
}

void combi(int n){
    fac[0]=inv[0]=1;
    for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;
    dfac[n]=power(fac[n],mod-2);
    for(int i=n;i>=1;i--){
        dfac[i-1]=dfac[i]*i%mod;
        inv[i]=dfac[i]*fac[i-1]%mod;
    }
}

void solve(){
    int n;cin >> n;
    vector<int> a(n+2);
    for(int i=1;i<=n;i++) cin >> a[i];

    auto cal = [&](vector<int> x){

        vector<int> lt(n+2),rt(n+2);
        for(int i=1;i<=n;i++){
            for(int j=1;j<i;j++) lt[i]+=(x[j]>x[i]);
        }
        for(int i=n;i>=1;i--){
            for(int j=i+1;j<=n;j++) rt[i]+=(x[j]>x[i]);
        }

        int res=0,num=1;
        vector<int> cnt(n+1),all(n+1);
        for(int i=1;i<=n;i++) cnt[a[i]]++;
        for(int i=1;i<=n;i++) num=num*dfac[cnt[i]]%mod;

        //cout << "Start " << num << '\n';

        int cur_sum=0;
        for(int i=1;i<=n;i++){

            vector<int> pre=cnt;
            for(int i=1;i<=n;i++) pre[i]+=pre[i-1];
            int cur=0,ls=0,ss=0;
            for(int k=n;k>=1;k--){
                int t0=0,t1=0;
                {
                    int mx=ls-cur;
                    if(mx>=0) mx/=2;
                    else mx=-1;
                    t0+=(mx+1)*cur+mx*(mx+1)/2;
                    t0+=(ls-mx)*(ls-mx-1)/2;
                    t0%=mod;
                }
                {
                    ls--;cur++;
                    int mx=ls-cur;
                    if(mx>=0) mx/=2;
                    else mx=-1;
                    t1+=(mx+1)*cur+mx*(mx+1)/2;
                    t1+=(ls-mx)*(ls-mx-1)/2;
                    t1%=mod;
                    ls++;cur--;
                }
                int add=0;
                //j=k
                if(k<x[i]) add=(add+t0*(cnt[k]-1)%mod*inv[ls+1]%mod*cnt[k])%mod;
                //j>k
                if(k+1<x[i]){
                    add=(add+t1*cnt[k]%mod*inv[ls]%mod*ss)%mod;
                }
                //j<k
                {
                    int t=min(x[i],k)-1;
                    add=(add+t0*cnt[k]%mod*inv[ls+1]%mod*pre[t])%mod;
                }
                res=(res+add*fac[n-i]%mod*num)%mod;
                cur+=all[k];
                ls+=cnt[k];
                if(k<x[i]) ss+=cnt[k];
            }

            int lval=0,rval=0;
            for(int j=x[i];j<=n;j++) rval+=cnt[j],lval+=all[j];
            for(int j=x[i]-1;j>=1;j--){
                if(!cnt[j]){
                    lval+=all[j];
                    continue;
                }
                
                int add=(cur_sum+min(lval,rval))%mod;
                res=(res+add*fac[n-i]%mod*num%mod*cnt[j])%mod;
                rval+=cnt[j],lval+=all[j];
            }
            num=num*cnt[x[i]]%mod;
            cnt[x[i]]--;all[x[i]]++;
            cur_sum+=min(lt[i],rt[i]);
        }
        return res;
    };

    vector<int> x(n+2),y(n+2);
    for(int i=1;i<=n;i++) cin >> y[i];
    for(int i=1;i<=n;i++) cin >> x[i];

    vector<int> lt(n+2),rt(n+2);
    for(int i=1;i<=n;i++){
        for(int j=1;j<i;j++) lt[i]+=(x[j]>x[i]);
    }
    for(int i=n;i>=1;i--){
        for(int j=i+1;j<=n;j++) rt[i]+=(x[j]>x[i]);
    }

    int res=(cal(x)-cal(y)+mod)%mod;
    for(int i=1;i<=n;i++) res+=min(lt[i],rt[i]);
    cout << res%mod << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    combi(1000);
    int test;cin >> test;
    while(test--) solve();
}
