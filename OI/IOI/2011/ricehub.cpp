#include "ricehub.h"
#include<bits/stdc++.h>
using namespace std;



int besthub(int R, int L, int x[], long long B)
{
  vector<long long> X(R+1,0);
  for(int i=0;i<R;i++) X[i+1]=X[i]+x[i];
  auto check = [&](int l,int r){
    int mid=(l+r)>>1;
    long long sum=1LL*x[mid-1]*(2*mid+1-r-l)+(X[r]+X[l-1]-2*X[mid]);
    return sum<=B;
  };
  int pos=1,ans=0;
  for(int i=1;i<=R;i++){
    while(pos<=R && check(i,pos)) pos++;
    ans=max(ans,pos-i);
  }
  return ans;
}
