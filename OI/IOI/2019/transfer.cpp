#include "transfer.h"
#include<bits/stdc++.h>
using namespace std;

std::vector<int> get_attachment(std::vector<int> S) {
	int L=0,X=0;
	while((1<<L)<(int)S.size()) L++;
	
	vector<int> A;
	for(int i=0;i<L;i++){
		int T=0;
		for(int j=1;j<(1<<L);j++) if(j>>i&1) T^=S[j-1];
		A.push_back(T);X^=T;
	}
	A.push_back(X);
	return A;
}

std::vector<int> retrieve(std::vector<int> A) {
	int L=0;
	while((1<<(L+1))<(int)A.size()) L++;
	vector<int> B(A.begin()+(1<<L)-1,A.end());
	A.resize((1<<L)-1);

	int X=0;
	for(int i=0;i<=L;i++) X^=B[i];
	if(X) return A;
	
	int P=0;
	for(int i=0;i<L;i++){
		int T=0;
		for(int j=1;j<(1<<L);j++) if(j>>i&1) T^=A[j-1];
		P+=(T^B[i])<<i;
	}
	if(P) A[P-1]^=1;
	return A;
}
