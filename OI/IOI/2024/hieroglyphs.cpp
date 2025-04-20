#include "hieroglyphs.h"
#include <bits/stdc++.h>
using namespace std;
const int S = 200001;
vector<int> P,Q;

struct Info{
  int p=0;
  vector<int> I,cnt,nxt,pos;

  Info(vector<int> _I):I(_I){
    int N=(int)I.size();
    cnt.assign(S,0);
    pos.assign(S,N);
    nxt.assign(N,N);
    for(int i=N-1;i>=0;i--){
      int X=I[i];
      cnt[X]++;
      nxt[i]=pos[X];
      pos[X]=i;
    }
  }
  int get(int x){
    return cnt[x];
  }
  void next(){
    cnt[I[p]]--;
    pos[I[p]]=nxt[p];
    p++;
  }
  void move(int x){
    while(p<x) next();
  }
  void jump(int x){
    move(pos[x]+1);
  }
};

vector<int> construct(vector<int> A,vector<int> B){
  int N=(int)A.size(),M=(int)B.size();
  vector<int> cntA(S),cntB(S);
  for(int i=0;i<N;i++) cntA[A[i]]++;
  for(int i=0;i<M;i++) cntB[B[i]]++;

  vector<int> posA,posB,res;
  for(int i=0;i<N;i++) if(cntA[A[i]]<=cntB[A[i]]) posA.push_back(i);
  for(int i=0;i<M;i++) if(cntB[B[i]]<cntA[B[i]]) posB.push_back(i);
  posA.push_back(N),posB.push_back(M);
  auto pA=posA.begin(),pB=posB.begin();

  Info fA(A),fB(B),gA(A),gB(B);
  gA.move(*pA);gB.move(*pB);

  while(*pA!=N || *pB!=M){
    bool dA=true,dB=true;
    int nA=A[*pA],nB=B[*pB];
    if(*pA!=N){
      dA&=fB.get(nA)>gB.get(nA);
      dB&=gB.get(nA)>=gA.get(nA);
    }
    else dA=false;
    if(*pB!=M){
      dB&=fA.get(nB)>gA.get(nB);
      dA&=gA.get(nB)>=gB.get(nB);
    }
    else dB=false;
    if(dA==dB) return {-1};
    if(dA){
      res.push_back(nA);
      fB.jump(nA);
      swap(fA,gA);
      gA.move(*(++pA));
      fA.next();
    }
    else{
      res.push_back(nB);
      fA.jump(nB);
      swap(fB,gB);
      gB.move(*(++pB));
      fB.next();
    }
    P.push_back(fA.p-1);
    Q.push_back(fB.p-1);
  }
  return res;
}

vector<int> cal(vector<int> A,vector<int> B){
  int N=(int)A.size(),M=(int)B.size();
  vector<vector<int>> pos(S);
  for(int i=0;i<M;i++) pos[B[i]].push_back(i);
  for(int i=0;i<S;i++) pos[i].push_back(M);
  
  vector<pair<int,int>> st;
  st.push_back({-1,-1});
  vector<int> lst(S,-1),res(N);
  for(int i=0;i<N;i++){
    int cur=lower_bound(st.begin(),st.end(),make_pair(lst[A[i]],-1))->second;
    if(cur<M) cur=*upper_bound(pos[A[i]].begin(),pos[A[i]].end(),cur);
    res[i]=cur;
    while(st.back().second>=cur) st.pop_back();
    st.push_back({i,cur});
    lst[A[i]]=i;
  }
  return res;
}

bool check(vector<int> A,vector<int> B,vector<int> C){
  int N=(int)A.size(),M=(int)B.size(),K=(int)C.size();
  
  vector<int> pos=cal(A,B),pre(N,-1);
  vector<bool> match(N);
  for(int i=0;i<K;i++) match[P[i]]=true,pre[P[i]]=i;
  for(int i=1;i<N;i++) if(pre[i]==-1) pre[i]=pre[i-1];
  for(int i=0;i<N;i++) if(!match[i] && pre[i]!=-1 && pos[i]<=Q[pre[i]]) return false;
  return true;
}

std::vector<int> ucs(std::vector<int> A, std::vector<int> B) {
  vector<int> res=construct(A,B);
  if(res==vector<int>{-1}) return {-1};
  if(!check(A,B,res)) return {-1};
  swap(A,B),swap(P,Q);
  if(!check(A,B,res)) return {-1};
  return res;
}
