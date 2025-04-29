#include<bits/stdc++.h>
using namespace std;
#define maxn 200005
int n,child[maxn],sz;
bool used[maxn];
vector<int> edge[maxn];
void dfs(int u,int par){
    child[u]=1;
    for(int v:edge[u]){
        if(v==par ||used[v]) continue;
        dfs(v,u);child[u]+=child[v];
    }
}
int findcen(int u,int par){
    for(int v:edge[u]){
        if(v==par ||used[v]) continue;
        if(child[v]>sz/2) return findcen(v,u);
    }
    return u;
}
int check(){
    int cnt=0,a=-1,b=-1;
    for(int i=1;i<=n;i++){
        if(used[i]) continue;
        if(a==-1) a=i;
        else b=i;
        cnt++;
    }
    if(cnt==1) return a;
    else if(cnt==2){
        cout << "? 1 " << a << ' ' << b << endl;
        int t;cin >> t;
        return t*a+(t^1)*b;
    }
    return -1;
}
void add(int u,int par,vector<int> &x){
    x.push_back(u);
    for(int v:edge[u]){
        if(v==par || used[v]) continue;
        add(v,u,x);
    }
}
int decompose(int u){
    int res=check();
    if(res!=-1) return res;
    dfs(u,0);sz=child[u];
    int cen=findcen(u,0);dfs(cen,0);
    //cout << cen << ' ' << sz << '\n';
    vector<int> x,y;
    for(int v:edge[cen]){
        if(used[v]) continue;
        //cout << child[v] << ' ';
        if((int)x.size()*4>=sz) add(v,cen,y);
        else add(v,cen,x);
    }
    //cout << '\n';
    cout << "? " << (int)x.size() << ' ' << cen << ' ';
    for(int v:x) cout << v << ' ';
    cout << endl;
    int t;cin >> t;
    if(t==1){for(int v:x) used[v]=true;}
    else{for(int v:y) used[v]=true;}
    return decompose(cen);
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n;
    for(int i=1;i<n;i++){
        int u,v;cin >> u >> v;
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    int ans=decompose(1);
    cout << "! " << ans << endl;
}
