#include<bits/stdc++.h>
using namespace std;
#define int long long
#define maxn 200005
const int inf=1e18;
int n,k,dp[maxn][15][15],a[maxn],b[maxn];
bool check[maxn][15][15];
int solve(int i,int p,int q){
    if(i==2*n+1) return 0;
    if(check[i][p][q]) return dp[i][p][q];
    check[i][p][q]=1;
    int res=0;
    if(i%2==1){
        res=-inf;
        int pp=i/2-q+p+1;
        res=max(res,solve(i+1,p,q));
        if(pp<=n && p<k) res=max(res,solve(i+1,p+1,q)+a[pp]);
    }
    else{
        res=inf;
        int pp=(i+1)/2-p+q+1;
        res=min(res,solve(i+1,p,q));
        if(pp<=n && q<k) res=min(res,solve(i+1,p,q+1)-b[pp]);
    }

    return dp[i][p][q]=res;
}
signed main(){
    //freopen("bai3.inp","r",stdin);
    //freopen("bai3.out","w",stdout);
    ios_base::sync_with_stdio(0);cin.tie(0);
    cin >> n >> k;
    for(int i=1;i<=n;i++) cin >> a[i];
    for(int i=1;i<=n;i++) cin >> b[i];
    sort(a+1,a+n+1,greater<int>());
    sort(b+1,b+n+1,greater<int>());
    cout << solve(1,0,0);
}