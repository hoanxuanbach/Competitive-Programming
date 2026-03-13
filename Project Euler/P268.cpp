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
    vector<int> P;

    int M=100;
    vector<int> p(M);
    for(int i=2;i<M;i++) if(!p[i]){
        P.push_back(i);
        for(int j=i;j<M;j+=i) p[j]=i;
    }

    int N;cin >> N;

    __int128 res=0;
    function<void(int,int,int)> dfs = [&](int i,int x,int k){ 
        if(i==(int)P.size()){
            if(k>=4){
                __int128 val=(__int128)(N/x)*(k-1)*(k-2)*(k-3)/6;
                if(k&1) res-=val;
                else res+=val;
            }
            return;
        }
        dfs(i+1,x,k);
        if(x*P[i]<=N) dfs(i+1,x*P[i],k+1);
    };
    dfs(0,1,0);
    cout << (int)res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
