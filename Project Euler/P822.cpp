#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
int power(int a,int n,int mod){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}

const int mod = 1234567891;
const int maxn = 2e5+5;
const int inf = 1e18;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}

void solve(){
    int N,T;cin >> N >> T;
    
    int mx=N;
    priority_queue<int,vector<int>,greater<int>> pq;
    for(int i=2;i<=N;i++) pq.push(i);
    while(T && pq.top()*pq.top()<=mx){
        int x=pq.top();pq.pop();T--;
        pq.push(x*x);
    }
    vector<int> X;
    while(!pq.empty()) X.push_back(pq.top()),pq.pop();
    int k=T%(N-1),d=T/(N-1);
    d=power(2,d,mod-1);
    
    int res=0;
    for(int i=0;i<N-1;i++){
        int dd=d;
        if(i<k) dd=dd*2%(mod-1);
        res=(res+power(X[i],dd,mod))%mod;
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
