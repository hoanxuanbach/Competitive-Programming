#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 1e9+7;
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
    int k;cin >> k;
    int A=1,B=1,C=1;
    for(int i=0;i<k;i++) A*=17,B*=19,C*=23;
    priority_queue<pii,vector<pii>,greater<pii>> pq;
    vector<int> f(A,inf);
    ;f[(B+C)%A]=A+B+C;
    pq.push({A+B+C,(B+C)%A});
    while(!pq.empty()){
        auto [d,x]=pq.top();pq.pop();
        if(f[x]!=d) continue;
        for(int w:{A,B,C}){
            int nx=(x+w)%A;
            if(f[nx]>f[x]+w) pq.push({f[nx]=f[x]+w,nx});
        }
    }
    int res=0;
    for(int i=0;i<A;i++){
        int k=(f[i]/A)%mod;
        (res+=i*k%mod+(k*(k-1)/2)%mod*A)%=mod;
        //cout << i << ' ' << f[i] << '\n';
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
