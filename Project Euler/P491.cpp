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

int d[15][15][15][15];

void solve(){
    d[0][0][0][0]=1;
    for(int i=1;i<=9;i++){
        for(int t=0;t<=2*(i-1);t++){
            for(int j=0;j<i;j++) for(int x=0;x<=10;x++){
                for(int k=0;k<=2;k++){
                    int nt=t+k,nj=j+(k==2),nx=(x+i*k)%11;
                    d[i][nt][nj][nx]+=d[i-1][t][j][x];
                }
            }
        }
    }
    auto C = [&](int x,int k){
        if(k==0) return 1LL;
        else if(k==1) return x;
        else return x*(x-1)/2;
    };
    vector<int> fac(11,1),pw(11,1);
    for(int i=1;i<=10;i++) fac[i]=fac[i-1]*i,pw[i]=pw[i-1]*2;

    int res=0;
    for(int k=0;k<=2;k++){
        int a=10-k,b=8+k;
        int mul=C(9,k)*C(10,2-k);
        cout << k << ' ' << mul << '\n';
        for(int i=0;i<=a/2;i++){
            int j=(b-(a-2*i))/2;
            if(j<0) continue;
            int val=mul*d[9][a][i][1];
            val*=(fac[a]*fac[b])/pw[i+j];
            res+=val;
        }
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
