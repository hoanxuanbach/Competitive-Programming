#include "boxes.h"
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e7+5;
long long pre[maxn],suf[maxn];

long long delivery(int N, int k, int L, int p[]) {
    for(int i=0;i<N;i++) pre[i]=(i<k?0:pre[i-k])+min(L,p[i]*2);
    for(int i=N-1;i>=0;i--) suf[i]=(i+k>=N?0:suf[i+k])+2*L-max(L,p[i]*2);
    long long ans=min(suf[0],pre[N-1]);
    for(int i=0;i<N-1;i++) ans=min(ans,pre[i]+suf[i+1]);
    return ans;
}
