#include "september.h"
#include <bits/stdc++.h>
using namespace std;

int solve(int N, int M, std::vector<int> F, std::vector<std::vector<int>> S) {
    vector<int> mx(N);
    for(int i=0;i<M;i++) for(int j=0;j<N-1;j++) mx[S[i][j]]=max(mx[S[i][j]],j);
    for(int i=N-1;i>=1;i--) mx[F[i]]=max(mx[F[i]],mx[i]);
    int cc=-1,k=0;
    for(int i=0;i<N-1;i++){
        if(i>cc) k++;
        for(int j=0;j<M;j++) cc=max(cc,mx[S[j][i]]);
    }
    return k;
}
