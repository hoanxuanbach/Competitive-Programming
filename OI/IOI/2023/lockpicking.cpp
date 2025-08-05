#include "lockpicking.h"
#include<bits/stdc++.h>
using namespace std;

int N;
vector<int> A;
vector<vector<int>> S;

int M;
vector<int> B;
vector<vector<int>> T;

void new_key(){
	M++;
	B.push_back(0);
	T.push_back({-1,-1});
}

map<vector<int>,int> mp;
int solve(vector<int> C){
	if(mp.find(C)!=mp.end()) return mp[C];
	int X=M;new_key();
	mp[C]=X;

	vector<vector<int>> P(2);
	for(int x:C) P[A[x]].push_back(x);
	B[X]=P[0].empty();
	for(int i=0;i<=1;i++){
		if(P[i].empty()) T[X][i]=X;
		else{
			vector<int> D;
			for(int x:P[i]) D.push_back(S[x][B[X]]);
			sort(D.begin(),D.end());
			D.erase(unique(D.begin(),D.end()),D.end());
			T[X][i]=solve(D);
		}
	}
	return X;
}

void construct_card(int _N, std::vector<int> _A, std::vector<std::vector<int>> _S) {
	M=N=_N;B=A=_A;T=S=_S;

	vector<int> S(N);
	iota(S.begin(),S.end(),0);
	define_states(M,B,T,solve(S));
}
