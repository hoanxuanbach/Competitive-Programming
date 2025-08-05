#include "routers.h"
#include<bits/stdc++.h>
using namespace std;

std::vector<int> find_routers(int L, int N, int Q) {
    vector<int> f(L+1,-1);
    f[0]=0,f[L]=N-1;
    function<void(int,int)> dnc = [&](int l,int r){
        if(f[l]==f[r]){
            for(int i=l+1;i<r;i++) f[i]=f[l];
            return;
        }
        if(l+1==r) return;
        int m=(l+r)>>1;
        f[m]=use_detector(m);
        dnc(l,m);dnc(m,r);
    };
    dnc(0,L);
    vector<int> ans(N,0);
    for(int i=L;i>=0;i--) ans[f[i]]=i;
    for(int i=1;i<N;i++) ans[i]=ans[i-1]+2*(ans[i]-1-ans[i-1]);
    return ans;
}
