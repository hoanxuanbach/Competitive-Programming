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

#define A array<int,5>

void solve(){
    vector<int> X;
    int N=100,K;cin >> K;

    vector<int> p(N);
    for(int i=2;i<N;i++) if(!p[i]){
        X.push_back(i);
        for(int j=i;j<N;j+=i) p[j]=1;
    }

    priority_queue<A,vector<A>,greater<A>> pq;
    pq.push({1,1,0,0,inf});
    while(!pq.empty()){
        auto [x,d,i,k,lst]=pq.top();pq.pop();
        if((d+1)/2>=K){
            cout << x << '\n';
            return;
        }
        if(k<lst) pq.push({x*X[i],d/(2*k+1)*(2*k+3),i,k+1,lst});
        if(k) pq.push({x,d,i+1,0,k});
    }
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
