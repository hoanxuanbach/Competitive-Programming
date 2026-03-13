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

const int N=2005;
int A[N][N],B[N][N],C[N][N];

void solve(){
    int n;cin >> n;
    for(int i=0;i<=2*n;i++) for(int j=0;j<=2*n;j++) A[i][j]=B[i][j]=C[i][j]=N;

    int res=0;
    for(int x=0;x<=n;x++) for(int y=x;y<=n;y++) for(int z=y;z<=n;z++){
        if(C[y-x][z-y]<x) continue;
        if(A[x][y]<z || A[y][z]<x || A[x][z]<y) continue;
        if(B[x][z-y]<y || B[y][z-x]<x || B[z][y-x]<x) continue;
        C[y-x][z-y]=x;
        A[x][y]=z;
        A[y][z]=x;
        A[x][z]=y;
        B[x][z-y]=y;
        B[y][z-x]=x;
        B[z][y-x]=x;
        cout << x << ' ' << y << ' ' << z << endl;
        res+=x+y+z;
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
