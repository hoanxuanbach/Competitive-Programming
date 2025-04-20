#include<bits/stdc++.h>
#include "xylophone.h"
int a[5005];
bool ok[5005];
void solve(int n) {
    int p=n,l=1,r=n;
    while(r>=l){
        int mid=(r+l)>>1;
        if(query(1,mid)==n-1){p=mid;r=mid-1;}
        else l=mid+1;
    }
    a[p]=n;ok[n]=true;
    if(p>=2){
        a[p-1]=n-query(p-1,p);ok[a[p-1]]=true;
        for(int i=p-2;i>=1;i--){
            int d=query(i,i+1);
            if(a[i+1]-d<=0) a[i]=a[i+1]+d;
            else if(a[i+1]+d>n) a[i]=a[i+1]-d;
            else if(ok[a[i+1]-d]) a[i]=a[i+1]+d;
            else if(ok[a[i+1]+d]) a[i]=a[i+1]-d;
            else{
                int k=query(i,i+2),x=abs(a[i+1]-a[i+2]);
                if(a[i+1]>a[i+2]){
                    if(k==x+d) a[i]=a[i+1]+d;
                    else a[i]=a[i+1]-d;
                }
                else{
                    if(k==x+d) a[i]=a[i+1]-d;
                    else a[i]=a[i+1]+d;
                }
            }
            ok[a[i]]=true;
        }
    }
    if(p<n){
        a[p+1]=n-query(p,p+1);ok[a[p+1]]=true;
        for(int i=p+2;i<=n;i++){
            int d=query(i-1,i);
            if(a[i-1]-d<=0) a[i]=a[i-1]+d;
            else if(a[i-1]+d>n) a[i]=a[i-1]-d;
            else if(ok[a[i-1]-d]) a[i]=a[i-1]+d;
            else if(ok[a[i-1]+d]) a[i]=a[i-1]-d;
            else{
                int k=query(i-2,i),x=abs(a[i-1]-a[i-2]);
                if(a[i-1]>a[i-2]){
                    if(k==x+d) a[i]=a[i-1]+d;
                    else a[i]=a[i-1]-d;
                }
                else{
                    if(k==x+d) a[i]=a[i-1]-d;
                    else a[i]=a[i-1]+d;
                }
            }
            ok[a[i]]=true;
        }
    }
    for(int i=1;i<=n;i++) answer(i,a[i]);
}
/*g++ -std=c++14 -O2 -pipe -static -s -o xylophone grader.cpp xylophone.cpp*/
