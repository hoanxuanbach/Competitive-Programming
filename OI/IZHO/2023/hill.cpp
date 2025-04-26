#include<bits/stdc++.h>
using namespace std;
const int maxn=2505;
const int inf=1e9;
int n,m,num[maxn],len[maxn],lt[maxn],rt[maxn];
int s[maxn][maxn],sum[maxn][maxn];
int query(int x,int y,int u,int v){
    return sum[u][v]-sum[x-1][v]-sum[u][y-1]+sum[x-1][y-1];
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            char c;cin >> c;
            if(c=='X') s[i][j]=-1;
            else s[i][j]=c-'0';
            sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+s[i][j];
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(s[i][j]==-1) len[j]=0;
            else len[j]++;
        }
        vector<int> v;
        for(int j=1;j<=m;j++){
            while(!v.empty() && len[v.back()]>=len[j]) v.pop_back();
            int cur=(v.empty()?0:v.back());
            lt[j]=lt[cur]+query(i-len[j]+1,cur+1,i,j);
            v.push_back(j);
        }
        v.clear();
        for(int j=m;j>=1;j--){
            while(!v.empty() && len[v.back()]>=len[j]) v.pop_back();
            int cur=(v.empty()?m+1:v.back());
            rt[j]=rt[cur]+query(i-len[j]+1,j,i,cur-1);
            v.push_back(j);
        }
        for(int j=1;j<=m;j++) ans=max(ans,rt[j]+lt[j]-query(i-len[j]+1,j,i,j));
    }
    cout << ans << '\n';
}
