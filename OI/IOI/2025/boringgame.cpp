#include "boringgame.h"
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define big __int128
const int inf=1000000000000000001;

long long play_game() {
  int L=1,R=inf;
  vector<array<int,3>> A;
  {
    int M=(L+R)>>1;
    if(ask(M)) L=M;
    else R=M;
    A.push_back({L,R,0LL});
  }
  for(int k=67;k>0;k--){
    if((int)A.size()==1){
      auto [l,r,t]=A[0];
      if(l+1==r) return l;
    }
    
    int m=0;
    {
      big X=0,S=0;
      for(auto [l,r,t]:A) X+=(big)(t?1:(k+1))*(r-l),S+=(r-l);
      S=X-S;X/=2;
      for(auto [l,r,t]:A){
        if(t){
          if(S<=X && X<=(S+r-l)){
            m=l+X-S;
            break;
          }
          S+=(r-l);
        }
        else{
          if((S-(big)(k-1)*(r-l))<=X && X<=S){
            m=l+(k>1?(S-X)/(k-1):0);
            break;
          }
          S-=(big)(k-1)*(r-l);
        }
      }
    }
    //cout << k << ' ' << m << endl;
    bool f=ask(m);
    vector<array<int,3>> B;
    for(auto [l,r,t]:A){
      if(!t){
        if(f) B.push_back({max(l,m),r,0LL});
        else B.push_back({l,min(m,r),0LL});
      }
      if(f) B.push_back({l,min(m,r),1LL});
      else B.push_back({max(l,m),r,1LL});
    }
    sort(B.begin(),B.end());
    A.clear();
    for(auto [l,r,t]:B) if(l<r) A.push_back({l,r,t});
  }
  return -1;
}

#undef int