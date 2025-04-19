#include <bits/stdc++.h>
#include "library.h"
using namespace std;
 
void Solve(int n)
{
    if(n==1){Answer({1});return;}
    vector<int> m(n),res(n);
    int st=-1;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(j==i) m[j]=0;
            else m[j]=1;
        }
        int d=Query(m);
        if(d==1) st=i;
    }
    res[0]=st+1;
    vector<int> p;
    for(int i=0;i<n;i++){
        if(i!=st) p.push_back(i);
    }
    for(int i=1;i<n;i++){
        int l=1,r=n-i,f=n-i;
        while(r>=l){
            int mid=(r+l)>>1;
            for(int j=0;j<n;j++) m[j]=0;
            for(int j=0;j<mid;j++) m[p[j]]=1;
            int a=Query(m);m[st]=1;
            int b=Query(m);
            if(a==b){f=mid;r=mid-1;}
            else l=mid+1;
        }
        res[i]=p[f-1]+1;st=p[f-1];
        p.erase(p.begin()+f-1);
    }
    Answer(res);
}