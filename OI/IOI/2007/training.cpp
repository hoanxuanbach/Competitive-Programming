#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e3+5;
const int maxm = 5e3+5;
const int inf = 1e9;

int n,m,w[maxm],d[maxn];
vector<int> edge[maxn],ss[maxn];
int cc[maxm],dp[maxn][maxm],f[maxn],val[maxm];

void pre_dfs(int u,int p){
    d[u]=d[p]^1;
    for(int v:edge[u]) if(v!=p) pre_dfs(v,u);
}

void dfs(int u,int p){
    for(int v:edge[u]){
        if(v==p) continue;
        dfs(v,u);
    }
    int cnt=0;
    for(int i=0;i<=m;i++) cc[i]=0;
    for(int id:ss[u]) cc[id]=u;
    vector<int> V;val[0]=0;
    for(int v:edge[u]){
        if(v==p) continue;
        vector<int> mx(cnt+1,-inf);
        for(int id:ss[v]){
            if(!cc[id]){cc[id]=v;continue;}
            if(cc[id]==u) mx[cnt]=max(mx[cnt],dp[v][id]+w[id]);
            else mx[f[cc[id]]]=max(mx[f[cc[id]]],dp[v][id]+dp[cc[id]][id]+w[id]);
            cc[id]=0;
        }
        for(int mask=(1<<cnt);mask<(1<<(cnt+1));mask++) val[mask]=0;
        for(int mask=0;mask<(1<<cnt);mask++){
            for(int i=0;i<=cnt;i++){
                int add=(1<<cnt)|(1<<i);
                if(mask&add) continue;
                int nmask=mask|add;
                val[nmask]=max(val[nmask],mx[i]+val[mask]);
            }
        }
        f[v]=cnt++;
        V.push_back(v);
    }
    for(int mask=0;mask<(1<<cnt);mask++){
        for(int i=0;i<cnt;i++){
            if(mask>>i&1) continue;
            val[mask|(1<<i)]=max(val[mask|(1<<i)],val[mask]+dp[V[i]][0]);
        }
    }
    ss[u].clear();
    for(int i=1;i<=m;i++) if(cc[i]){
        ss[u].push_back(i);
        if(cc[i]==u) dp[u][i]=val[(1<<cnt)-1];
        else{
            int t=f[cc[i]];
            dp[u][i]=val[((1<<cnt)-1)^(1<<t)]+dp[cc[i]][i];
        }
        //cout << "ss " << u << ' ' << i << '\n';
    }
    dp[u][0]=val[(1<<cnt)-1];
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> m;
    vector<pair<pair<int,int>,int>> e;
    int total=0;
    for(int i=1;i<=m;i++){
        int u,v;cin >> u >> v >> w[i];
        total+=w[i];
        if(w[i]) e.push_back({{u,v},i});
        else{
            edge[u].push_back(v);
            edge[v].push_back(u);
        }
    }
    pre_dfs(1,0);
    for(auto [x,id]:e) if(d[x.first]==d[x.second]){
        ss[x.first].push_back(id);
        ss[x.second].push_back(id);
        //cout << "edge " << x.first << ' ' << x.second << ' ' << id << '\n';
    }
    dfs(1,0);
    cout << total-dp[1][0] << '\n';
}
