#include "vision.h"
#include<bits/stdc++.h>
using namespace std;

int solve(int h,int w,int k){
    vector<int> dL[400],dR[400],pL,pR,ans;

    for(int i=0;i<h;i++) for(int j=0;j<w;j++){
        dL[i+j].push_back(i*w+j);
        dR[i+(w-1-j)].push_back(i*w+j);
    }

    for(int d=k;d<h+w-1;d++){
        pL.push_back(add_or(dL[d-k]));
        pR.push_back(add_or(dR[d-k]));
        ans.push_back(add_and({add_or(dL[d]),add_or(pL)}));
        ans.push_back(add_and({add_or(dR[d]),add_or(pR)}));
    }
    return add_or(ans);
}

void construct_network(int h, int w, int k) {
	if(k==h+w-2) solve(h,w,k);
    else add_and({solve(h,w,k),add_not(solve(h,w,k+1))});
}
