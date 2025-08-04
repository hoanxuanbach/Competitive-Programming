#include "pyramids.h"
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5+5;
#define ll long long
ll A[maxn],B[maxn];

void init(std::vector<int> _A, std::vector<int> _B) {
    int N=(int)_A.size();
    for(int i=1;i<=N;i++) A[i]=A[i-1]+_A[i-1],B[i]=B[i-1]+_B[i-1];
}

bool can_transform(int L, int R, int X, int Y) {
    return (A[R+1]-A[L]==B[Y+1]-B[X]);
}
