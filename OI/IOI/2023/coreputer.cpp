#include "coreputer.h"
#include<bits/stdc++.h>
using namespace std;

std::vector<int> malfunctioning_cores(int N) {
    vector<int> res(N),pos(N,0);
    int l=0,r=N-1;
    while(l<r){
        int mid=(l+r)>>1;
        vector<int> v(mid+1);
        iota(v.begin(),v.end(),0);
        pos[mid]=run_diagnostic(v);
        if(pos[mid]<0) l=mid+1;
        else r=mid;
    }
    res[l]=1;
    if(l!=N-1){
        int cnt=1-pos[l];
        vector<int> cur(N-l-1);
        iota(cur.begin(),cur.end(),l+1);
        for(int i=l-1;i>=0;i--){
            cur.push_back(i);
            res[i]=(run_diagnostic(cur)>-pos[l]);
            cnt+=res[i];
            cur.pop_back();
        }
        cur.resize(l);
        iota(cur.begin(),cur.end(),0);
        for(int i=l+1;i<N;i++){
            cur.push_back(i);
            if(i==N-1) res[i]=cnt;
            else{
                res[i]=run_diagnostic(cur)>=0;
                cnt-=res[i];
            }
            cur.pop_back();
        }
    }
    return res;
}
