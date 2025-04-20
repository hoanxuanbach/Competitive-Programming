#include "parks.h"
#include<bits/stdc++.h>
using namespace std;
int dx[]={0,0,2,-2},
    dy[]={2,-2,0,0};

int construct_roads(std::vector<int> X, std::vector<int> Y) {
    int N=(int)X.size();
    vector<int> U,V,A,B;

    map<pair<int,int>,int> mp;
    for(int i=0;i<N;i++) mp[{X[i],Y[i]}]=i;

    int cnt=0;
    vector<bool> vis(N);
    queue<int> q;
    q.push(0);vis[0]=1;
    while(!q.empty()){
        int u=q.front();q.pop();cnt++;
        for(int t=0;t<4;t++){
            int xt=X[u]+dx[t],yt=Y[u]+dy[t];
            if(mp.count({xt,yt})){
                int v=mp[{xt,yt}];
                if(!vis[v]) q.push(v),vis[v]=1;
            }
        }
    }
    if(cnt!=N) return 0;

    for(int i=0;i<N;i++){
        int x=X[i],y=Y[i];
        if(mp.count({x+2,y})){
            if(!((x+y)&2) || !mp.count({x,y+2}) || !mp.count({x+2,y+2})){
                U.push_back(i);V.push_back(mp[{x+2,y}]);
                A.push_back(x+1);
                if((x+y)&2) B.push_back(y+1);
                else B.push_back(y-1);
            }
        }
        if(mp.count({x,y+2})){
            if(((x+y)&2) || !mp.count({x+2,y}) || !mp.count({x+2,y+2})){
                U.push_back(i);V.push_back(mp[{x,y+2}]);
                B.push_back(y+1);
                if((x+y)&2) A.push_back(x-1);
                else A.push_back(x+1);
            }
        }
    }

    build(U,V,A,B);
    return 1;
}
