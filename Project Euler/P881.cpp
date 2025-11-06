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
    int N=1000;
    vector<int> X;
    
    vector<int> p(N);
    for(int i=2;i<N;i++) if(!p[i]){
        X.push_back(i);
        for(int j=i;j<N;j+=i) p[j]=1;
    }

    priority_queue<pii,vector<pii>,greater<pii>> pq;
    pq.push({2,0});
    while(!pq.empty()){
        auto [n,x]=pq.top();pq.pop();
        int A=0,B=0,d=n;
        while(d%X[x]==0) d/=X[x],B++;
        if(x){
            while(d%X[x-1]==0) d/=X[x-1],A++;
        }
        else A=inf;
        if(B<A) pq.push({n*X[x],x});
        pq.push({n*X[x+1],x+1});

        d=n;
        int T=1;
        vector<int> c(x+1);
        for(int i=0;i<=x;i++){
            while(d%X[i]==0) d/=X[i],c[i]++;
            T+=c[i];
        }

        vector<int> f(T);f[0]=1;
        for(int i=0;i<=x;i++){
            for(int j=1;j<T;j++) f[j]+=f[j-1];
            for(int j=T-1;j>c[i];j--) f[j]-=f[j-c[i]-1];
        }
        int val=0;
        for(int i=0;i<T;i++) val=max(val,f[i]);
        if(val>=10000){
            cout << n << '\n';
            return;
        }
    }
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
