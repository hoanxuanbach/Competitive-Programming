#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>

int power(int a,int n,int mod){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}

void solve(){

    auto get_phi = [&](int mod){
        vector<int> P={2,3,5,7};

        int ret=1;
        for(int x:P){
            int k=0,d=1;
            while(mod%x==0) mod/=x,d*=x;
            if(d>1) ret*=d/x*(x-1);
        }
        assert(mod==1);
        return ret;
    };

    function<pii(int,int,int)> dfs = [&](int x,int n,int mod){
        if(n==1) return pii{x,0};
        else if(mod==1) return pii{0,1};
        else{
            int p=get_phi(mod);
            pii T=dfs(x,n-1,p);
            if(T.second || T.first*log(x)>=log(mod)) return pii{power(x,T.first+p,mod),1};
            else return pii{power(x,T.first,mod),0};
        }
    };

    auto f = [&](int n,int mod){
        if(n==0) return n+1;
        else if(n==1) return n+2;
        else if(n==2) return 2*n+3;
        else if(n==3) return power(2,n+3,mod)-3;
        else if(n==4) return dfs(2,n+3,mod).first-3;
        else return dfs(2,10,mod).first-3;
    };

    int mod=1;
    for(int i=0;i<8;i++) mod*=14;

    int res=0;
    for(int i=0;i<=6;i++){
        cout << i << ' ' << f(i,mod) << '\n';
        res=(res+f(i,mod))%mod;
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
