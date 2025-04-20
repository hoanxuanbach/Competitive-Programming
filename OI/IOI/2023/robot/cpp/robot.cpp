#include "robot.h"
#include<bits/stdc++.h>
using namespace std;
#define mp make_pair
const int B=-2,M=5;
string C="WSEN";

void program_pulibot()
{
    auto f = [&](vector<int> &S){
        int h=S[0],w=S[1],s=S[2],e=S[3],n=S[4];
        if(!h){
            if(w==-2 && n==-2) return s==-1?mp(4,'E'):mp(3,'S');
            else if(e==-2 && s==-2) return mp(4,'H');
            else for(int i=0;i<4;i++) if(S[i+1]-2==(i+2)%4) return mp(i+2,C[i]);
            return mp(6,'T');
        }
        else if(h>=2 && h<=5){
            int d=h-2;
            if(S[d+1]-2==(d+2)%4){
                for(int i=1;i<=4;i++){
                    int k=(d+i)%4;
                    if(S[k+1]-2==(k+2)%4 || !S[k+1]) return mp(k+2,C[k]);
                }
                return mp(6,'T');
            }
            else{
                int path=0;
                for(int i=1;i<=4;i++){
                    int k=(d+i)%4;
                    if(S[k+1]-2==(k+2)%4) return mp(h,C[k]);
                    if(S[k+1]==1) path=1;
                }
                path|=(w==-2 && n==-2);
                return mp(path,(e==-2 && s==-2)?'T':C[d]);
            }
        }
        else return mp(6,'T');
    };
    for(int h=B;h<=M;h++) for(int w=B;w<=M;w++) for(int s=B;s<=M;s++) for(int e=B;e<=M;e++) for(int n=B;n<=M;n++){
        vector<int> S={h,w,s,e,n};
        auto [Z,A]=f(S);
        if(Z>M) continue;
        set_instruction(S,Z,A);
    }
}
