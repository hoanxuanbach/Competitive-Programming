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

    vector<int> p(N+1),f(N+1,-1),X;
    for(int i=2;i<=N;i++) if(!p[i]){
        f[i]=(int)X.size();X.push_back(i);
        for(int j=i;j<=N;j+=i) p[j]=i;
    }
    int S=(int)X.size();
    auto get = [&](int k){
        vector<int> d(S);
        for(int i=1;i<=k;i++){
            int x=i;
            while(x>1) d[f[p[x]]]++,x/=p[x];
        }
        return d;
    };
    vector<int> A=get(N),B=get(M),C=get(N-M);
    int res=0;
    for(int i=0;i<S;i++) res+=(A[i]-B[i]-C[i])*X[i];
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
