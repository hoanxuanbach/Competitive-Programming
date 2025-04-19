#include "meetings.h"
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e3+5;
#define pii pair<int,int>
#define fi first
#define se second
vector<int> edge[maxn];
bool check[maxn];
int child[maxn],sz;
bool used[maxn];

void add(int u,int v){
    edge[u].push_back(v);
    edge[v].push_back(u);
}
void del(int u,int v){
    for(int t=0;t<2;t++){
        for(int i=0;i<(int)edge[u].size();i++){
            if(edge[u][i]==v){edge[u].erase(edge[u].begin()+i);break;}
        }
        swap(u,v);
    }
}
void dfs_sz(int u,int p){
    child[u]=1;
    for(int v:edge[u]){
        if(v==p || used[v]) continue;
        dfs_sz(v,u);child[u]+=child[v];
    }
}
int findcen(int u,int p){
    for(int v:edge[u]){
        if(v==p || used[v]) continue;
        if(child[v]>sz/2) return findcen(v,u);
    }
    return u;
}
void decompose(int u,int a){
    dfs_sz(u,0);sz=child[u];
    int x=findcen(u,0);used[x]=true;
    dfs_sz(x,0);
    vector<pii> p;
    for(int v:edge[x]){
        if(used[v]) continue;
        p.push_back({child[v],v});
    }
    sort(p.begin(),p.end(),greater<pii>());
    for(int i=0;i<(int)p.size();i+=2){
        if(i+1<(int)p.size()){
            int v1=p[i].se,v2=p[i+1].se;
            int cc=Query(v1,v2,a);
            if(cc==x) continue;
            if(!check[cc] || cc==a){
                int c2=Query(x,v1,cc);
                if(c2==cc){del(x,v1);add(x,cc);add(cc,v1);}
                else{del(x,v2);add(x,cc);add(cc,v2);}
                if(a!=cc) add(a,cc);
                check[a]=check[cc]=1;
            }
            else if(cc==v1) decompose(v1,a);
            else if(cc==v2) decompose(v2,a);
            return;
        }
        else{
            int v=p[i].se;
            int cc=Query(x,v,a);
            if(cc==x) continue;
            if(!check[cc] || cc==a){
                del(x,v);add(x,cc);add(cc,v);
                if(a!=cc) add(a,cc);
                check[a]=check[cc]=1;
            }
            else decompose(v,a);
            return;
        }
    }
    add(x,a);check[a]=true;
}
void Solve(int N) {
    check[0]=check[1]=1;add(0,1);
    while(true){
        int a=0;
        while(a<N && check[a]) a++;
        if(a==N) break;
        for(int i=0;i<N;i++) used[i]=false;
        decompose(0,a);
    }
    for(int i=0;i<N;i++){
        for(int v:edge[i]){
            if(i<v) Bridge(i,v);
        }
    }
}
