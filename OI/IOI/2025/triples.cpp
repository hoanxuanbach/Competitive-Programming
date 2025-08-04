#include "triples.h"
#include<bits/stdc++.h>
using namespace std;
#define ll long long

ll count_triples(std::vector<int> H){
  int N=(int)H.size();
  set<array<int,3>> S;

  auto cal = [&](int i,int j,int k){
    if(i>j) swap(i,j);
    if(i>k) swap(i,k);
    if(j>k) swap(j,k);
    if(i<0 || k>=N || i==j || j==k) return;
    vector<int> A={k-i,j-i,k-j};
    vector<int> B={H[i],H[j],H[k]};
    sort(A.begin(),A.end());
    sort(B.begin(),B.end());
    if(A==B) S.insert({i,j,k});
  };
  auto add = [&](int i,int j){
    if(j<0 || j>=N) return;
    for(int x:{i,j}) for(int d:{H[i],H[j]}) for(int k:{x-d,x+d}) cal(i,j,k);
  };
  for(int i=0;i<N;i++) for(int j:{i-H[i],i+H[i]}) add(i,j);
  
  ll ans=(int)S.size();
  auto check = [&](int i,int j,int k){
    return (H[i]==k-j && H[j]==k-i && H[k]==j-i && H[i]!=H[k]);
  };
  
  vector<vector<int>> A(2*N),B(2*N);
  for(int i=0;i<N;i++) A[H[i]+N-i].push_back(i);
  for(int i=N-1;i>=0;i--) B[H[i]+i].push_back(i);
  
  for(int j=0;j<N;j++){
    int a=H[j]+N-j,b=H[j]+j;
    if((int)A[a].size()<(int)B[b].size()){
      for(int i:A[a]){
        if(i==j) break;
        int k=i+H[j];
        if(k>j && k<N) ans+=check(i,j,k);
      }
    }
    else{
      for(int k:B[b]){
        if(k==j) break;
        int i=k-H[j];
        if(i>=0 && i<j) ans+=check(i,j,k);
      }
    }
  }

  return ans;
}

std::vector<int> construct_range(int N, int K) {
  int seed=1,LIM=10000;
  while(seed){
    cerr << seed << endl;
    vector<int> H(N,0);
    int cnt=0;

    auto add = [&](int s,int d){
      if(s<d) swap(s,d);
      int i=(s+d)/2,x=(s-d)/2;
      if(!H[i]) H[i]=x,cnt++;
    };
    

    vector<int> v;
    for(int i=0;i<=N;i+=2) v.push_back(i);
    mt19937_64 rng(seed);
    shuffle(v.begin(),v.end(),rng);
    if((int)v.size()>LIM) v.resize(LIM);

    for(int x:v){
      if(cnt==N) break;
      for(int y:v){
        if(x==y || cnt==N) break;
        add(x,y);
      }
    }
    for(int i=0;i<N;i++) if(!H[i]) H[i]=1;
    if(count_triples(H)>=K) return H;
    seed++;
  }
  return {};
}