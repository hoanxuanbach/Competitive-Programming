#include<bits/stdc++.h>
using namespace std;
const int maxn = 305;
const int inf = 1e9;
int n,k,x[maxn],p[maxn];
int dp[maxn][maxn],f[maxn][maxn];

int cost(int l,int r){
    int m=(l+r)>>1;
    return x[m]*(m-l+1)-(p[m]-p[l-1])+(p[r]-p[m])-(r-m)*x[m];
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> k;
    for(int i=1;i<=n;i++) cin >> x[i],p[i]=x[i]+p[i-1];
    for(int i=1;i<=k;i++) dp[0][i]=inf;
    for(int i=1;i<=n;i++){
        dp[i][0]=inf;
        for(int t=1;t<=k;t++){
            dp[i][t]=inf,f[i][t]=-1;
            for(int j=0;j<i;j++){
                int val=dp[j][t-1]+cost(j+1,i);
                if(val<dp[i][t]) dp[i][t]=val,f[i][t]=j;
            }
        }
    }
    int u=n;
    vector<int> res;
    for(int i=k;i>=1;i--){
        int v=f[u][i];
        res.push_back(x[(v+1+u)>>1]);
        u=v;
    }
    reverse(res.begin(),res.end());
    cout << dp[n][k] << '\n';
    for(int u:res) cout << u << ' ';
    cout << '\n';
}
