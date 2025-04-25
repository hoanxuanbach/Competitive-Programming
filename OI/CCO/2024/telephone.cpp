#include<bits/stdc++.h>
using namespace std;
const int maxn = 5e5+5;
#define int long long

int sub,n,q;
int p[3*maxn],total,lst;

int vis[maxn],T;
int c[maxn],sz[2*maxn],cnt;
set<int> g[maxn];
set<int>::iterator ptr[maxn];

void add(int x,int y){
    if(sz[c[x]]>sz[c[y]]) swap(x,y);
    total+=sz[c[x]]*sz[c[y]];

    queue<int> q;
    q.push(x);vis[x]=++T;
    while(!q.empty()){
        int u=q.front();q.pop();
        c[u]=c[y];sz[c[y]]++;
        for(int v:g[u]) if(vis[v]!=T){q.push(v);vis[v]=T;}
    }
    g[x].insert(y);
    g[y].insert(x);
}

bool cmp(int x,int y){
    queue<int> qx,qy;
    qx.push(x);qy.push(y);
    vis[x]=vis[y]=++T;
    ptr[x]=g[x].begin();
    ptr[y]=g[y].begin();

    while(true){
        while(!qx.empty()){
            int u=qx.front();
            while(ptr[u]!=g[u].end() && vis[*ptr[u]]==T) ptr[u]++;
            if(ptr[u]==g[u].end()) qx.pop();
            else{
                int v=*ptr[u];
                ptr[v]=g[v].begin();
                vis[v]=T;qx.push(v);
                break;
            }
        }
        if(qx.empty()) return false;
        while(!qy.empty()){
            int u=qy.front();
            while(ptr[u]!=g[u].end() && vis[*ptr[u]]==T) ptr[u]++;
            if(ptr[u]==g[u].end()) qy.pop();
            else{
                int v=*ptr[u];
                ptr[v]=g[v].begin();
                vis[v]=T;qy.push(v);
                break;
            }
        }
        if(qy.empty()) return true;
    }
    return true;
}

int del(int x,int y){
    g[x].erase(y);
    g[y].erase(x);
    if(cmp(x,y)) swap(x,y);

    cnt++;
    queue<int> q;
    q.push(x);vis[x]=++T;
    while(!q.empty()){
        int u=q.front();q.pop();
        c[u]=cnt;sz[cnt]++;
        for(int v:g[u]) if(vis[v]!=T){q.push(v);vis[v]=T;}
    }
    sz[c[y]]-=sz[cnt];
    int val=sz[cnt]*sz[c[y]];
    total-=val;
    return val;
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> sub >> n >> q;
    cnt=n;
    for(int i=1;i<=n;i++) c[i]=i,sz[i]=1;
    for(int i=1;i<=q;i++){
        int op;cin >> op;
        if(op==1){
            int x,y;cin >> x >> y;
            if(sub) x^=lst,y^=lst;
            add(x,y);
        }
        else if(op==2){
            int x,y;cin >> x >> y;
            if(sub) x^=lst,y^=lst;
            p[i-1]+=del(x,y);
        }
        else{
            int t;cin >> t;
            if(sub) t^=lst;
            lst=total+p[i-1]-(i>t?p[i-t-1]:0);
            cout << lst << '\n';
        }
        p[i]=p[i-1];
    }
}
