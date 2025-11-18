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

    vector<bool> f(N+1);
    vector<set<int>> S(N+1);
    for(int i=1;i<=N;i++){
        for(int j=1;j<i;j++){
            int d=i*i+j*j+i*j;
            if(d>N*N) break;
            int x=sqrtl(d);
            if(x*x==d) S[i].insert(j);
        }
        if(i%100==0){
            cout << i/100 << endl;
        }
    }
    for(int i=1;i<=N;i++) for(int j:S[i]) for(int k:S[j]){
        if(i+j+k>N) break;
        if(S[i].count(k)) f[i+j+k]=true;
    }
    int res=0;
    for(int i=1;i<=N;i++) res+=f[i]*i;
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
