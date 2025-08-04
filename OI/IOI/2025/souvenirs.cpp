#include "souvenirs.h"
#include <bits/stdc++.h>
using namespace std;
#define ll long long

void buy_souvenirs(int N, ll P) {
  
  vector<ll> s(N);
  vector<int> c(N);
  vector<vector<int>> f(N);
  s[0]=P;
  f[0].assign(N,0);
  f[0][0]=1;

  for(int i=N-1;i>=0;i--){
    while(!s[i]){
      int j=i;
      while(!s[j]) j--;
      int cnt=0;
      for(int k=0;k<N;k++) cnt+=f[j][k];
      ll val=(s[j]-1)/cnt;

      auto [V,d]=transaction(val);
      vector<int> v(N);
      for(int x:V) v[x]=1;

      for(int k=0;k<N;k++) c[k]+=v[k];

      val-=d;
      for(int k=i+1;k<N;k++) if(v[k]) v[k]=0,val-=s[k];

      int t=0;
      while(!v[t]) t++;
      f[t]=v,s[t]=val;
    }
    for(int j=0;j<i;j++) if(s[j] && f[j][i]) f[j][i]=0,s[j]-=s[i];
  }
  for(int i=0;i<N;i++) for(int j=c[i];j<i;j++) transaction(s[i]);
  return;
}
