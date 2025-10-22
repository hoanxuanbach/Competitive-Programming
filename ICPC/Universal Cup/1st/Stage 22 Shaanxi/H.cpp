#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int mod = 998244353;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}

void solve(){
    int n;cin >> n;
    
    int S=sqrtl(n);
    vector<int> A(S+1,-1),B(S+1,-1);

    function<int(int)> f = [&](int x){  
        if(x==1) return 1LL;
        if(x<=S){
            if(A[x]!=-1) return A[x];
        }
        else{
            if(B[n/x]!=-1) return B[n/x];
        }
        int res=1,s=sqrtl(x);
        for(int i=1;i<=s;i++){
            int l=x/(i+1),r=x/i;
            if(l<r) (res+=(r-l)*f(i))%=mod;
        }
        for(int i=2;i<=x/(s+1);i++) (res+=f(x/i))%=mod;

        if(x<=S) return A[x]=res;
        else return B[n/x]=res;
    };

    int K=20210926;
    vector<int> g(n/K+1,0);
    for(int i=n/K;i>=1;i--){
        int l=2,r=K;
        
        g[i]=1;
        while(l<=r && i*l<=n/K) g[i]=(g[i]+g[i*l])%mod,l++;
        while(l<=r && i*l<=S) g[i]=(g[i]+f(n/(i*l)))%mod,l++;
        for(int j=1;j<=S;j++){
            int lt=max(l,(n/(j+1))/i+1),rt=min(r,(n/j)/i);
            if(lt<=rt) g[i]=(g[i]+(rt-lt+1)*f(j))%mod;
        }
    }
    if(n<=K) cout << f(n) << '\n';
    else cout << g[1] << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}