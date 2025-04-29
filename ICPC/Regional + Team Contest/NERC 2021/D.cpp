#include<bits/stdc++.h>
using namespace std;
#define maxn 100005
#define maxd 15
int n,d,a[maxn],trace[maxn][maxd];
long double dp[maxn][maxd];
bool check[maxn][maxd];
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> d;
    for(int i=1;i<=n;i++) cin >> a[i];
    for(int i=1;i<=n;i++){
        for(int j=0;j<=9;j++) trace[i][j]=-1;
        for(int j=0;j<=9;j++){
            check[i][j]=check[i-1][j];
            dp[i][j]=dp[i-1][j];
        }
        if(log2(a[i])>dp[i][a[i]%10]){
            dp[i][a[i]%10]=log2(a[i]);
            trace[i][a[i]%10]=-2;
            check[i][a[i]%10]=true;
        }
        for(int j=0;j<=9;j++){
            if(!check[i-1][j]) continue;
            int ne=(j*a[i])%10;
            if(dp[i-1][j]+log2(a[i])>dp[i][ne]){
                dp[i][ne]=dp[i-1][j]+log2(a[i]);
                check[i][ne]=true;trace[i][ne]=j;
            }
        }
        //for(int j=0;j<=9;j++) cout << trace[i][j] << ' ';
        //cout << '\n';
    }
    if(!check[n][d]) cout << -1 << '\n';
    else{
        int x=d;
        vector<int> ans;
        for(int i=n;i>=1;i--){
            if(x==-2) break;
            if(trace[i][x]!=-1){ans.push_back(a[i]);x=trace[i][x];}
        }
        sort(ans.begin(),ans.end());
        cout << (int)ans.size() << '\n';
        for(int v:ans) cout << v << ' ';
    }
}
