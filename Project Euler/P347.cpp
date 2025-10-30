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
    vector<int> p(N+1,0),f(N+1);
    for(int i=2;i<=N;i++) if(!p[i]){
        for(int j=i;j<=N;j+=i) p[j]=i;
    }
    for(int i=2;i<=N;i++){
        int x=i;
        
        int a=p[x];
        while(x%a==0) x/=a;
        if(x==1) continue;
        int b=p[x];
        while(x%b==0) x/=b;
        if(x>1) continue;
        f[a*b]=max(f[a*b],i);
    }
    int T=0;
    for(int i=1;i<=N;i++) T+=f[i];
    cout << T << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
