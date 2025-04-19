#include "thief.h"
#include<bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
#define fi first
#define se second

void solve(int N, int M, std::vector<int> U, std::vector<int> V) {

  vector<vector<int>> cc;

  vector<int> ord(M);
  iota(ord.begin(),ord.end(),0);
  cc.push_back(ord);
  ord.clear();

  vector<int> sub(N),vis(N),col(N,-1),color(N,-1);
  vector<vector<int>> adj(N),tree(N);
  
  int w=0;
  while(!cc.empty()){
    bool flag=false;
    vector<vector<int>> ask(3,vector<int>(M,-1));

    vector<vector<int>> nxt;
    for(auto e:cc){
      int root = -1;
      
      vector<int> X;

      for(int id:e){
        root=U[id];
        if(adj[U[id]].empty()) X.push_back(U[id]);
        if(adj[V[id]].empty()) X.push_back(V[id]);
        adj[U[id]].push_back(V[id]);
        adj[V[id]].push_back(U[id]);
      }
      

      if((int)X.size()==2){
        int id=e[0];
        ask[0][id]=0;
        ask[1][id]=1;
      }
      else{
      

        int x=-1,num=0;
        {//find_centroid
          function<void(int)> dfs = [&](int u){
            sub[u]=1;
            vis[u]=true;
            for(int v:adj[u]){
              if(!vis[v]){
                tree[u].push_back(v);
                tree[v].push_back(u);
                dfs(v),sub[u]+=sub[v];
              }
            }
          };
          dfs(root);
          int sz=sub[root];
          function<int(int,int)> find_cen = [&](int u,int p){
            for(int v:tree[u]) if(v!=p && sub[v]>sz/2) return find_cen(v,u);
            return u;
          };
          x=find_cen(root,-1);
          function<void(int,int)> cal = [&](int u,int p){
            sub[u]=1;
            for(int v:tree[u]) if(v!=p) cal(v,u),sub[u]+=sub[v];
          };
          cal(x,-1);

          int cnt=0;
          function<void(int,int)> dfs2 = [&](int u,int p){
            color[u]=num;
            //cout << "color " << u << ' ' << num << '\n';
            for(int v:tree[u]) if(v!=p) dfs2(v,u);
          };
          for(int v:tree[x]){
            //cout << v << ' ' << sub[v] << '\n';
            if(cnt+sub[v]>sz/2) num++,cnt=0;
            cnt+=sub[v];
            dfs2(v,x);
          }
        }

        for(int i=0;i<=num;i++){
          int T=0;
          for(int u:X){
            vis[u]=0;
            if(u!=x) col[u]=(color[u]==i);
          }
          function<void(int)> dfs = [&](int u){
            vis[u]=++T;
            for(int v:adj[u]) if(col[u]==col[v] && !vis[v]) dfs(v);
          };
          vis[x]=++T;
          for(int v:adj[x]) dfs(v);
          for(int id:e){
            int u=U[id],v=V[id];
            if(col[u]==col[v]) ask[i][id]=(vis[u]<vis[v])^col[u];
            else if(col[u]!=-1 && col[v]!=-1) ask[i][id]=col[u];
            else{
              if(u==x) ask[i][id]=!col[v];
              else ask[i][id]=col[u];
            }
          }

          vector<int> ne;
          for(int id:e) if(col[U[id]] && col[V[id]]) ne.push_back(id);
          //cout << "nxt ";
          //for(int id:ne) cout << id << ' ';
          //cout << '\n';

          if(!ne.empty()) nxt.push_back(ne);
        }
      }

      for(int u:X){
        adj[u].clear();
        tree[u].clear();
        col[u]=color[u]=-1,sub[u]=vis[u]=0;
      }
    }

    for(int i=0;i<3;i++){
      if(*max_element(ask[i].begin(),ask[i].end())==-1) continue;
      vector<int> topo,deg(N),pos(N);
      //cout << '*' << i << '\n';
      for(int j=0;j<M;j++){
        int k=ask[i][j];
        if(k==-1) continue;
        //cout << j << ' ' << k << '\n';
        if(k) adj[V[j]].push_back(U[j]),deg[U[j]]++;
        else adj[U[j]].push_back(V[j]),deg[V[j]]++;
      }
      queue<int> q;
      for(int j=0;j<N;j++) if(deg[j]==0) q.push(j);
      while(!q.empty()){
        int u=q.front();q.pop();
        pos[u]=(int)topo.size();
        topo.push_back(u);
        for(int v:adj[u]) if((--deg[v])==0) q.push(v);
      }
      //for(int u:topo) cout << u << ' ';
      //cout << '\n';
      
      for(int j=0;j<M;j++) ask[i][j]=pos[U[j]]>pos[V[j]];
      for(int j=0;j<N;j++) adj[j].clear();

      if(query(ask[i])){
        ord=topo;
        flag=true;
        break;
      }
    }
    if(flag) break;
    swap(cc,nxt);
  }

  //assert(ord.empty());
  vector<int> pos(N);
  for(int i=0;i<N;i++) pos[ord[i]]=i;

  //for(int x:ord) cout << x << ' ';
  //cout << '\n';

  int l=0,r=N;
  while(l<r){
    int x=(l+r)>>1;
    vector<int> ask(M);
    for(int i=0;i<M;i++){
      int u=U[i],v=V[i];
      if(pos[u]<x && pos[v]<x) ask[i]=pos[u]>pos[v];
      else if(pos[u]>=x && pos[v]>=x) ask[i]=pos[u]<pos[v];
      else ask[i]=pos[u]<x;
    }
    if(query(ask)) r=x;
    else l=x+1;
  }
  
  int B=ord[l-1];

  l=0,r=N;
  while(l<r){
    int x=(l+r+1)>>1;
    vector<int> ask(M);
    for(int i=0;i<M;i++){
      int u=U[i],v=V[i];
      if(pos[u]<x && pos[v]<x) ask[i]=pos[u]<pos[v];
      else if(pos[u]>=x && pos[v]>=x) ask[i]=pos[u]>pos[v];
      else ask[i]=pos[u]<x;
    }
    if(query(ask)) l=x;
    else r=x-1;
  }

  int A=ord[l];
  answer(A,B);
}
