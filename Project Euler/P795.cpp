#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 998244353;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
 
const int maxn = 2e5+5;
const int inf = 1e18;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}

void solve(){
    int N;cin >> N;
    vector<int> f(N+1),p(N+1),d(N+1);
    f[1]=1;
    for(int i=2;i<=N;i++){
        if(!p[i]){
            for(int j=i;j<=N;j+=i) p[j]=i;
        }
        if((i/p[i])%p[i]==0) f[i]=f[i/p[i]]*p[i];
        else f[i]=f[i/p[i]]*(p[i]-1);
    }

    int res=0;
    for(int n=1;n<=N;n++){
        if(n&1) res-=n;
        int x=n;d[n]=1;
        while(x>1){
            int j=p[x],k=0;
            while(x%j==0) x/=j,k^=1;
            if(k) d[n]*=j;
        }
        d[n]=sqrtl(n/d[n]);
    }
    for(int x=2;x<=N;x+=2) for(int n=x;n<=N;n+=x){
        res+=n*f[x]*d[x]/x;
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
