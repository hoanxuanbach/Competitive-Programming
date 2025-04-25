#include "Ali.h"
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5+5;

namespace Ali{
  const int K = 7;
  const int L = 24;
  const int LG = 10;
  const int mxD = 5000;
  const int sz_root = 21;
  const int sz_all = 290;
  // List of Small Tree
  const int sz7 = 5;
  vector<string> T7 = {
    "000011100111", // [0]
    "000011011011", // [1]
    "000001101111", // [2]
    "000110110011", // [3]
    "000011011101"  // [4]
  };

  const int sz6 = 11;
  vector<string> T6 = {
    "0001100111",  // Group 0
    "0001011011",  // Group 1
    "0000111011",  // Group 1
    "0000011111",  // Group 2
    "0000101111",  // Group 2
    "0001101101",  // Group 3
    "0010110011",  // Group 3
    "0001110011",  // Group 3
    "0000110111",  // Group 4
    "0000111101",  // Group 4
    "0001011101"   // Group 4
  };
  vector<int> group = {0,1,1,2,2,3,3,3,4,4,4};
  int get_hash(string hash){
    for(int i=0;i<sz6;i++) if(T6[i]==hash) return i;
    assert(false);
    return -1;
  }

  map<vector<int>,int> root_tree,all_tree;

  int id_all[sz7+5][sz6+5][2*K+5];
  int id_root[sz7+5][sz6+5];

  bool init=false;
  void INIT(){
    //cout << "A_Init" << endl;
    if(init) return;
    memset(id_all,-1,sizeof(id_all));
    memset(id_root,-1,sizeof(id_root));
    init=true;
    for(int b=0;b<sz6;b++) for(int a=group[b];a<sz7;a++){
      string cur="0"+T7[a]+"10"+T6[b]+"1";

      vector<int> deg(2*K);
      vector<vector<int>> edge(2*K);

      int T=0;
      vector<int> x;
      x.push_back(0);
      vector<pair<int,int>> e;
      for(char c:cur){
        if(c=='0'){
          e.push_back({x.back(),++T});
          x.push_back(T);
        }
        else x.pop_back();
      }
      for(auto [u,v]:e){
        deg[u]++,deg[v]++;
        edge[u].push_back(v);
      }

      T=0;
      vector<int> c(2*K,-1);
      queue<int> q;q.push(0);
      while(!q.empty()){
        int u=q.front();q.pop();
        c[u]=T++;
        for(int v:edge[u]) q.push(v);
      }

      for(auto [u,v]:e) edge[v].push_back(u);
      
      vector<bool> ex(2*K);

      if(a==1) ex[3]=true;
      else if(a==2) ex[4]=true;
      else if(a==3) ex[2]=true;
      else if(a==4) ex[1]=ex[3]=true;

      for(int i=0;i<2*K;i++){
        if(deg[i]==3 && !ex[i]) continue;
        vector<int> d(2*K,0);
        function<void(int,int)> dfs = [&](int u,int p){
          for(int v:edge[u]) if(v!=p) d[c[v]]=d[c[u]]+1,dfs(v,u);
        };
        dfs(i,-1);
        if(all_tree.find(d)==all_tree.end()) all_tree[d]=(int)all_tree.size();
        id_all[a][b][c[i]]=all_tree[d];

        if(i==0 && root_tree.find(d)==root_tree.end()) root_tree[d]=(int)root_tree.size();
        if(i==0) id_root[a][b]=root_tree[d];
      }
    }
    assert(sz_root==(int)root_tree.size());
    assert(sz_all==(int)all_tree.size());
    //cout << (int)all_tree.size() << ' ' << (int)root_tree.size() << '\n';
  }

  int cnt=0,M=0,N=0,RT;
  vector<vector<int>> edge,adj,g;
  vector<bool> head;
  vector<int> f,c,par,dep,root;
  vector<pair<int,int>> pp;

  void Init(int _N, std::vector<int> U, std::vector<int> V) {
    //cout << "Start Init" << endl;
    INIT();
    
    N=_N,cnt=0;
    edge.assign(N,{});
    for(int i=0;i<N-1;i++) edge[U[i]].push_back(V[i]),edge[V[i]].push_back(U[i]);
  
    RT=-1;
    {//Find diameter to determine the farthest vertex from each vertex and use the vertex that has degree <=2 anh the smallest farthest vertex to be the root
      vector<int> d(N),val(N);
      int A=0;
      function<void(int,int)> dfs = [&](int u,int p){
        if(d[u]>d[A]) A=u;
        for(int v:edge[u]) if(v!=p) d[v]=d[u]+1,dfs(v,u);
      };
      dfs(0,-1);
      int X=A;d[X]=0;
      dfs(X,-1);
      for(int i=0;i<N;i++) val[i]=max(val[i],d[i]);
      int Y=A;d[Y]=0;
      dfs(Y,-1);
  
      int mn=N;
      for(int i=0;i<N;i++) if((int)edge[i].size()<=2 && max(val[i],d[i])<mn) RT=i,mn=max(val[i],d[i]);
      assert(mn<=mxD);
    }
    assert(RT!=-1);

    head.assign(N,false);
    f.assign(N,-1);
    c.assign(N,-1);
    par.assign(N,-1);
    dep.assign(N,0);
    
    M=N;
    adj.assign(N,{});
    {//Decompose and modify the tree into smaller tree with left and right direct subtree has K-1 vertices without adding a new vertex to a vertex with degree = 2
  
      vector<int> sz(N),leaf(N,-1);
      {//Decompose the tree into each smaller tree of size <2*K  
        
        function<void(int,int)> dfs = [&](int u,int p){
          sz[u]=1,par[u]=p;
          for(int v:edge[u]) if(v!=p){
            dep[v]=dep[u]+1,dfs(v,u),sz[u]+=sz[v];
            if(leaf[v]!=-1) leaf[u]=leaf[v];
          }
          if(sz[u]>=K) head[u]=true,sz[u]=0,leaf[u]=-1;
          if(sz[u]==1) leaf[u]=u;
        };
        dfs(RT,-1);
        if(!head[RT]) head[RT]=true,sz[RT]=0;
  
        function<void(int,int)> dfs2 = [&](int u,int p){
          if(head[u]) f[u]=cnt++;
          else f[u]=f[p];
          for(int v:edge[u]) if(v!=p) dfs2(v,u);
        };
        dfs2(RT,-1);
      }
      //cerr << "root: " << RT << endl;
      {//Add more vertices to the tree to make it a tree with exactly 2*K-1 vertices with 6 vertices left and 6 vertices right
        for(int i=0;i<N;i++) if(!head[i]) adj[par[i]].push_back(i);
  
        
        root.assign(cnt,-1);
        g.assign(cnt,{});
        
        for(int i=0;i<N;i++){
          g[f[i]].push_back(i);
          if(head[i]) root[f[i]]=i;
        }
        for(int i=0;i<cnt;i++){
          int X=-1;
          for(int v:g[i]) if(head[v]) X=v;
          //cout << "*head " << X << endl;

          int lt=-1,rt=-1,sl=0,sr=0;
          for(int v:adj[X]){
            if(lt==-1) lt=v;
            else rt=v;
          } 
          if(lt==-1) lt=X,sl=0;
          else sl=sz[lt],lt=leaf[lt];
          if(rt==-1) rt=X,sr=0;
          else sr=sz[rt],rt=leaf[rt];
          //cerr << '*' << i << ' ' << sl << ' ' << sr << ' ' << lt << ' ' << rt << endl;
          while(sl<K-1){
            adj[lt].push_back(M);
            adj.push_back({});
            f.push_back(i);
            c.push_back(-1);
            g[i].push_back(M);
            sl++,lt=M++;
          }
          while(sr<K-1){
            adj[rt].push_back(M);
            adj.push_back({});
            f.push_back(i);
            c.push_back(-1);
            g[i].push_back(M);
            sr++,rt=M++;
          }
        }
      }
    }
    
    //for(int i=0;i<N;i++) cout << "f " << i << ": " << f[i] << endl;
    //for(int i=0;i<M;i++) for(int v:adj[i]) cerr << "adj " << i << ' ' << v << endl;
    
    pp.assign(cnt,{-1,-1});
    {//Identify the type of left and right subtree and change the larger one to size 7 
      vector<int> sz(M);
      for(int i=0;i<N;i++) if(head[i]){
        //cerr << "head " << i << ' ' << f[i] << endl;
        function<void(int)> dfs = [&](int u){
          sz[u]=1;
          for(int v:adj[u]) dfs(v),sz[u]+=sz[v];
          if((int)adj[u].size()==2){
            int x=adj[u][0],y=adj[u][1];
            if(sz[x]<sz[y]) swap(adj[u][0],adj[u][1]);
          }
        };
        dfs(i);
        
        string hash;
        function<void(int)> build = [&](int u){
          //cerr << "build " << u << endl;
          for(int v:adj[u]){
            hash+='0';
            build(v);
            hash+='1';
          }
        };
        build(adj[i][0]);
        int lt=get_hash(hash);hash.clear();
        build(adj[i][1]);
        int rt=get_hash(hash);hash.clear();
        if(lt<rt){
          swap(lt,rt);
          swap(adj[i][0],adj[i][1]);
        }
  
        
        int id=group[lt],pos=0;
        pp[f[i]]={id,rt};

        //cout << lt << ' ' << rt << ' ' << id << endl;
        //cout << M << ' ' << (int)adj.size() << '\n';
        function<void(int)> add = [&](int u){
          //cout << "add " << u << endl;
          for(int v:adj[u]){
            if(T7[id][pos]=='0') pos++;
            add(v);
            assert(T7[id][pos]=='1');
            pos++;
          }
          if(pos<(int)T7[id].size() && T7[id][pos]=='0'){
            //cout << "add " << u << ' ' << M << endl;
            adj[u].push_back(M);
            adj.push_back({});
            f.push_back(f[i]);
            c.push_back(-1);
            g[f[i]].push_back(M);
            M++,pos+=2;
          }
        };
        add(adj[i][0]);

        int num=0;
        queue<int> q;q.push(i);
        while(!q.empty()){
          int u=q.front();q.pop();
          c[u]=num++;
          for(int v:adj[u]) q.push(v);
        }
      }
      
    }
    
    for(int i=0;i<N;i++){
      //cout << "SetId " << i << ' ' << f[i] << ' ' << c[i] << '\n';
      SetID(i,f[i]*2*K+c[i]);
    }
  
    //cout << "End Init" << endl;
  }
  
  std::string SendA(std::string S) {    
    
    int val=0;
    for(int i=0;i<2*LG;i++) val+=(S[i]-'0')<<i;

    int fX=0,fY=0;
    while(val>=(fY+2)*(fY+1)/2) fY++;
    fX=val-fY*(fY+1)/2;

    //cerr << "SendA " << fX << ' ' << fY << ' ' << pp[fX].first << ' ' << pp[fY].second << endl;

    val=0;
    if(fX==fY) val+=pp[fX].first*sz6+pp[fX].second;
    else{
      val+=sz7*sz6;
      int u=root[fY],dist=0;
      while(u!=-1 && f[u]!=fX) u=par[u],dist++;
      
      if(u==-1){
        
        dist=0;
        int a=root[fX],b=root[fY];
        //cerr << "no_ancestor " << a << ' ' << b << endl;
        if(dep[a]>dep[b]) swap(a,b);
        while(dep[b]!=dep[a]) dist++,b=par[b];
        while(a!=b) dist+=2,a=par[a],b=par[b];
      }
      
      if(dist<=mxD){
        
        if(u==-1) u=root[fX];
        int b=id_all[pp[fX].first][pp[fX].second][c[u]];
        int a=id_root[pp[fY].first][pp[fY].second];
        /*
        cerr << "first " << c[u] << ' ' << a << ' ' << b << ' ' << dist << endl;
        for(int i:g[fX]) for(int v:adj[i]) cerr << "adj_fX " << c[i] << ' ' << c[v] << endl;
        cerr << endl;
        for(int i:g[fY]) for(int v:adj[i]) cerr << "adj_fY " << c[i] << ' ' << c[v] << endl;
        cerr << endl;
        */
        val+=a*sz_all*mxD+b*mxD+dist-1;
      }
      else{
        //cerr << "second" << endl;
        dist-=mxD;
        val+=sz_root*sz_all*mxD;
        int a=id_root[pp[fX].first][pp[fX].second];
        int b=id_root[pp[fY].first][pp[fY].second];
        val+=a*sz_root*mxD+b*mxD+dist-1;
      }
    }
    val+=2;
    string res(L+1,'0');
    for(int i=0;i<=L;i++) if(val>>i&1) res[i]='1';
    while(res.back()=='0') res.pop_back();
    if(res.back()=='1') res.pop_back();
    return res;
  }
}

void Init(int _N, std::vector<int> U, std::vector<int> V) {
  Ali::Init(_N,U,V);
}

std::string SendA(std::string S) {
  return Ali::SendA(S);
}
