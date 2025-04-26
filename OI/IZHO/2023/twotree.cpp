#include<bits/stdc++.h>
using namespace std;
const int maxs=2005;
const int maxn=500005;
#define pii pair<int,int>
#define piii pair<pii,pii>
#define fi first
#define se second
int n,ans[maxn];
vector<int> edge[2][maxn];
vector<pii> ss[2][maxn];
namespace sub5{
    int child[2][maxn];
    vector<pii> p[maxn];
    int L[maxn],R[maxn],X[maxn],Y[maxn],bit[maxn],posl=0,posx=0,cn[maxn];
    vector<piii> cc[maxn];
    void dfs(int id,int u,int par){
        child[id][u]=1;
        for(int v:edge[id][u]){
            if(v==par) continue;
            dfs(id,v,u);child[id][u]+=child[id][v];
            ss[id][u].push_back({(n-child[id][v]),v});
        }
    }
    void dfs0(int u,int par){
        L[u]=++posl;cn[posl]=u;
        sort(ss[0][u].begin(),ss[0][u].end());
        for(pii v:ss[0][u]){
            if(v.se==par) continue;
            dfs0(v.se,u);
            cc[u].push_back({{v.fi,0},{L[v.se],R[v.se]}});
        }
        R[u]=posl;
    }
    void dfs1(int u,int par){
        X[u]=++posx;
        sort(ss[1][u].begin(),ss[1][u].end());
        for(pii v:ss[1][u]){
            if(v.se==par) continue;
            dfs1(v.se,u);
            cc[u].push_back({{v.fi,1},{X[v.se],Y[v.se]}});
        }
        Y[u]=posx;
        //cout << u << ' ' << L[u] << ' ' << R[u] << ' ' << X[u] << ' ' << Y[u] << '\n';
    }
     void add(int l,int r,int x,int y){
        if(l>r || x>y) return;
        //cout << l << ' ' << r << ' ' << x << ' ' << y  << '\n';
        p[l].push_back({x,y});
        p[r+1].push_back({-x,-y});
    }
    void build(){
        dfs(0,1,0);dfs(1,1,0);
        dfs0(1,0);dfs1(1,0);
        for(int i=1;i<=n;i++){
            sort(cc[i].begin(),cc[i].end());
            int cx=-1,cy=-1;
            for(piii v:cc[i]){
                if(v.fi.se==0){
                    if(v.fi.fi>(Y[i]-X[i]+1)){
                        add(v.se.fi,v.se.se,Y[i]+1,n);
                        add(v.se.fi,v.se.se,1,X[i]-1);
                    }
                    if(cx!=-1 && cy!=-1) add(v.se.fi,v.se.se,cx,cy);
                }
                else{
                    if((R[i]-L[i]+1)>v.fi.fi){
                        add(R[i]+1,n,v.se.fi,v.se.se);
                        add(1,L[i]-1,v.se.fi,v.se.se);
                    }
                    if(cx==-1) cx=v.se.fi;
                    cy=v.se.se;
                }
            }
            if((R[i]-L[i]+1)>(Y[i]-X[i]+1)){
                add(R[i]+1,n,Y[i]+1,n);
                add(R[i]+1,n,1,X[i]-1);
                add(1,L[i]-1,Y[i]+1,n);
                add(1,L[i]-1,1,X[i]-1);
            }
        }
    }
    void update(int x,int val){
        for(int i=x;i<=n;i+=(i&(-i))) bit[i]+=val;
    }
    void update_range(int l,int r,int val){
        update(l,val);update(r+1,-val);
    }
    int query(int x){
        int res=0;
        for(int i=x;i>=1;i-=(i&(-i))) res+=bit[i];
        return res;
    }
    void solve(){
        build();
        for(int i=1;i<=n;i++){
            for(pii x:p[i]) update_range(abs(x.first),abs(x.second),(x.first>0?1:-1));
            ans[cn[i]]=query(X[cn[i]]);
        }
    }
}
signed main(){
    //freopen("INPUT.INP","r",stdin);
    //freopen("TWOTREE.OUT","w",stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n;
    for(int i=1;i<n;i++){
        int u,v;cin >> u >> v;
        edge[0][u].push_back(v);
        edge[0][v].push_back(u);
    }
    for(int i=1;i<n;i++){
        int u,v;cin >> u >> v;
        edge[1][u].push_back(v);
        edge[1][v].push_back(u);
    }
    sub5::solve();
    for(int i=1;i<=n;i++) cout << ans[i] << ' ';
    cout << '\n';
}
