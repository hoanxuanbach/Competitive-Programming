#include "ramen.h"
#include<bits/stdc++.h>
using namespace std;

void Ramen(int n) {
    vector<int> Min,Max;
    for(int i=0;i<n;i+=2){
        if(i==n-1){Min.push_back(i);Max.push_back(i);}
        else{
            int c=Compare(i,i+1);
            if(c==-1){Max.push_back(i+1);Min.push_back(i);}
            else{Max.push_back(i);Min.push_back(i+1);}
        }
    }
    int x=Max[0],y=Min[0];
    for(int i=1;i<(int)Max.size();i++){
        int cx=Compare(x,Max[i]),cy=Compare(y,Min[i]);
        if(cx==-1) swap(x,Max[i]);
        if(cy==1) swap(y,Min[i]);
    }
    Answer(y,x);
}
