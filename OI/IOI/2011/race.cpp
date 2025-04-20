#include "race.h"
#include<bits/stdc++.h>
using namespace std;
#define maxn 200005
#define ll long long
#define pii pair<ll,ll>
ll n,k,son[maxn],lans,nans,d[maxn],dist[maxn];
vector<pii>  edge[maxn];
map<ll,pii> mp;
vector<ll> p;
ll pre_dfs(ll u,ll par){
    ll Max=0,cu=1;
    d[u]=d[par]+1;
    for(pii v:edge[u]){
        if(v.first==par) continue;
        dist[v.first]=dist[u]+v.second;
        ll cv=pre_dfs(v.first,u);
        if(cv>Max){Max=cv;son[u]=v.first;}
        cu+=cv;
    }
    return cu;
}
void add(ll u){
    if(mp.find(dist[u])==mp.end() || mp[dist[u]].first>d[u]) mp[dist[u]]={d[u],1};
    else if(mp[dist[u]].first==d[u]) mp[dist[u]].second++;
}
void update(ll l,ll u,ll anc){
    if(mp.find(l)!=mp.end()){
        if(lans>mp[l].first+d[u]-2*d[anc]){
            lans=mp[l].first+d[u]-2*d[anc];
            nans=mp[l].second;
        }
        else if(lans==mp[l].first+d[u]-2*d[anc]) nans+=mp[l].second;
    }
}
void cal(ll u,ll par,ll anc){
    p.push_back(u);
    update(k+2*dist[anc]-dist[u],u,anc);
    for(pii v:edge[u]){
        if(v.first==par) continue;
        cal(v.first,u,anc);
    }
}
void dfs(ll u,ll par,ll t){
    for(pii v:edge[u]){
        if(v.first!=son[u] && v.first!=par) dfs(v.first,u,1);
    }
    if(son[u]) dfs(son[u],u,0);
    //cout << u << " " << dist[u] << ' ' << par << ' ' << t << '\n';
    add(u);update(dist[u]+k,u,u);
    for(pii v:edge[u]){
        if(v.first==par || v.first==son[u]) continue;
        cal(v.first,u,u);
        for(ll x:p) add(x);
        p.clear();
    }
    //for(auto it:mp) cout << it.first << " " << it.second.first << " " << it.second.second << '\n';
    if(t) mp.clear();
}
int best_path(int N,int K,int H[][2],int L[]){
    n=N;k=K;
    for(ll i=0;i<n-1;i++){
        ll u=H[i][0],v=H[i][1],w=L[i];
        u++;v++;
        edge[u].push_back({v,w});
        edge[v].push_back({u,w});
    }
    lans=LLONG_MAX;
    pre_dfs(1,0);dfs(1,0,0);
    if(lans==LLONG_MAX) return -1;
    else return (int)lans;
}
