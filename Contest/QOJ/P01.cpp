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
    int n,m;cin >> n >> m;
    vector<vector<char>> c(n,vector<char>(m));
    for(int i=0;i<n;i++) for(int j=0;j<m;j++) cin >> c[i][j];

    int cnt=0;
    vector<vector<int>> f(n,vector<int>(m));
    if(c[0][0]=='.') f[0][0]=1;
    for(int i=0;i<n;i++) for(int j=0;j<m;j++){
        if(c[i][j]=='*') continue;
        cnt++;
        if(i) f[i][j]|=f[i-1][j];
        if(j) f[i][j]|=f[i][j-1];
    }
    if(!f[n-1][m-1]){
        cout << cnt*(cnt-1)/2 << '\n';
        return;
    }
    for(int i=n-1;i>=0;i--) for(int j=m-1;j>=0;j--){
        if(c[i][j]=='*' || !f[i][j]) continue;
        if(i!=n-1 || j!=m-1) f[i][j]=0;
        if(i+1<n) f[i][j]|=f[i+1][j];
        if(j+1<m) f[i][j]|=f[i][j+1];
    }
    vector<pii> A,B;

    int X=0,Y=0;
    A.push_back({0,0});
    while(X+1<n || Y+1<m){
        if(Y+1<m && f[X][Y+1]) Y++;
        else X++;
        A.push_back({X,Y});
    }

    X=0,Y=0;
    B.push_back({0,0});
    while(X+1<n || Y+1<m){
        if(X+1<n && f[X+1][Y]) X++;
        else Y++;
        B.push_back({X,Y});
    }

    int res=0,k=1;
    vector<vector<int>> d(n,vector<int>(m));
    for(auto [x,y]:B) d[x][y]=1;
    for(int r=1,l=0;r<n+m-1;r++){
        auto [U,V]=A[r];
        if(!d[U][V]) continue;
        tie(X,Y)=A[l];k++;
        for(int i=l+1;i<r;i++){
            auto [x,y]=A[i];
            y--;assert(x+1<n);
            while(y>=0 && (!f[x+1][y] || !f[x][y])) y--;

            int cx=x+1,cy=y;
            while(cx<U || cy<V){
                res+=d[cx][cy];
                if(cy<V && f[cx][cy+1]) cy++;
                else cx++;
            }
            
            cx=x,cy=y;
            while(cx>X || cy>Y){
                res+=d[cx][cy];
                if(cx>X && f[cx-1][cy]) cx--;
                else cy--;
            }
        }
        l=r;
    }
    res+=cnt*(cnt-1)/2-(cnt-k)*(cnt-k-1)/2;
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
