#include "doll.h"
#include <bits/stdc++.h>
using namespace std;
const int maxn=3e5+5;


void create_circuit(int M, std::vector<int> A) {
    vector<int> s(M+1,-1),x(maxn,0),y(maxn,0),z(maxn,0);
    A.push_back(0);
    int n=(int)A.size(),sz=1,cnt=0;
    while(sz<n) sz*=2;

    function<int(int,int)> dnc = [&](int l,int r){
        if(l>=n) return -1;
        if(r-l>1){
            int mid=(l+r)>>1,u=cnt++;
            y[u]=dnc(l,mid);x[u]=dnc(mid,r);
            return -(u+1);
        }
        return 1;
    };
    dnc(0,sz);

    for(int i:A){
        int u=0;
        while(u>=0){
            z[u]^=1;
            int &w = z[u]?x[u]:y[u];
            if(w>=0){w=i;break;}
            else u=-1-w;
        }
    }
    x.resize(cnt);
    y.resize(cnt);
    answer(s,x,y);
}
