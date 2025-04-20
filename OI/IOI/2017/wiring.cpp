#include "wiring.h"
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+5;
#define ll long long
#define pii pair<ll,ll>
#define fi first
#define se second
const ll inf=1e18;

ll dp[maxn],dist[maxn],pos[2],num[maxn];
pii p[maxn];

long long min_total_length(std::vector<int> r, std::vector<int> b) {
    int n=0;p[0]={0,-1};
    for(int x:r) p[++n]={x,0};
    for(int x:b) p[++n]={x,1};
    sort(p+1,p+n+1);
    for(int i=1;i<=n;i++) dist[i]=inf;
    pos[0]=pos[1]=-1;
    for(int i=1;i<=n;i++){
        pos[p[i].se]=p[i].fi;
        if(pos[p[i].se^1]!=-1) dist[i]=min(dist[i],p[i].fi-pos[p[i].se^1]);
    }
    pos[0]=pos[1]=inf;
    for(int i=n;i>=1;i--){
        pos[p[i].se]=p[i].fi;
        if(pos[p[i].se^1]!=inf) dist[i]=min(dist[i],pos[p[i].se^1]-p[i].fi);
    }

    for(int i=1;i<=n;i++) p[i].fi+=p[i-1].fi;
    auto get = [&](int l,int r){
        return p[r].fi-p[l-1].fi;
    };

    dp[0]=0;
    for(int i=1;i<=n;i++){
        dp[i]=dp[i-1]+dist[i];
        if(p[i].se==p[i-1].se) num[i]=num[i-1]+1;
        else num[i]=1;
        if(num[i-num[i]]>=num[i]) dp[i]=min(dp[i],dp[i-2*num[i]]+get(i-num[i]+1,i)-get(i-2*num[i]+1,i-num[i]));
    }
    return dp[n];
}
