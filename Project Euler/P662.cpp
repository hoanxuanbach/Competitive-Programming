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
    int n,m;cin >> n >> m;

    vector<pii> P;
    int S=sqrtl(n*n+m*m);
    
    int A=1,B=1;
    while(B<=S){
        for(int x=0;x*x<=(B*B)/2;x++){
            int y=B*B-x*x;
            int s=sqrtl(y);
            if(s*s==y) P.push_back({x,s});
        }
        swap(A,B),B+=A;
    }
    
    //cout << (int)P.size() << '\n';
    
    vector<vector<int>> f(n+1,vector<int>(m+1,0));f[0][0]=1;
    for(int i=0;i<=n;i++){
        if(i%100==0) cout << i << endl;
        for(int j=0;j<=m;j++){
            for(auto [x,y]:P){
                if(i>=x && j>=y) (f[i][j]+=f[i-x][j-y])%=mod;
                if(i>=y && j>=x) (f[i][j]+=f[i-y][j-x])%=mod;
            }
        }
    }
    cout << f[n][m] << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
