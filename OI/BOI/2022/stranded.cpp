#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int,int>
#define fi first
#define se second
const int maxn = 2e5+5;
int n,m,s[2*maxn];

int sz;
vector<int> com;
vector<pii> e[maxn];

int par[2*maxn],d[2*maxn],pp[2*maxn],T;

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> m;
    for(int i=1;i<=n;i++){cin >> s[i];com.push_back(s[i]);}
    sort(com.begin(),com.end());
    com.erase(unique(com.begin(),com.end()),com.end());
    sz=(int)com.size();
    for(int i=1;i<=m;i++){
        int u,v;cin >> u >> v;
        int x=max(s[u],s[v]);
        x=lower_bound(com.begin(),com.end(),x)-com.begin();
        e[x].push_back({u,v});
    }
    set<pii> ss;T=n;
    for(int i=1;i<=n;i++) pp[i]=i,par[i]=i,ss.insert({s[i],i});
    function<int(int)> findpar = [&](int u){
        if(u!=par[u]) return par[u]=findpar(par[u]);
        return u;
    };
    auto unions = [&](int u,int v){
        u=findpar(u),v=findpar(v);
        if(u==v) return;
        pp[u]=pp[v]=par[u]=par[v]=++T;
        par[T]=pp[T]=T;
        s[T]=s[u]+s[v];
        ss.erase({s[u],u});
        ss.erase({s[v],v});
        ss.insert({s[T],T});
    };
    for(int i=0;i<sz;i++){
        while(!ss.empty() && ss.begin()->fi<com[i]){
            d[ss.begin()->se]=1;
            ss.erase(ss.begin());
        }
        for(auto [u,v]:e[i]) unions(u,v);
    }
    for(int i=T;i>=1;i--) d[i]|=d[pp[i]];
    for(int i=1;i<=n;i++) cout << (d[i]^1);
}
