#include<bits/stdc++.h>
using namespace std;
#define Tree vector<pair<int,int>>

namespace {
    const int K = 7;
    const int L = 24;
    const int LG = 10;
    const int mxD = 50000;
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
    void Init(){
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

        for(int i=0;i<2*K;i++) cout << c[i] << ' ';
        cout << '\n';
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
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    Init();
}