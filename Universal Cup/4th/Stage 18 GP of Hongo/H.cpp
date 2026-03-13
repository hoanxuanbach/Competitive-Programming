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
    if(N==1){
        cout << "No\n";
        return;
    }
    cout << "Yes\n";

    vector<vector<int>> a(3*N+1,vector<int>(3*N+1));
    for(int i=0;i<=6;i++) a[i][i]^=1,a[i][6-i]^=1;
    a[0][3]=a[3][0]=a[3][6]=a[6][3]=1;

    if(N>=3){
        for(int i=0;i<=9;i++) a[i][9-i%3]=1;
        for(int i=0;i<=2;i++) a[9-i][i]=1;
        a[7][4]=a[8][5]=a[9][3]=1;
    }

    for(int x=4;x<=N;x++){
        for(int i=0;i<=3*x;i++) a[i][3*x-i%3]=1;
        for(int i=0;i<=2;i++) a[3*x-i][i]=a[3*x-i][3+i]=1;
        a[3*x-2][7]=a[3*x-1][6]=1;
        for(int i=8;i<3*(x-1);i++) a[3*x-(i+1)%3][i]=1;
    }

    for(int i=0;i<=3*N;i++){
        for(int j=0;j<=3*N;j++) cout << (a[i][j]?'#':'.');
        cout << '\n';
    }
    
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}