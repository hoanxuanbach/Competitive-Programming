#include<bits/stdc++.h>
using namespace std;
#define ld long double
const int maxn=105;
int n,m;
ld g[maxn][maxn],p[maxn][maxn];
void print(){
    for(int i=0;i<n;i++){
        for(int j=0;j<=n;j++){
            cout << g[i][j] << ' ';
        }
        cout << '\n';
    }
    cout << '\n';
}
void Gauss_elimination(){
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            ld d=g[j][i]/g[i][i];
            for(int k=i;k<=n;k++) g[j][k]-=d*g[i][k];
        }
        //print();
    }
    for(int i=n-1;i>=0;i--){
        g[i][n]/=g[i][i];
        for(int j=i-1;j>=0;j--) g[j][n]-=g[j][i]*g[i][n];
    }
}
void solve(){
    cin >> n >> m;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++) cin >> p[i][j];
    }
    for(int i=0;i<=n;i++) g[0][i]=1;
    for(int i=1;i<n;i++){
        g[i][i]=-1;
        for(int j=0;j<n;j++){
            if(i==j) continue;
            g[i][i]+=p[i][j]/(n-1);
            g[i][j]+=p[i][j]/(n-1);
        }
    }
    //print();
    Gauss_elimination();
    for(int i=1;i<=m;i++){
        string s;cin >> s;
        ld ans=0;
        for(int j=0;j<n;j++){
            if(s[j]=='1') ans+=g[j][n];
        }
        cout << setprecision(8) << fixed << ans << '\n';
    }
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
