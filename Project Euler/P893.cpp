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

vector<int> S={6,2,5,5,4,5,6,3,7,6};

void solve(){
    int N;cin >> N;
    vector<int> f(N+1);
    for(int i=1;i<=N;i++){
        int d=i;
        while(d) f[i]+=S[d%10],d/=10;
    }

    for(int i=1;i<=N;i++) for(int j=i;j<=N;j+=i) f[j]=min(f[j],f[i]+f[j/i]+2);

    for(int i=1;i<=N;i++){
        cout << i << endl;
        for(int j=1;2*j<=i;j++) f[i]=min(f[i],f[j]+f[i-j]+2);
    }
    int res=0;
    for(int i=1;i<=N;i++) res+=f[i];
    cout << res << '\n';   
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
