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
    int n,m,u,r,d,l;cin >> n >> m >> u >> r >> d >> l;
    if(u<n-1 || r<m-1){
        cout << "impossible\n";
        return;
    }
    u-=(n-1);r-=(m-1);

    vector<vector<char>> c(n,vector<char>(m,'*'));
    int x=0,y=m-1;
    while(x<n-1 || y){
        if(d+r>=y){
            for(int i=0;i<y;i++){
                if(d) c[x][i]='D',d--;
                else c[x][i]='R',r--;
            }
            x++;
            c[x][y]='U';
        }
        else{
            for(int i=x+1;i<n;i++){
                if(l) c[i][y]='L',l--;
                else c[i][y]='U',u--;
            }
            y--;
            c[x][y]='R';
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++) cout << c[i][j];
        cout << '\n';
    }
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--){
        solve();
        if(test) cout << '\n';
    }
}
