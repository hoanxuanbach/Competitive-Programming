#include "Bruno.h"
#include <bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
#define fi first
#define se second
namespace{
    int val2[]={
        174,68,84,191,83,16,2,202,
        103,139,195,52,91,17,243,5,
        209,77,245,214,216,218,94,
        43,62,240,190,1,109,128,35,
        93,105,117,163,37,23,78,155,
        61,176,204,29,38,235,82,180,
        255,210,187,134,238,166,50,248,
        170,21,14,194,197,11,24,0,92,151,
        126,112,172,72,215,34,106
    };
}
std::string Bruno(int N, std::vector<std::vector<int>> T) {
    string res;
    int X=0,Y=0,L=0,mask=0;
    for(int i=0;i<8;i++) mask+=(T[i][i]<<i);
    for(int i=0;i<72;i++){
        int py=i%8,px=(py+i/8)%8,lst=(i>=64);
        bool ok=false;
        for(int j=0;j<4;j++){
            int cur=val2[i];
            if(j&1) cur^=(1<<px);
            if(j&2) cur^=(1<<py);
            if(cur==mask) ok=true;
        }
        if(ok){
            X=px;Y=py;L=lst;
            break;
        }
    }
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            if(i==j || i==X || j==Y) continue;
            if(res.length()<N) res+=char(T[i][j]+'A');
        }
    }
    if(X==Y && res.length()<N) res+=char(L+'A');
    return res;
}
