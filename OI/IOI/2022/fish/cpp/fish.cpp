#include "fish.h"

#include <bits/stdc++.h>
using namespace std;
#define ll long long
const ll inf=1e18;
struct fish{
    int y=0;
    ll cost,f0=0,f1=0;
    friend bool operator<(fish a,fish b){
        return a.y<b.y;
    }
};
long long max_weights(int N, int M, std::vector<int> X, std::vector<int> Y,
                      std::vector<int> W) {
    vector<vector<fish>> dp(N+1);
    vector<int> check(N+1,0);
    for(int i=0;i<M;i++){
        X[i]++;Y[i]++;
        dp[X[i]].push_back({Y[i]-1,W[i],0,0});
        check[X[i]]|=(Y[i]==1);
    }
    for(int i=0;i<=N;i++){
        if(!check[i]) dp[i].push_back({0,0,0,0});
        dp[i].push_back({N,0,0,0});
        sort(dp[i].begin(),dp[i].end());
    }
    dp[0].front().f0=dp[0].front().f1=0;
    dp[0].back().f0=dp[0].back().f1=-inf;
    for(int i=1;i<=N;i++){
        int cur=0;
        ll sum=0,csum=0,Max=dp[i-1][0].f0;
        //cout << i << '\n';
        for(auto &a:dp[i]){
            csum+=a.cost;
            while(cur+1<(int)dp[i-1].size() && dp[i-1][cur+1].y<=a.y){
                sum+=dp[i-1][cur].cost;cur++;
                Max=max(Max,dp[i-1][cur].f0-sum);
            }
            a.f0=Max+sum+(a.y>dp[i-1][cur].y)*dp[i-1][cur].cost;
            //cout << "*f0 " << Max << ' ' << sum+dp[i-1][cur].cost << '\n';
        }
        Max=dp[i-1].back().f1+csum;cur++;
        for(int j=(int)dp[i].size()-1;j>=0;j--){
            auto &a=dp[i][j];
            while(cur && dp[i-1][cur-1].y>=a.y){
                cur--,Max=max(Max,dp[i-1][cur].f1+csum-(dp[i-1][cur].y==a.y)*a.cost);
            }
            csum-=a.cost;
            a.f1=Max-csum;
            //cout << "*f1 " << Max << ' ' << csum << '\n';
        }
        dp[i].front().f0=max(dp[i].front().f0,dp[i-1].front().f1);
        dp[i].back().f1=max({dp[i].back().f1,dp[i].back().f0,dp[i-1].front().f1});
        /*
        for(auto a:dp[i]){
            cout << a.f0 << ' ' << a.f1 << '\n';
        }
        */
    }
    return max(dp[N].front().f1,dp[N].back().f0);
}
