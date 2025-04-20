#include "soccer.h"
#include<bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
#define fi first
#define se second
const int maxn=2005;
const int maxl=10;
const int inf=1e9;

map<int,int> dp[maxn][maxn];

int biggest_stadium(int N, std::vector<std::vector<int>> F)
{
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if(i) F[i][j]+=F[i-1][j];
            if(j) F[i][j]+=F[i][j-1];
            if(i && j) F[i][j]-=F[i-1][j-1];
        }
    }
    auto rect = [&](int x,int y,int u,int v){
        int res=F[u][v];
        if(x) res-=F[x-1][v];
        if(y) res-=F[u][y-1];
        if(x && y) res+=F[x-1][y-1];
        return res;
    };
    auto range = [&](int x,int l,int r){
        int lx=x,rx=x-1;
        for(int i=maxl;i>=0;i--){
            if((lx-(1<<i))>=0 && !rect(lx-(1<<i),l,x,r)) lx-=(1<<i);
            if((rx+(1<<i))<N && !rect(x,l,rx+(1<<i),r)) rx+=(1<<i);
        }
        return make_pair(lx,rx);
    };
    function<int(int,int,int)> cal = [&](int x,int l,int r){
        if(dp[l][r].find(x)!=dp[l][r].end()) return dp[l][r][x];
        int res=0;
        auto [lx,rx]=range(x,l,r);
        if(x!=lx) return cal(lx,l,r);
        for(int lt=l,rt=l;rt<=r;lt++,rt=max(rt,lt)){
            auto check = [&](int R){
                return (lx>=1 && !rect(lx-1,lt,x,R)) || (rx+1<N && !rect(x,lt,rx+1,R));
            };
            if(!check(rt)) continue;
            for(int i=maxl;i>=0;i--) if(rt+(1<<i)<=r && check(rt+(1<<i))) rt+=(1<<i);
            auto [nl,nr]=range(x,lt,rt);
            res=max(res,cal(x,lt,rt)+(lx-nl+nr-rx)*(rt-lt+1));
            rt++;
        }
        //cout << l << ' ' << r << ' ' << x << ' ' << res << '\n';
        return dp[l][r][x]=res;
    };
    int ans=0;
    for(int i=0;i<N;i++){
        pii p=range(i,0,N-1);
        //cout << p.fi << ' ' << p.se << '\n';
        ans=max(ans,cal(i,0,N-1)+(p.se-p.fi+1)*N);
    }
    return ans;
}
