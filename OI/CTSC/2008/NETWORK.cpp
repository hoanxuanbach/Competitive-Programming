#include<bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
#define piii pair<int,pii>
#define fi first
#define se second
const int maxn=80005;
const int maxl=20;
const int maxs=405;
const int bl=400;
int n,q,a[maxn],L[maxn],R[maxn],len,sz,parent[maxn][maxl],dep[maxn];
vector<int> edge[maxn];
piii que[maxn];
vector<pii> com;
void dfs(int u,int par){
    L[u]=++len;parent[u][0]=par;
    dep[u]=dep[par]+1;
    for(int v:edge[u]){
        if(v==par) continue;
        dfs(v,u);
    }
    R[u]=len;
}
int lca(int u,int v){
    if(dep[u]>dep[v]) swap(u,v);
    for(int i=0;i<18;i++){
        if((dep[v]-dep[u])&(1<<i)) v=parent[v][i];
    }
    if(v==u) return u;
    for(int i=17;i>=0;i--){
        if(parent[u][i]!=parent[v][i]){
            u=parent[u][i];
            v=parent[v][i];
        }
    }
    return parent[u][0];
}
int c[2*maxn];
struct Block{
    int cnt[maxn],num[maxs];
    void update(int l,int r,int val){
        for(int i=l;i<=r;i++){
            if(i%bl==0 && i+bl-1<=r){num[i/bl]+=val;i+=bl-1;}
            else cnt[i]+=val;
        }
    }
    int query(int u){
        if(u==0) return 0;
        return cnt[L[u]]+num[L[u]/bl];
    }
}s[maxs];
int f(int u,int v){
    return (L[v]>=L[u] && L[v]<=R[u]);
}
int query(int k,int u,int v){
    int w=lca(u,v),p=parent[w][0],cur=-1;
    //cout << u << ' ' << v << ' ' << w << ' ' << p << '\n';
    for(int i=0;i<=(sz-1)/bl;i++){
        int add=s[i].query(u)+s[i].query(v)-s[i].query(w)-s[i].query(p);
        //cout << add << '\n';
        if(add<k) k-=add;
        else{cur=i;break;}
    }
    //cout << '*' << cur << '\n';
    if(cur==-1) return -1;
    for(int i=cur*bl;i<min(sz,(cur+1)*bl);i++){
        if(!c[i]) continue;
        int add=f(com[i].se,u)+f(com[i].se,v)-f(com[i].se,p)-f(com[i].se,w);
        if(k==add) return com[i].fi;
        else k-=add;
    }
    return -1;
}
void solve(){
    cin >> n >> q;
    for(int i=1;i<=n;i++){
        cin >> a[i];
        com.push_back({a[i],i});
    }
    for(int i=1;i<n;i++){
        int u,v;cin >> u >> v;
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    for(int i=1;i<=q;i++){
        cin >> que[i].fi >> que[i].se.fi >> que[i].se.se;
        if(que[i].fi==0) com.push_back({que[i].se.se,que[i].se.fi});
    }
    sort(com.begin(),com.end());
    com.erase(unique(com.begin(),com.end()),com.end());
    sz=(int)com.size();
    dfs(1,0);
    for(int i=1;i<18;i++){
        for(int j=1;j<=n;j++) parent[j][i]=parent[parent[j][i-1]][i-1];
    }
    for(int i=1;i<=n;i++){
        int pos=lower_bound(com.begin(),com.end(),make_pair(a[i],i))-com.begin();
        c[pos]=1;s[pos/bl].update(L[i],R[i],1);
    }
    //for(pii x:com) cout << x.fi << ' ' << x.se << '\n';
    for(int i=1;i<=q;i++){
        int x=que[i].se.fi,y=que[i].se.se;
        if(que[i].fi==0){
            int pos=lower_bound(com.begin(),com.end(),make_pair(a[x],x))-com.begin();
            c[pos]=0;s[pos/bl].update(L[x],R[x],-1);
            pos=lower_bound(com.begin(),com.end(),make_pair(y,x))-com.begin();
            c[pos]=1;s[pos/bl].update(L[x],R[x],1);a[x]=y;
        }
        else{
            int res=query(que[i].fi,x,y);
            if(res==-1) cout << "invalid request!" << '\n';
            else cout << res << '\n';
        }
    }
}
signed main(){
    freopen("4.in","r",stdin);
    freopen("out.txt","w",stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
