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
    
    int S=N/10000;
    vector<int> f(S),T;
    for(int i=2;i<S;i++) if(!f[i]){
        if(i%3==1) T.push_back(i);
        for(int j=i;j<S;j+=i) f[j]=i;
    }

    vector<int> p(S);
    for(int i=1;i<S;i++){
        int x=i;p[i]=i;
        while(x>1){
            int j=f[x];
            if(j%3!=2) p[i]=0;
            while(x%j==0) x/=j;
        }
        p[i]+=p[i-1];
    }

    int res=0,timer=0;
    function<void(int,int,int)> dfs = [&](int k,int x,int s){
        timer++;
        if(timer%100000==0) cout << timer << endl;
        if(k==0){
            res+=p[N/x]*x;
            return;
        }
        for(int i=s;i<=(int)T.size()-k;i++){
            int m=N;
            for(int j=1;j<k;j++) m/=T[i+j];
            if(m<x*T[i]) break;
            for(int nx=x*T[i];nx<=m;nx*=T[i]) dfs(k-1,nx,i+1);
        }
    };
    dfs(5,1,0);
    dfs(5,3,0);
    for(int k=9;k<=N;k*=3) dfs(4,k,0);
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
