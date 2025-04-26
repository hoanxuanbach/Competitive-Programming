#include "workshop.h"
#include<bits/stdc++.h>
using namespace std;

const int N = 1e5;
int f[3][N+5];

void init() {
    int d=0;
    for(int i=0;i<N;i++){
        while(__builtin_popcount(d)!=10) d++;
        f[0][i]=d++;
    }
    d=0;
    for(int i=0;i<20;i++){
        while(__builtin_popcount(d)!=3) d++;
        f[1][i]=d++;
    }
    d=0;
    for(int i=0;i<6;i++){
        while(__builtin_popcount(d)!=2) d++;
        f[2][i]=d++;
    }
}

int morning(int x, int y) {
    for(int i=0;i<20;i++) if((f[0][x]>>i&1) && !(f[0][y]>>i&1)) return i;
    return -1;
}

int afternoon(int x, int y, int z) {
    int a=-1,b=-1;
    for(int i=0;i<6;i++) if((f[1][x]>>i&1) && !(f[1][y]>>i&1)){a=i;break;}
    for(int i=0;i<6;i++) if((f[1][y]>>i&1) && !(f[1][z]>>i&1)){b=i;break;}
    swap(x,a);swap(y,b);a=b=-1;
    for(int i=0;i<4;i++) if((f[2][x]>>i&1) && !(f[2][y]>>i&1)){a=i;break;}
    return a;
}

int evening(int x,int y,int z) {
    if(y<=2) return y;
    vector<int> cnt(3,0);
    cnt[x]++;cnt[z]++;
    for(int i=0;i<3;i++) if(!cnt[i]) return i;
    return -1;
}
