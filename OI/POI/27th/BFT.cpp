#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int,int>
#define maxn 200005
struct ed{
    int u,v,w,a;
    bool operator<(ed o){return w<o.w;}
};
vector<ed> e;
int ans[maxn],n,q,par[2][maxn],res[2],r[2][maxn];
vector<pii> p;
int findpar(int t,int u){
    if(u!=par[t][u]) return par[t][u]=findpar(t,par[t][u]);
    return u;
}
void unions(int t,int u,int v){
    u=findpar(t,u);v=findpar(t,v);
    if(u==v) return;
    res[t]-=(r[t][u]*(r[t][u]-1))/2+(r[t][v]*(r[t][v]-1))/2;
    par[t][v]=u;r[t][u]+=r[t][v];
    res[t]+=r[t][u]*(r[t][u]-1)/2;
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> q;
    for(int i=1;i<=n;i++){par[0][i]=par[1][i]=i;r[0][i]=r[1][i]=1;}
    for(int i=1;i<n;i++){
        int u,v,w,a;cin >> u >> v >> w >> a;
        e.push_back({u,v,w,a});
    }
    for(int i=1;i<=q;i++){
        int x;cin >> x;
        p.push_back({x,i});
    }
    sort(p.begin(),p.end(),greater<pii>());
    sort(e.begin(),e.end());
    for(pii x:p){
        while(!e.empty() && e.back().w>=x.first){
            unions(0,e.back().u,e.back().v);
            if(e.back().a==0) unions(1,e.back().u,e.back().v);
            e.pop_back();
        }
        ans[x.second]=res[0]-res[1];
    }
    for(int i=1;i<=q;i++) cout << ans[i] << '\n';
}
