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
    int n;cin >> n;
    vector<vector<int>> A(n+1,vector<int>(n+1,0));
    for(int i=1;i<=n;i++) for(int j=i;j<=n;j++){
        cin >> A[i][j];
        A[j][i]=A[i][j];
    }

    vector<int> d(n+1);
    vector<vector<bool>> f(n+1,vector<bool>(n+1,false));
    for(int x=1;x<=n;x++){
        for(int i=1;i<=n;i++){
            int u=A[1][x]^A[1][i]^A[x][i];
            f[x][u]=true;
        }
        for(int i=1;i<=n;i++) d[x]+=f[x][i];
    }
    for(int x=2;x<=n;x++){
        int v=-1;
        for(int i=1;i<=n;i++) if(f[x][i] && d[i]==d[x]-1) v=i;
        assert(v!=-1);
        cout << v << ' ' << x << '\n';
    }

}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
