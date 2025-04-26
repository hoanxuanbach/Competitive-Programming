#include "monkey.h"
#include<bits/stdc++.h>
using namespace std;

using i32 = int;
#define int long long
#define pii pair<int,int>
#define fi first
#define se second
const int maxn = 500005;
int dp[maxn],nA[maxn],nB[maxn];
vector<pii> pA[maxn],pB[maxn];

int max_bananas(vector<i32> A,vector<i32> B,vector<pair<i32,i32>> P){
    int N=(int)A.size();
    int M=(int)P.size();
    for(int i=0;i<M;i++){
        P[i].fi--;P[i].se--;
        pA[P[i].fi].push_back({P[i].se,i+1});
        pB[P[i].se].push_back({P[i].fi,i+1});
        dp[i+1]=A[P[i].fi]+B[P[i].se];
    }
    for(int i=0;i<N;i++){
        sort(pA[i].begin(),pA[i].end());
        for(int j=0;j<(int)pA[i].size()-1;j++) nA[pA[i][j].se]=pA[i][j+1].se;
        sort(pB[i].begin(),pB[i].end());
        for(int j=0;j<(int)pB[i].size()-1;j++) nB[pB[i][j].se]=pB[i][j+1].se;
    }
    int res=0;
    for(int i=0;i<N;i++){
        for(auto [x,id]:pA[i]){
            res=max(res,dp[id]);
            if(nA[id]) dp[nA[id]]=max(dp[nA[id]],dp[id]+B[P[nA[id]-1].se]);
            if(nB[id]) dp[nB[id]]=max(dp[nB[id]],dp[id]+A[P[nB[id]-1].fi]);
        }
    }
    return res;
}
#undef int
