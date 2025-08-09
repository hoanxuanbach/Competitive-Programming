#include "creclib.h"
#include<bits/stdc++.h>
using namespace std;

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    while(true){
        int x=dimension_x(),y=dimension_y();
        if(x==-1 && y==-1) break;
        bool sw=false;
        if(x>y) swap(x,y),sw=true;
        while(2*x+1<=y) x=2*x+1;
        if(sw) cut(vertical,x);
        else cut(horizontal,x);
    }
}
