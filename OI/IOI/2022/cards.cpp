#include "cards.h"
#include<bits/stdc++.h>
using namespace std;

int N,K;
void init_magician(int _N, int _K) {
  N=_N,K=_K;
}

void init_assistant(int _N, int _K) {
  N=_N,K=_K;
}

std::vector<int> choose_cards(std::vector<int> cards){
  if(K==2){
    if(cards[1]==2) return {1};
    else if(cards[0]==2) return {2};
    else return {3};
  }
  int S=0;
  for(int x:cards) S=(S+x)%K;
  int val=cards[S];cards.erase(cards.begin()+S);

  sort(cards.begin(),cards.end());
  for(int i=0;i<(val-S)/K;i++) next_permutation(cards.begin(),cards.end());
  return cards;
}

int find_discarded_card(std::vector<int> cards) {
  if(K==2) return cards[0]%3+1;
  int T=0;
  for(int x:cards) T=(T+x)%K;
  
  int val=0;
  vector<int> P=cards;
  sort(P.begin(),P.end());
  while(P!=cards) val++,next_permutation(P.begin(),P.end());
  val=val*K+(K-T)%K;
  sort(cards.begin(),cards.end());
  for(int x:cards) if(x<=val) val++;
  return val;
}
