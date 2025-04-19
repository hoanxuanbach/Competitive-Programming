#include "Bruno.h"
#include <bits/stdc++.h>
using namespace std;
#define ll long long

namespace BB{
    const int L=140;
    ll dp[L+5];
    void init(){
        dp[1]=dp[2]=1;dp[3]=2;
        for(int i=4;i<=L;i++) dp[i]=dp[i-2]+dp[i-3]+1;
    }
    ll solve(vector<int> x){
        init();
        ll A=x[0];
        int l=(int)x.size()/2;
        for(int i=2*l-1;i>=0;i--) x[i]^=x[0];
        for(int i=1;i<l;i++) A+=2*dp[i];
        int c=0,d=0;
        for(int i=1,j=1;j<2*l;j++){
            d+=(x[j]?-1:1);
            if(d>=2){
                if(c==0) A+=2,i+=2;
                else A+=(dp[l-i-1]+1)*2,i+=3;
                c=d=0;
            }
            else if(d<=-2){
                if(c==1) A+=2,i+=2;
                else A+=(dp[l-i-1]+1)*2,i+=3;
                c=1;d=0;
            }
        }
        return A;
    }
}

long long Bruno(std::vector<int> u) {
  return BB::solve(u);
}
