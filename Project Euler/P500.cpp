#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 500500507;
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
    int N=10000000;
    vector<int> X;

    vector<int> p(N,1);
    p[0]=p[1]=0;
    for(int i=2;i<N;i++){
        if(p[i]){
            X.push_back(i);
            for(int j=i*i;j<N;j+=i) p[j]=0;
        }
    }

    cout << (int)X.size() << '\n';
    vector<int> f(5);

    int res=1,n=500500;
    while(n--){
        pii A={inf,-1};
        for(int i=0;i<=4;i++){
            int x=X[f[i]];
            int val=1;
            for(int j=0;j<(1<<i);j++) val*=x;
            A=min(A,{val,i});
        }
        f[A.second]++;
        res=res*A.first%mod;
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
