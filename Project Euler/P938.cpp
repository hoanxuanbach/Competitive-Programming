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

#define ld long double
void solve(){
    int N=12345,M=12345;

    vector<ld> P(N+1,0);
    for(int i=1;i<=M;i++){
        vector<ld> Q(N+1,0);
        Q[0]=1;
        for(int j=1;j<=N;j++){
            ld T=(i+2*j)*(i+2*j-1);
            ld A = (ld)2*j*(2*j-1)/T;
            Q[j]+=Q[j-1]*A;
            ld B = (ld)4*j*i/T;
            Q[j]+=P[j]*B;
            Q[j]/=(A+B);
        }
        swap(P,Q);
    }

    cout << setprecision(10) << P[N] << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
