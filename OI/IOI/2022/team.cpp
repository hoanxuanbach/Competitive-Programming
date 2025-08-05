#include "team.h"
#include <bits/stdc++.h>
using namespace std;

int maximum_teams(int N, int K, std::vector<int> L) {
  sort(L.begin(),L.end());
  int cnt=0,p=0,d=0;
  for(int i=N-1;i>=0;i--){
    while(p<N && (L[p]+L[i])<=K) p++,d--;
    d=max(d,0);
    if((i-p-1)<=d) break;
    cnt++;p++;d++;
  }
  return cnt;
}
