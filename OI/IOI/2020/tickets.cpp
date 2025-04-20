#include "tickets.h"
#include <bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
#define fi first
#define se second

long long find_maximum(int k, std::vector<std::vector<int>> x) {
	int n = x.size(),m = x[0].size();
	vector<vector<int>> answer(n,vector<int>(m,-1)),state(n,vector<int>(m,0)),pos(n,vector<int>(k,0));
	vector<int> cnt(n,k-1),sum(k,0);
	priority_queue<pii> pq;
	long long ans=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<k;j++) state[i][j]=-1,ans-=x[i][j];
        pq.push({x[i][m-1]+x[i][k-1],i});
    }
    for(int i=0;i<n*k/2;i++){
        auto [a,u]=pq.top();pq.pop();ans+=a;
        int j=cnt[u]--;
        state[u][j]=0;state[u][m-(k-j)]=1;
        if(j>=1) pq.push({x[u][j-1]+x[u][m-(k-j)-1],u});
    }
    for(int i=0;i<n;i++){
        int cur=0;
        for(int j=0;j<m;j++){
            if(state[i][j]){
                pos[i][cur]=j;
                sum[cur++]+=state[i][j];
            }
        }
    }
    for(int i=0;i<n;i++){
        vector<int> d0,d1;
        for(int j=0;j<k;j++){
            if(state[i][pos[i][j]]<0 && sum[j]<0) d0.push_back(j);
            if(state[i][pos[i][j]]>0 && sum[j]>0) d1.push_back(j);
        }
        while(!d0.empty() && !d1.empty()){
            int u=d0.back();d0.pop_back();
            int v=d1.back();d1.pop_back();
            swap(pos[i][u],pos[i][v]);
            sum[u]+=2;sum[v]-=2;
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<k;j++) answer[i][pos[i][j]]=j;
    }
	allocate_tickets(answer);
	return ans;
}
