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
    int N;cin >> N;
    vector<int> pw(N+1);pw[0]=1;
    for(int i=1;i<=N;i++) pw[i]=pw[i-1]*2%mod;

    vector<int> f(N+1),A(N+1),B(N+1);
    for(int i=2;i<=N;i++) if(!f[i]){
        for(int j=i;j<=N;j+=i) f[j]=i;
    }
    A[1]=1;B[1]=0;
    for(int i=2;i<=N;i++){
        vector<int> X;

        int x=i;
        while(x>1){
            int j=f[x];
            X.push_back(j);
            while(x%j==0) x/=j;
        }
        x=X[0];
        if((i/x)%x==0) A[i]=A[i/x]*x;
        else A[i]=A[i/x]*(x-1);
        if(i&1){
            int s=(int)X.size();
            for(int mask=0;mask<(1<<s);mask++){
                int y=1,d=1;
                for(int j=0;j<s;j++) if(mask>>j&1) y*=X[j],d*=-1;
                B[i]+=(i/(2*y))*d;
            }
        }
    }

    int res=0;
    for(int g=1;g<=N;g++) for(int n=g;n<=N;n+=g){
        int a=A[n/g],b=B[n/g];a-=b;
        res=(res+pw[n+1-g]*a+pw[n-g]*b)%mod;
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
