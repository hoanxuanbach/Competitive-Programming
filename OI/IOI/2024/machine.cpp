#include "machine.h"
#include<bits/stdc++.h>
using namespace std;
vector<int> S={10,26,58,122};

std::vector<int> find_permutation(int N) {
	vector<int> s={0,1,2};
    for(int x:S) if(x==N) s[2]=4;
    vector<int> A;
    for(int i=0;i<=N+2;i++){
        if(i==s[0] || i==s[1] || i==s[2]) continue;
        A.push_back(i);
    }
    vector<int> B=use_machine(A);
    vector<int> C=A;
    sort(C.begin(),C.end());
    for(int x=0;x<256;x++){
        vector<int> D=B;
        for(int &y:D) y^=x;
        sort(D.begin(),D.end());
        if(C==D){
            for(int &y:B) y^=x;
            break;
        }
    }
    vector<int> pos(N+3);
    for(int i=0;i<N;i++) pos[A[i]]=i;
    vector<int> P(N);
    for(int i=0;i<N;i++) P[i]=pos[B[i]];
	return P;
}
