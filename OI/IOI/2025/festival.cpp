#include "festival.h"
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll inf = 1e15;

std::vector<int> max_coupons(int _A, std::vector<int> _P, std::vector<int> _T) {
  int N=(int)_P.size();

  ll A=_A;
  vector<ll> P(N),T(N);
  for(int i=0;i<N;i++) P[i]=_P[i],T[i]=_T[i];
  


  vector<int> ord,pos;
  for(int i=0;i<N;i++){
    if(T[i]!=1) ord.push_back(i);
    else pos.push_back(i);
  }
  sort(pos.begin(),pos.end(),[&](int i,int j){
    return P[i]<P[j];
  });
  sort(ord.begin(),ord.end(),[&](int i,int j){
    return (P[i]*T[i]*T[j]+P[j]*T[j])<(P[j]*T[j]*T[i]+P[i]*T[i]);
  });

  N=(int)ord.size();
  vector<int> res;
  bool ok=false;
  for(int i=0;i<N;i++){
    int id=ord[i];
    ll nA=(A-P[id])*T[id];
    if(nA<A){
      ok=true;
      res=vector<int>(ord.begin(),ord.begin()+i);
      ord.erase(ord.begin(),ord.begin()+i);
      break;
    }
    else A=nA;
    if(A>=inf){
      res=ord;
      res.insert(res.end(),pos.begin(),pos.end());
      return res;
    }
  }
  if(!ok){
    res=ord;
    ord.clear();
  }

  int sz=(int)pos.size();
  vector<ll> S(sz);
  for(int i=0;i<sz;i++){
    S[i]=P[pos[i]];
    if(i) S[i]+=S[i-1];
  }
  auto cal = [&](ll X){
    return upper_bound(S.begin(),S.end(),X)-S.begin();
  };

  int LG=32;
  N=(int)ord.size();
  vector<vector<ll>> dp(N+1,vector<ll>(LG,-inf));
  vector<vector<bool>> trace(N+1,vector<bool>(LG,false));

  dp[0][0]=A;
  for(int i=0;i<N;i++){
    int id=ord[i];
    for(int j=0;j<LG;j++){
      if(dp[i][j]==-inf) continue;
      ll X=dp[i][j];
      if(X>dp[i+1][j]) dp[i+1][j]=X,trace[i+1][j]=false;
      X=(X-P[id])*T[id];
      if(X>=0 && X>dp[i+1][j+1]) dp[i+1][j+1]=X,trace[i+1][j+1]=true;
    }
  }

  int mx=0,cj=0;
  for(int j=0;j<LG;j++){
    ll X=dp[N][j];
    if(X==-inf) continue;
    int cnt=j+cal(X);
    if(cnt>mx) mx=cnt,cj=j;
  }

  ll X=dp[N][cj];

  vector<int> nxt;
  for(int i=N;i>=1;i--){
    if(trace[i][cj]){
      nxt.push_back(ord[i-1]);
      cj--;
    }
  }
  reverse(nxt.begin(),nxt.end());
  res.insert(res.end(),nxt.begin(),nxt.end());

  for(int i=0;i<sz;i++){
    if(X>=P[pos[i]]){
      X-=P[pos[i]];
      res.push_back(pos[i]);
    }
  }
  return res;
}
