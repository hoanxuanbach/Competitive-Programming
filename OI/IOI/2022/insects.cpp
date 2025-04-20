#include "insects.h"
#include<bits/stdc++.h>
using namespace std;

int c[2005];

int min_cardinality(int N) {
    int d=0;
    for(int i=0;i<N;i++){
        move_inside(i);
        if(press_button()==2) move_outside(i);
        else d++,c[i]=1;
    }
    int s=d;
    int l=2,r=N/d,p=1,res=1;
    while(l<=r){
        int m=(l+r)>>1;
        if(r-l>5) m++;
        if(m<p){
            for(int i=0;i<N;i++) if(c[i]>m){
                c[i]=0,s--;
                move_outside(i);
            }
        }
        for(int i=0;i<N;i++) if(!c[i]){
            move_inside(i);
            if(press_button()==m+1) move_outside(i);
            else c[i]=m,s++;
        }
        if(s!=d*m){
            r=m-1;
            for(int i=0;i<N;i++) if(!c[i]) c[i]=-1;
        }
        else l=m+1,res=m;
        p=m;
    }
    return res;
}
