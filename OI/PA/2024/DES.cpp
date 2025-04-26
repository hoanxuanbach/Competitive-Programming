#include<bits/stdc++.h>
using namespace std;
const int maxn = 1005;

int n,m;
int ans[maxn],a[maxn],b[maxn];

void update(vector<int> c){
    int mx=n-1;
    while(mx>=0 && c[mx]!=1) mx--;
    for(int i=0;i<n;i++){
        for(int j=i;j<n;j++){
            if(c[j]==0) break;
            if(j<mx) continue;
            ans[j-i+1]^=1;
        }
        if(c[i]==1) break;
    }
}

void dfs(vector<int> c,int x){
    while(x<m){
        int u=a[x],v=b[x];
        if(c[u]==-1 && c[v]==-1) break;
        else if(c[u]==-1){
            if(c[v]==0) swap(c[u],c[v]);
        }
        else if(c[v]==-1){
            if(c[u]==1) swap(c[u],c[v]);
        }
        else if(c[u]) swap(c[u],c[v]);
        x++;
    }
    if(x==m) return update(c);
    int u=a[x],v=b[x];
    c[u]=c[v]=0;
    dfs(c,x);
    c[u]=c[v]=1;
    dfs(c,x);
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> m;
    for(int i=0;i<m;i++) cin >> a[i] >> b[i],a[i]--,b[i]--;
    vector<int> c(n,-1);
    dfs(c,0);
    for(int i=1;i<=n;i++) cout << ans[i] << ' ';
    cout << '\n';
}
