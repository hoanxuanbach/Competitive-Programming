#include "Bruno.h"
#include<bits/stdc++.h>
using namespace std;

namespace{
    int sz[4]={19,17,16,15};
    string s[4]={"0100201101202102200", "01100201202102200", "1100201202102200", "011002102201200"};
    string C="RGB";
    int f(char x){return find(C.begin(),C.end(),x)-C.begin();}
}

void init(int N,int l){}

int bruno(string u) {
    if((int)u.size()<=27) return 1;
    vector<int> d(27),z(9);
    for(int i=0;i<27;i++){
        d[i]=(f(u[i+1])-f(u[i])+3)%3;
        if(!d[i]) z[i%9]=1;
    }
    int ss=0;
    for(int i=0;i<9;i++) if(!z[i]){
        int j=1;
        while(z[(i+j)%9]) j++;
        if(j&1) ss=(i+2)%9;
    }
    int res=0,m=1;
    for(int i=0;i<4;i++){
        string cc;
        for(int j=0;j<3;j++) cc+=char('0'+d[9*j+(2*i+ss)%9]);
        for(int j=0;j<sz[i];j++){
            int ok=1;
            for(int k=0;k<3;k++) if(s[i][(j+k)%sz[i]]!=cc[k]) ok=0;
            if(!ok) continue;
            int k=j;
            if(2*i+ss>=9) k=(k+1)%sz[i];
            while(res%sz[i]!=k) res+=m;
            m*=sz[i];break;
        }
    }
    return 9*res-ss+1;
}
