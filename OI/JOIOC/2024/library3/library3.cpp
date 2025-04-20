#include "library3.h"
#include <bits/stdc++.h>
using namespace std;

void solve(int N){
    vector<int> p(N);
    iota(p.begin(),p.end(),0);
    for(int i=1;i<N;i++){
        int l=0,r=i,val=query(p);
        while(l<r){
            int mid=(l+r)>>1;
            vector<int> cur=p;
            for(int j=1;j<=mid;j++) swap(cur[j-1],cur[j]);
            swap(cur[0],cur[i]);
            if(query(cur)==val+mid+1) l=mid+1;
            else r=mid;
        }
        swap(p[l],p[i]);
    }
    answer(p);
}
