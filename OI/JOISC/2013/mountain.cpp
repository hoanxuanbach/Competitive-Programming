#include "grader.h"
#include<bits/stdc++.h>
using namespace std;
int t=0;
int get(int x,int y){
    int h=Measure(x,y);
    if(h==t) Pinpoint(x,y);
    return h;
}
//g++ −O2 grader.cpp mountain.cpp −o mountain
void Rescue(int R, int C, int RS, int CS, int X) {
    int x=1,y=CS;t=X;
    while(x<=RS && y>=1){
        int h=get(x,y);
        if(h<X) x++;
        else y--;
    }
    x=1,y=CS;
    while(x<=RS && y<=C){
        int h=get(x,y);
        if(h<X) x++;
        else y++;
    }
    x=R;y=CS;
    while(x>RS && y>=1){
        int h=get(x,y);
        if(h<X) x--;
        else y--;
    }
    x=R;y=CS;
    while(x>RS && y<=C){
        int h=get(x,y);
        if(h<X) x--;
        else y++;
    }
}
