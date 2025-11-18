#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = (1<<20);
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
    vector<vector<int>> a(N+1,vector<int>(N+1,0)),d(N+1,vector<int>(N+1,0));
    int T=0;
    for(int i=1;i<=N;i++){
        for(int j=1;j<=i;j++){
            T=(615949*T+797807)%mod;
            a[i][j]=d[i][j]=T-(mod/2);
            a[i][j]+=a[i][j-1];
        }
        for(int j=1;j<=i;j++) a[i][j]+=a[i-1][j-1];
        for(int j=1;j<=N;j++) d[i][j]+=d[i-1][j]+d[i][j-1]-d[i-1][j-1];
    }

    int res=inf;
    for(int i=1;i<=N;i++) for(int j=1;j<=i;j++){
        for(int k=1;k<=min(i,j);k++){
            int val=a[i][j]-a[i-k][j-k]-(d[i][j-k]-d[i-k][j-k]);
            res=min(res,val);
        }
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
