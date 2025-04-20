#include "friend.h"
#include<bits/stdc++.h>
using namespace std;
const int inf = 1e9;
const int maxn = 1e5+5;
int dp[maxn][2];

int findSample(int n,int confidence[],int host[],int protocol[]){

    for(int i=0;i<n;i++) dp[i][1]=confidence[i];
    for(int i=n-1;i>=1;i--){
        int j=host[i],id=protocol[i];
        if(id==0){
            dp[j][0]+=max(dp[i][0],dp[i][1]);
            dp[j][1]+=dp[i][0];
        }
        else if(id==1){
            dp[j][1]=max({dp[j][1]+dp[i][0],dp[j][0]+dp[i][1],dp[j][1]+dp[i][1]});
            dp[j][0]+=dp[i][0];
        }
        else{
            dp[j][1]=max({dp[j][1]+dp[i][0],dp[j][0]+dp[i][1]});
            dp[j][0]+=dp[i][0];
        }
    }
	return max(dp[0][0],dp[0][1]);
}
