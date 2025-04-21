#include<bits/stdc++.h>
using namespace std;
#define maxn 100005
#define pii pair<int,int>
int mp[maxn];
int ans[maxn],sum[maxn],pos[maxn],n,m,k,s[maxn],son[maxn],res=0;
vector<int> add[maxn];
vector<pii> edge[maxn];
void dfs(int u,int par){
    sum[u]=(int)add[u].size()+1;
    for(pii v:edge[u]){
        if(v.first==par) continue;
        dfs(v.first,u);
        sum[u]+=sum[v.first];
        if(sum[v.first]>sum[son[u]]){son[u]=v.first;pos[u]=v.second;}
    }
}
void ad(int v){
    int x=mp[v];
    if(x==0) res++;
    if(x+1==s[v]) res--;
    mp[v]++;
}
void calc(int u,int par){
    for(int v:add[u]) ad(v);
    for(pii v:edge[u]){
        if(v.first==par) continue;
        calc(v.first,u);
    }
}
void del(int u,int par){
    for(int v:add[u]) mp[v]=0;
    for(pii v:edge[u]){
        if(v.first==par) continue;
        del(v.first,u);
    }
}
void dfs2(int u,int par,int era,int id){
    for(pii v:edge[u]){
        if(v.first==par || v.first==son[u]) continue;
        dfs2(v.first,u,1,v.second);
    }
    if(son[u]!=0) dfs2(son[u],u,0,pos[u]);
    for(pii v:edge[u]){
        if(v.first==par || v.first==son[u]) continue;
        calc(v.first,u);
    }
    for(int v:add[u]) ad(v);
    ans[id]=res;
    if(era){del(u,par);res=0;}
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> m >> k;
    for(int i=1;i<n;i++){
        int u,v;cin >> u >> v;
        edge[u].push_back({v,i});
        edge[v].push_back({u,i});
    }
    for(int i=1;i<=m;i++){
        cin >> s[i];
        for(int j=1;j<=s[i];j++){
            int a;cin >> a;
            add[a].push_back(i);
        }
    }
    dfs(1,0);dfs2(1,0,0,0);
    int num=0;
    for(int i=1;i<n;i++){
        if(ans[i]>=k) num++;
    }
    cout << num << '\n';
    for(int i=1;i<n;i++){
        if(ans[i]>=k) cout << i << ' ';
    }
}
