#include<bits/stdc++.h>
using namespace std;
#define maxn 100005
#define int long long
#define pii pair<int,int>
int n,c[maxn],num[maxn],ans[maxn],res,child[maxn],son[maxn],f[maxn],cnt[maxn];
vector<pii> edge[maxn];
void pre_dfs(int u,int par){
    child[u]=1;
    for(pii v:edge[u]){
        if(v.first==par) continue;
        pre_dfs(v.first,u);
        if(child[v.first]>child[son[u]]){son[u]=v.first;f[u]=v.second;}
        child[u]+=child[v.first];
    }
}
void cal(int u,int par){
    res+=cnt[c[u]]-2*num[c[u]]-1;num[c[u]]++;
    for(pii v:edge[u]){
        if(v.first==par) continue;
        cal(v.first,u);
    }
}
void del(int u,int par){
    num[c[u]]=0;
    for(pii v:edge[u]){
        if(v.first==par) continue;
        del(v.first,u);
    }
}
void dfs(int u,int par,int t,int id){
    for(pii v:edge[u]){
        if(v.first==par || v.first==son[u]) continue;
        dfs(v.first,u,1,v.second);
    }
    if(son[u]!=0) dfs(son[u],u,0,f[u]);
    for(pii v:edge[u]){
        if(v.first==par || v.first==son[u]) continue;
        cal(v.first,u);
    }
    res+=cnt[c[u]]-2*num[c[u]]-1;num[c[u]]++;
    ans[id]=res;
    if(t){res=0;del(u,par);}
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n;
    for(int i=1;i<=n;i++){cin >> c[i];cnt[c[i]]++;}
    for(int i=1;i<n;i++){
        int u,v;cin >> u >> v;
        edge[u].push_back({v,i});
        edge[v].push_back({u,i});
    }
    pre_dfs(1,0);
    dfs(1,0,0,0);
    for(int i=1;i<n;i++) cout << ans[i] << ' ';
}
