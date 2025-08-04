#include "obstacles.h"
#include<bits/stdc++.h>
using namespace std;
const int LG=20;

vector<int> a;
vector<vector<int>> sl,sr,sn,ln,rn;

void initialize(std::vector<int> T, std::vector<int> H) {
  int N=(int)T.size(),M=(int)H.size();
  
  vector<int> mn(N),mx(N);
  for(int i=0;i<N;i++){
    mn[i]=mx[i]=T[i];
    if(i){
      mn[i]=min(mn[i],mn[i-1]);
      mx[i]=max(mx[i],mx[i-1]);
    }
  }

  a.assign(M,-1);
  for(int i=0;i<M;i++){
    int p=lower_bound(mn.begin(),mn.end(),H[i],[&](int x,int y){
      return x>y;
    })-mn.begin();
    if(p) a[i]=mx[p-1];
  }

  vector<int> lt(M),rt(M);
  vector<pair<int,int>> v;
  for(int i=0;i<M;i++){
    int val=H[i];
    while(!v.empty() && H[v.back().first]>H[i]) val=max(val,v.back().second),v.pop_back();
    lt[i]=i;
    if(!v.empty() && a[i]>val) lt[i]=v.back().first;
    v.push_back({i,val});
  }
  v.clear();
  for(int i=M-1;i>=0;i--){
    int val=H[i];
    while(!v.empty() && H[v.back().first]>=H[i]) val=max(val,v.back().second),v.pop_back();
    rt[i]=i;
    if(!v.empty() && a[i]>val) rt[i]=v.back().first;
    v.push_back({i,val});
  }

  vector<int> nxt(M);
  for(int i=0;i<M;i++){
    if(lt[i]==i || rt[i]==i) nxt[i]=lt[i]^rt[i]^i;
    else{
      pair<int,int> L={H[lt[i]],lt[i]},R={H[rt[i]],rt[i]};
      if(L>R) nxt[i]=L.second;
      else nxt[i]=R.second;
    }
  }

  sl.assign(LG,vector<int>(M,0));
  sr.assign(LG,vector<int>(M,0));
  sn.assign(LG,vector<int>(M,0));
  ln.assign(LG,vector<int>(M,0));
  rn.assign(LG,vector<int>(M,0));
  sl[0]=lt,sr[0]=rt,sn[0]=nxt;
  for(int i=0;i<M;i++) ln[0][i]=min(i,nxt[i]),rn[0][i]=max(i,nxt[i]);
  
  for(int i=1;i<LG;i++){
    for(int j=0;j<M;j++){
      sl[i][j]=sl[i-1][sl[i-1][j]];
      sr[i][j]=sr[i-1][sr[i-1][j]];
      sn[i][j]=sn[i-1][sn[i-1][j]];
      ln[i][j]=min(ln[i-1][j],ln[i-1][sn[i-1][j]]);
      rn[i][j]=max(rn[i-1][j],rn[i-1][sn[i-1][j]]);
    }
  }
}

bool can_reach(int L, int R, int S,int D) {
  if(min(a[S],a[D])==-1) return false;
  auto f = [&](int A){
    int lA=A,rA=A;
    for(int i=LG-1;i>=0;i--){
      int nA=sn[i][A],nlA=min(lA,ln[i][A]),nrA=max(rA,rn[i][A]);
      if(L<=nlA && nrA<=R) A=nA,lA=nlA,rA=nrA;
    }
    for(int i=LG-1;i>=0;i--){
      int nA=sl[i][A];
      if(L<=nA) A=nA;
    }
    for(int i=LG-1;i>=0;i--){
      int nA=sr[i][A];
      if(nA<=R) A=nA;
    }
    return A;
  };
  return f(S)==f(D);
}
