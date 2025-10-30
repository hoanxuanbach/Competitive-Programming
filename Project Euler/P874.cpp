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
    int n;cin >> n;

    int N=1000000;
    vector<int> p(N),X;
    for(int i=2;i<N;i++) if(!p[i]){
        X.push_back(i);
        for(int j=i*i;j<N;j+=i) p[j]=1;
    }

    int m=X[n],T=min(m,2000LL),D=min(n,100LL);
    
    vector<int> d(n,-inf);
    d[((m-T)*(n-1))%n]=(m-T)*X[n-1];
    while(T--){
        cout << T << endl;
        vector<int> nd(n,-inf);
        for(int i=0;i<n;i++) for(int j=n-1;j>=n-D;j--) nd[(i+j)%n]=max(nd[(i+j)%n],d[i]+X[j]);
        swap(d,nd);
    }
    cout << d[0] << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
