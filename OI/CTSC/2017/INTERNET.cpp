#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define pii pair<int,int>
#define fi first
#define se second
const ll inf=1e18;
const int maxn=100005;
int n,l,c[maxn];
pii par[maxn];
vector<pii> edge[maxn];
int ver[maxn],sz;
ll L[maxn],d[maxn],dep[maxn],ans;
void dfs(int u,int p){
    for(pii v:edge[u]){
        if(v.fi==p) continue;
        dep[v.fi]=dep[u]+v.se;
        par[v.fi]={u,v.se};
        dfs(v.fi,u);
    }
}
ll dfs2(int u,int p){
    ll Max=0;
    for(pii v:edge[u]){
        if(v.fi==p || c[v.fi]) continue;
        ll cur=v.se+dfs2(v.fi,u);
        ans=max(ans,Max+cur);Max=max(Max,cur);
    }
    return Max;
}
bool check(ll D){
    ll lm=-inf,ls=-inf,rm=-inf,rs=-inf,mm=-inf,ms=-inf;
    deque<int> dq;
    for(int i=0;i<sz;i++){
        while(!dq.empty() && L[i]+d[i]-L[dq.front()]+d[dq.front()]>D){
            ms=max(ms,L[dq.front()]+d[dq.front()]);
            mm=max(mm,d[dq.front()]-L[dq.front()]);
            dq.pop_front();
        }
        ll cur=d[i]+l-D;
        ls=max(ls,ms+L[i]+cur);
        lm=max(lm,ms-L[i]+cur);
        rm=max(rm,mm+L[i]+cur);
        rs=max(rs,mm-L[i]+cur);
        while(!dq.empty() && d[dq.back()]-L[dq.back()]<=d[i]-L[i]) dq.pop_back();
        dq.push_back(i);
    }
    rm=-rm;rs=-rs;
    int pls=sz,plm=-1,prs=sz-1,prm=0;
    for(int i=0;i<sz;i++){
        while(pls>0 && L[pls-1]+L[i]>=ls) pls--;
        while(plm<sz-1 && L[i]-L[plm+1]>=lm) plm++;
        while(L[prs]+L[i]>rs) prs--;
        while(prm<sz && L[i]-L[prm]>rm) prm++;
        if(max({pls,prm})<=min({plm,prs})) return true;
    }
    return false;
}
void solve(){
    sz=0;ans=0;
    for(int i=1;i<=n;i++){edge[i].clear();c[i]=0;}
    for(int i=1;i<n;i++){
        int u,v,w;cin >> u >> v >> w;
        edge[u].push_back({v,w});
        edge[v].push_back({u,w});
    }
    int x=0;dep[1]=0;dfs(1,0);
    for(int i=1;i<=n;i++){
        if(dep[i]>dep[x]) x=i;
    }
    int y=0;dep[x]=0;dfs(x,0);
    for(int i=1;i<=n;i++){
        if(dep[i]>dep[y]) y=i;
    }
    ll r=dep[y];
    c[y]=1;ver[sz++]=y;
    while(y!=x){
        L[sz]=par[y].se;y=par[y].fi;
        c[y]=1;ver[sz++]=y;
    }
    for(int i=0;i<sz;i++){
        d[i]=dfs2(ver[i],0);
        L[i]+=(i?L[i-1]:0);
        //cout << d[i] << ' ' << L[i] << ' ' << ver[i] << '\n';
    }
    ll l=ans,res=r;
    //cout << l << ' ' << r << '\n';
    while(r>=l){
        ll mid=(r+l)>>1;
        if(check(mid)){res=mid;r=mid-1;}
        else l=mid+1;
    }
    cout << res << '\n';
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    while(cin >> n >> l){
        if(n==0 && l==0) break;
        solve();
    }
}
