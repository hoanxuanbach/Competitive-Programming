#include "swaps.h"
#include <bits/stdc++.h>
using namespace std;

void solve(int N, int V) {
    vector<int> p(N);
    iota(p.begin(),p.end(),1);
    int S=1;
    while(S<N) S<<=1;
    for(int x=1;x<S;x<<=1) for(int k=x;k;k>>=1){
        vector<pair<int,int>> pp;
        for(int j=k%x;j<S-k;j+=2*k) for(int i=0;i<k && i+j+k<N;i++){
            if((i+j)/(2*x)==(i+j+k)/(2*x)){
                schedule(p[i+j],p[i+j+k]);
                pp.push_back({i+j,i+j+k});
            }
        }   
        vector<int> res=visit();
        for(int i=0;i<(int)res.size();i++) if(!res[i]) swap(p[pp[i].first],p[pp[i].second]);
    }
    answer(p);
}