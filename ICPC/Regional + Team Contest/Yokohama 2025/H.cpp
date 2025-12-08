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

const int inf = 1e18;
const int maxn = 2e5+5;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}


void solve(){
    int n,m,k;cin >> n >> m >> k;
    vector<vector<char>> c(n,vector<char>(m));
    for(int i=0;i<n;i++) for(int j=0;j<m;j++) cin >> c[i][j];
    
    for(int i=0;i<n;i++) for(int j=0;j<m;j++) if(c[i][j]=='#'){
        if(i+k>n || j+k>m){
            cout << "no\n";
            return;
        }
        int A=1,B=1,C=1,D=1;
        for(int x=0;x<k;x++) if(c[i+x][j]=='.') A=false;
        for(int x=0;x<k;x++) if(c[i][j+x]=='.') B=false;
        for(int x=0;x<k;x++) if(c[i+k-1][j+x]=='.') C=false;
        for(int x=0;x<k;x++) if(c[i+x][j+k-1]=='.') D=false;
        if(A+B+C+D!=3){
            cout << "no\n";
            return;
        }
        if(A) for(int x=0;x<k;x++) c[i+x][j]='.';
        if(B) for(int x=0;x<k;x++) c[i][j+x]='.';
        if(C) for(int x=0;x<k;x++) c[i+k-1][j+x]='.';
        if(D) for(int x=0;x<k;x++) c[i+x][j+k-1]='.';
    }
    cout << "yes\n";
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}


