#include "dango3.h"
#include <bits/stdc++.h>
using namespace std;

void Solve(int N, int M) {
    function<void(int,vector<int>)> dnc = [&](int m,vector<int> x){
        if(m==1){Answer(x);return;}
        int k=m/2;
        vector<int> x1;
        for(int i=N*m-1;i>=0;i--){
            int d=x[i];x.erase(x.begin()+i);
            if(Query(x)>=k) x1.push_back(d);
            else x.insert(x.begin()+i,d);
        }
        dnc(k,x);dnc(m-k,x1);
    };
    vector<int> x;
    for(int i=1;i<=N*M;i++) x.push_back(i);
    dnc(M,x);
}
