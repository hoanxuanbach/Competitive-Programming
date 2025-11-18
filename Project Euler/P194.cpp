#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 1e8;
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
    vector<pii> P={{0,5},{0,1},{1,6},{5,6},{0,2},{5,2},{1,4},{6,4},{2,3},{3,4}};

    vector<vector<int>> d(2,vector<int>(8,0));

    vector<int> f(7,-1);
    f[0]=0;f[1]=1;
    auto check = [&](int x){
        for(int i=x;i<(int)P.size();i++){
            auto [a,b]=P[i];
            if(f[a]==f[b]) return 0;
        }
        return 1;
    };
    function<void(int,int)> dfs = [&](int i,int x){
        if(i==7){
            d[0][x]+=check(0);
            d[1][x]+=check(1);
            return;
        }
        for(int j=0;j<=x;j++){
            f[i]=j;
            dfs(i+1,max(x,j+1));
        }
    };
    dfs(2,2);

    int A,B,C;cin >> A >> B >> C;
    int res=C*(C-1)%mod;

    int sA=0,sB=0;
    for(int x=0;x<=5;x++){
        int da=d[0][x+2],db=d[1][x+2];
        for(int i=1;i<=x;i++) da=da*(C-i-1)%mod,db=db*(C-i-1)%mod;
        sA=(sA+da)%mod;
        sB=(sB+db)%mod;
    }
    for(int i=0;i<A;i++) res=res*sA%mod;
    for(int i=0;i<B;i++) res=res*sB%mod;

    __int128 mul=1;
    for(int i=0;i<A;i++){
        mul*=(A+B-i);
        mul/=(i+1);
    }
    
    mul%=mod;
    res=res*mul%mod;
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
