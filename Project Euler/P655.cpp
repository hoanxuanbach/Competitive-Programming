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
    int N,M;cin >> N >> M;
    vector<int> p(N);p[0]=1;
    for(int i=1;i<N;i++){
        p[i]=p[i-1]*10;
        if(i>10) p[i]%=M;
    }

    int res=0;
    vector<int> A(M),B(M);
    for(int d=1;d<=N;d++){
        int k=(d+1)/2;
        vector<int> f(k);
        for(int i=0;i<k;i++){
            if(2*i==d-1) f[i]=p[i]%M;
            else f[i]=(p[i]+p[d-1-i])%M;
        }
        int s=(k+1)/2;
        for(int i=0;i<M;i++) A[i]=B[i]=0;
        
        cout << d << endl;

        function<void(int,int)> dfsA = [&](int i,int x){
            if(i==s){
                A[x]++;
                return;
            }
            for(int t=(i==0);t<=9;t++) dfsA(i+1,(x+f[i]*t)%M);
        };
        dfsA(0,0);

        function<void(int,int)> dfsB = [&](int i,int x){
            if(i==k){
                B[x]++;
                return;
            }
            for(int t=(i==0);t<=9;t++) dfsB(i+1,(x+f[i]*t)%M);
        };
        dfsB(s,0);

        for(int i=0;i<M;i++) res=(res+A[i]*B[(M-i)%M]);
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
