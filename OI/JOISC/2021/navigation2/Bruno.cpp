#include "Bruno.h"
#include <bits/stdc++.h>
using namespace std;

namespace B{
    const int Col = 12;
    vector<int> solve(int K,vector<int> value){
        vector<int> res(K,0);
        int dx=-1,dy=-1;
        for(int i=0;i<9;i++) if(value[i]==Col){
            dx=i/3,dy=i%3;
            break;
        }
        int X=value[dx*3+(dy+2)%3];
        function<int(int,int,int,int)> f = [&](int i,int j,int x,int y){
            if(j<y) return 0;
            if(j>y) return 1;
            if(i<x) return 2;
            if(i>x) return 3;
            return 4;
        };
        for(int d=0;d<9;d++){
            int i=(d/3+2-dx)%3,j=(d%3+2-dy)%3;
            int k=i*3+j;
            if(k>=7) continue;
            if(value[d]>=X) value[d]++;
            if(value[d]>=9) res[k]=value[d]-9;
            else{
                int x=d/3+(1-(value[d]-1)/3),y=d%3+(1-(value[d]-1)%3);
                res[k]=f(1,1,x,y);
            }
        }
        return res;
    }
}

std::vector<int> Bruno(int K, std::vector<int> value) {
    return B::solve(K,value);
}
