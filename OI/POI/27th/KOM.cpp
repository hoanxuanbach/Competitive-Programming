#include<bits/stdc++.h>
using namespace std;
#define maxn 1000005
const int inf=1e9;
vector<int> edge[maxn],ver[maxn],ss[maxn];
int num[maxn],a[maxn],n,p[maxn],dp[maxn],pos[maxn],trace[maxn];
void dfs(int u){
    if(edge[u].empty()){
        for(int x:ver[u]) cout << x << ' ';
        return;
    }
    for(int v:edge[u]) dfs(v);
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n;
    for(int i=1;i<=n;i++) cin >> a[i];
    sort(a+1,a+n+1);
    if(a[1]==0){
        cout << 1 << '\n' << 0 << '\n';
        return 0;
    }
    for(int i=1;i<=n;i++){
        num[a[i]]++;
        if(a[i]==a[i-1]) p[i]=p[i-1]+1;
        else p[i]=1;
    }
    int cnt=0,cc=n;
    for(int i=1;i<=n;i++){
        dp[i]=inf;
        for(int j=0;j<=18;j++){
            if(p[i]>=(1<<j)){
                if(dp[i-(1<<j)]+1<dp[i]){
                    trace[i]=a[i]-j;
                    dp[i]=dp[i-(1<<j)]+1;
                    pos[i]=i-(1<<j);
                }
            }
            else if(p[i]%2==0 && p[i]+num[a[i]-1]*2>=(1<<j)){
                int pp=i-p[i]/2-(1<<(j-1));
                if(dp[pp]+1<dp[i]){
                    trace[i]=a[i]-j;
                    dp[i]=dp[pp]+1;
                    pos[i]=pp;
                }
            }
        }
    }
    while(cc){
        cnt++;
        ss[trace[cc]].push_back(cnt);
        for(int j=pos[cc]+1;j<=cc;j++) ver[cnt].push_back(a[j]);
        cc=pos[cc];
    }
    for(int i=n;i>=1;i--){
        for(int j=0;j<(int)ss[i].size();j+=2){
            cnt++;
            edge[cnt].push_back(ss[i][j+1]);
            edge[cnt].push_back(ss[i][j]);
            ss[i-1].push_back(cnt);
        }
    }
    cout << cnt << '\n';
    dfs(cnt);
}
