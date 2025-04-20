#include "mosaic.h"
#include <bits/stdc++.h>
using namespace std;
#define ll long long 
const int maxn = 2e5+5;
const int K = 4;
ll C[5][maxn],D[maxn][5];
ll AC[maxn],BC[maxn],AD[maxn],BD[maxn];

std::vector<ll> mosaic(std::vector<int> X, std::vector<int> Y,
                              std::vector<int> T, std::vector<int> B,
                              std::vector<int> L, std::vector<int> R) {
  int N=(int)X.size(),Q=(int)T.size();
  for(int i=0;i<N;i++){
    C[1][i+1]=X[i];
    D[i+1][1]=Y[i];
    if(i<K){
      D[1][i+1]=X[i];
      C[i+1][1]=Y[i];
    }
  }
  for(int i=2;i<=K;i++) for(int j=2;j<=N;j++) C[i][j]=!(C[i-1][j]|C[i][j-1]);
  for(int i=2;i<=N;i++) for(int j=2;j<=K;j++) D[i][j]=!(D[i-1][j]|D[i][j-1]);
  for(int i=K;i<=N;i++){
    AC[i]=AC[i-1]+C[K][i];
    BC[i]=BC[i-1]+C[K][i]*i;
    if(i>K){
      AD[i]=AD[i-1]+D[i][K];
      BD[i]=BD[i-1]+D[i][K]*i;
    }
  }
  for(int i=1;i<=K;i++) for(int j=1;j<=N;j++) C[i][j]+=C[i-1][j]+C[i][j-1]-C[i-1][j-1];
  for(int i=1;i<=N;i++) for(int j=1;j<=K;j++) D[i][j]+=D[i-1][j]+D[i][j-1]-D[i-1][j-1];

  auto query = [&](int x,int y){
    ll total=0;
    if(x>K){
      int a=max(0,y-x+K);
      total+=AC[a]*(x-K)+(AC[y]-AC[a])*y-(BC[y]-BC[a]);
    }
    if(y>K){
      int a=max(0,x-y+K);
      total+=AD[a]*(y-K)+(AD[x]-AD[a])*x-(BD[x]-BD[a]);
    }
    {
      int xk=min(x,K),yk=min(y,K);
      total+=C[xk][y]+D[x][yk]-C[xk][yk];
    }
    return total;
  };
  vector<ll> res(Q);
  for(int i=0;i<Q;i++) res[i]=query(B[i]+1,R[i]+1)-query(B[i]+1,L[i])-query(T[i],R[i]+1)+query(T[i],L[i]);
  return res;
}
