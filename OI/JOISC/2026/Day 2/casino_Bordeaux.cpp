#include "Bordeaux.h"
#include<bits/stdc++.h>
using namespace std;

namespace {
    
}

std::string Bordeaux(int N, int L, std::vector<std::vector<int>> T) {
    string res;
    res+=char('A'+(T[0][0]^1));
    int X=0,Y=0;
    for(int s=1;s<2*N-2;s++){
        int l=max(0,s-N+1);
        int r=min(s,N-1);
        if(X==N-1) Y++;
        else if(Y==N-1) X++;
        else{
            int K=0;
            for(int i=r;i>=l;i-=2) K^=T[i][s-i];
            if(K){
                if((r-X)%2==0) Y++;
                else X++;
            }
            else{
                if((r-X)%2==0) X++;
                else Y++;
            }
        }
        T[X][Y]^=1;
        for(int i=l;i<r;i++) res+=char('A'+T[i][s-i]);
    }
    res+=char('A'+(T[N-1][N-1]^1));
    res.resize(L);
	return res;
}