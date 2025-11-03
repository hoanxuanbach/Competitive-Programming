#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 1e9+7;
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
    int N,S;cin >> N >> S;
    /*
    int cnt=1;
    vector<int> q(N+1);
    for(int i=2;i<=N;i++){
        if(!q[i]){
            for(int j=i;j<=N;j+=i) q[j]=i;
        }
        int x=i,s=0;
        while(x>1){
            int j=q[x];
            if(j<S) s=(s+j)%3;
            while(x%j==0) x/=j;
        }
        if(!s) cnt++;
    }
    cout << cnt << '\n';
    */

    vector<int> X;
    
    vector<int> p(S);
    for(int i=2;i<S;i++) if(!p[i]){
        if(i!=3) X.push_back(i);
        for(int j=i;j<S;j+=i) p[j]=1;
    }

    int T=30;
    vector<int> fac(T,1),dfac(T,1);
    for(int i=1;i<T;i++) fac[i]=fac[i-1]*i%mod,dfac[i]=power(fac[i],mod-2);

    vector<vector<int>> f(T,vector<int>(T,0));
    for(int i=0;i<T;i++) for(int j=0;i+j<T;j++){
        for(int x=0;x<=i;x++) for(int y=0;y<=j;y++){
            if((x+2*y)%3!=0) continue;
            int val=((x+y)&1?-1:1);
            int C=fac[i]*dfac[x]%mod*dfac[i-x]%mod;
            int D=fac[j]*dfac[y]%mod*dfac[j-y]%mod;
            f[i][j]+=val*C*D;
        }
    }

    int A=0,B=0;
    __int128 res=0;
    function<void(int,int)> dfs = [&](int i,int x){
        if(i==(int)X.size()){
            int k=((A+B)&1?-1:1);
            res+=((__int128)f[A][B]*k*(N/x))%(N+1);
            return;
        }
        dfs(i+1,x);
        if(x<=N/X[i]){
            if(X[i]%3==1) A++;
            else B++;
            dfs(i+1,x*X[i]);
            if(X[i]%3==1) A--;
            else B--;
        }
    };
    dfs(0,1);
    int ans=(res%(N+1)+(N+1))%(N+1);
    cout << ans << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
