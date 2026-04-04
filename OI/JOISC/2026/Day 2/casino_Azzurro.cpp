#include "Azzurro.h"
#include<bits/stdc++.h>
using namespace std;

namespace {
    
}

std::vector<std::vector<int>> Azzurro(int N, int L, std::string S){
    while(L<51) L++,S+='A';
    
    int T=0;
    vector<vector<int>> A(N,vector<int>(N));
    A[0][0]=S[T++]-'A';
    for(int s=1;s<2*N-2;s++){
        int l=max(0,s-N+1);
        int r=min(s,N-1);
        for(int i=l;i<r;i++){
            A[i][s-i]=S[T++]-'A';
            if((r-i)%2==0) A[r][s-r]^=A[i][s-i];
        }
    }
    A[N-1][N-1]=S[T++]-'A';
    return A;
}