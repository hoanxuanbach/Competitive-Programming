#include "gap.h"
#include<bits/stdc++.h>
using namespace std;
long long findGap(int t, int n)
{
    long long lx,rx,l=0,r=1e18,ans=0,bl;
    if(t==1){
        MinMax(l,r,&lx,&rx);l=lx;r=rx;
        for(int i=2;i<=(n+1)/2;i++){
            MinMax(l+1,r-1,&lx,&rx);
            ans=max(ans,max(lx-l,r-rx));l=lx;r=rx;
        }
        ans=max(ans,r-l);
    }
    else{
        MinMax(l,r,&lx,&rx);ans=bl=(rx-lx-1)/(n-1)+1;
        long long pre=lx,lst=lx+1;l=lx;r=rx;
        while(lst+bl<=r){
            MinMax(lst,lst+bl-1,&lx,&rx);
            ans=max(ans,lx-pre);
            if(rx!=-1) pre=rx;
            lst=lst+bl;
        }
        if(lst<=(r-1)){
            MinMax(lst,r-1,&lx,&rx);
            ans=max(ans,lx-pre);
            if(rx!=-1) pre=rx;
        }
        ans=max(ans,r-pre);
    }
	return ans;
}

