#include<bits/stdc++.h>
using namespace std;
#define maxn 600005
#define pii pair<int,int>
#define piii pair<pii,int>
#define fi first
#define se second
int n,k,low[maxn],num[maxn],a[maxn],scc[maxn],pos,cnt,sz,st[maxn];
piii p[maxn];
bool inq[maxn];
vector<int> edge[maxn];
void dfs(int u){
    low[u]=num[u]=++pos;
    inq[u]=true;st[++sz]=u;
    for(int v:edge[u]){
        if(!num[v]){
            dfs(v);
            low[u]=min(low[u],low[v]);
        }
        else if(inq[v]) low[u]=min(low[u],num[v]);
    }
    if(low[u]==num[u]){
        int v;cnt++;
        do{
            v=st[sz--];
            inq[v]=false;scc[v]=cnt;
        }while(v!=u);
    }
}
void solve(){
    cin >> n >> k;pos=sz=cnt=0;
    for(int i=1;i<=4*n;i++){edge[i].clear();low[i]=num[i]=scc[i]=0;inq[i]=false;}
    for(int i=1;i<=n;i++) cin >> a[i];
    for(int i=1;i<n;i++){p[i].fi.fi=a[i];p[i].fi.se=a[i+1];p[i].se=i;}
    sort(p+1,p+n);
    for(int i=2;i<n-1;i++){edge[4*i-2].push_back(4*i-7);edge[4*i-2].push_back(4*i+1);}
    edge[2].push_back(5);edge[4*n-6].push_back(4*n-11);
    edge[2].push_back(1);edge[4*n-6].push_back(4*n-7);
    for(int i=2;i<n;i++){
        if(p[i].fi==p[i-1].fi){
            edge[4*p[i-1].se-3].push_back(4*p[i].se-1);
            edge[4*p[i].se-3].push_back(4*p[i-1].se);
            edge[4*p[i-1].se-1].push_back(4*p[i].se-1);
            edge[4*p[i].se].push_back(4*p[i-1].se);
        }
    }
    for(int i=1;i<n;i++){
        edge[4*i].push_back(4*i-2);
        edge[4*i-1].push_back(4*i-2);
    }
    for(int i=1;i<=4*n-4;i++){
        if(!num[i]) dfs(i);
    }
    bool check=true;
    for(int i=1;i<n;i++){
        if(scc[4*i-2]==scc[4*i-3]) check=false;
    }
    if(check) cout << "TAK\n";
    else cout << "NIE\n";
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int t;cin >> t;
    while(t--) solve();
}
