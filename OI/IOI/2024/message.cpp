#include "message.h"
#include<bits/stdc++.h>
using namespace std;
const int S = 66;
const int N = 31;

void send_message(std::vector<bool> M, std::vector<bool> C) {
  vector<int> d(N);
  for(int i=0;i<N;i++){
    if(C[i]) continue;
    d[i]=1;
    while(C[(i+d[i])%N]) d[i]++;
  }
  int x=0;
  for(int i=0;i<S;i++){
    vector<bool> A(N);
    for(int j=0;j<N;j++){
        if(C[j]) continue;
        if(i<d[j]) A[j]=(i==d[j]-1);
        else if(x<(int)M.size()) A[j]=M[x++];
        else A[j]=!M.back();
    }
    send_packet(A);
  }
}

std::vector<bool> receive_message(std::vector<std::vector<bool>> R) {
  vector<bool> C(N,true);
  vector<int> d(N);
  for(int i=0;i<N;i++){
    for(int j=0;j<S;j++){
      if(R[j][i]){
        d[i]=j+1;
        break;
      }
    }
  }
  for(int i=0;i<N;i++){
    vector<bool> vis(N,false);
    int u=i,cnt=0;
    while(!vis[u]){
      vis[u]=true;
      u=(u+d[u])%N;
      cnt++;
    }
    if(u==i && cnt==16) C[i]=false;
  }
  vector<bool> M;
  for(int i=0;i<S;i++){
    for(int j=0;j<N;j++){
      if(C[j] || i<d[j]) continue;
      else M.push_back(R[i][j]);
    }
  }
  bool T=M.back();
  while(M.back()==T) M.pop_back();
  return M;
}
