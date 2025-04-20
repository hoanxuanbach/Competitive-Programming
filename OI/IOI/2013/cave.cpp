#include<bits/stdc++.h>
#include "cave.h"
using namespace std;

void exploreCave(int N) {
    int com[N],door[N];
    for(int i=0;i<N;i++) com[i]=door[i]=0;
    for(int i=1;i<=N;i++){
        if(tryCombination(com)!=i-1){
            for(int j=0;j<N;j++){
                if(door[j]==0) com[j]^=1;
            }
        }
        int l=0,r=N-1,pre=-1,cur=-1;
        while(r>l){
            int mid=(r+l-1)>>1;cur=mid;
            if(pre<mid){
                for(int j=pre+1;j<=mid;j++){
                    if(!door[j]) com[j]^=1;
                }
            }
            else{
                for(int j=pre;j>mid;j--){
                    if(!door[j]) com[j]^=1;
                }
            }
            if(tryCombination(com)!=i-1) r=mid;
            else l=mid+1;
            pre=mid;
        }
        door[r]=i;
        if(cur<r) com[r]^=1;
    }
    for(int i=0;i<N;i++) door[i]--;
    answer(com,door);
}
