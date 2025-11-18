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
    vector<int> A(N+1),B(N+1);
    for(int i=1;i<=N;i++) A[i]=i/2+A[i/2];
    for(int i=1;i<=N;i++) B[i]=i/5+B[i/5];

    int res=0;
    for(int x=0;x<=N;x++){
        if(x%100==0){
            cout << x << endl;
        }
        for(int y=0;x+y<=N;y++){
            int z=N-x-y;
            int a=A[N]-A[x]-A[y]-A[z];
            int b=B[N]-B[x]-B[y]-B[z];
            if(min(a,b)>=12) res++;
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
