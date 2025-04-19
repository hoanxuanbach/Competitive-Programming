#include "Anna.h"
#include <bits/stdc++.h>
using namespace std;
#define ll long long

namespace AA{
    const int L=140;
    ll dp[L+5];
    void init(){
        dp[1]=dp[2]=1;dp[3]=2;
        for(int i=4;i<=L;i++) dp[i]=dp[i-2]+dp[i-3]+1;
    }
    pair<vector<int>,vector<int>> solve(long long A){
        init();
        int l=1,x=A&1;A>>=1;
        while(A>=dp[l]) A-=dp[l++];
        vector<int> a(l,0),b(l,0);
        for(int i=0;i<l;i++) a[i]=(x+i)&1;
        b[0]=x;
        for(int i=1;i<l;i++){
            if(A==0) b[i]=b[i-1]^1;
            else if(A<=dp[l-i-1]) A--,b[i]=b[i+1]=b[i-1],i++;
            else A-=(dp[l-i-1]+1),b[i]=b[i+1]=b[i+2]=b[i-1]^1,i+=2;
        }
        return {a,b};
    }
}
int Declare(){
    return 140;
}
std::pair<std::vector<int>, std::vector<int> > Anna(long long A) {
  return AA::solve(A);
}
