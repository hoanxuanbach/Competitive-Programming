#include "hexagon.h"
#include "hexagon.cpp"
#include <cassert>
#include <cstdio>

#include <vector>

int main() {
  int N, A, B;
  assert(3 == scanf("%d %d %d", &N, &A, &B));
  std::vector<int> D(N), L(N);
  for (int i = 0; i < N; ++i) {
    assert(2 == scanf("%d %d", &D[i], &L[i]));
  }

  int result = draw_territory(N, A, B, D, L);
  printf("%d\n", result);
  return 0;
}
/*
#include "hexagon.h"
#include <bits/stdc++.h>
using namespace std;
using i32 = int;
#define int long long
#define pii pair<int,int>
#define fi first
#define se second
const int inf = 1e9;
const int mod = 1e9+7;
const int inv2 = (mod+1)/2;
int dx[]={0,0,1,1,0,-1,-1},
    dy[]={0,1,1,0,-1,-1,0};

i32 draw_territory(i32 N, i32 A, i32 B,
                   std::vector<i32> D, std::vector<i32> L) {
    int X=0,Y=0;
    int a=0,b=0;
    for(int i=0;i<N;i++){
        b+=L[i];
        int nX=X+L[i]*dx[D[i]];
        int nY=Y+L[i]*dy[D[i]];
        a+=X*nY-Y*nX;
        X=nX;Y=nY;
    }
    a=(abs(a)+b)%mod;
    a=a*inv2%mod;
    a=(a+1)%mod;

    X=0,Y=0;
    vector<pii> p;
    set<pii> ss;
    for(int i=0;i<N;i++){
        for(int j=0;j<L[i];j++){
            X+=dx[D[i]];
            Y+=dy[D[i]];
            p.push_back({X,Y});
            for(int t=1;t<=6;t++) ss.insert({X+dx[t],Y+dy[t]});
        }
    }
    for(pii x:p) ss.erase(x);

    set<pii> outers;
    queue<pii> q;
    q.push(*ss.begin());
    outers.insert(*ss.begin());

    while(!q.empty()){
        auto [x,y]=q.front();q.pop();
        for(int t=1;t<=6;t++){
            pii cc={x+dx[t],y+dy[t]};
            if(ss.find(cc)!=ss.end() && outers.find(cc)==outers.end()){
                q.push(cc);
                outers.insert(cc);
            }
        }
    }

    for(pii x:p){
        if(outers.find({x.fi,x.se-1})!=outers.end()) mp[x.fi].push_back(x.se);
        if(outers.find({x.fi,x.se+1})!=outers.end()) mp[x.fi].push_back(x.se);
    }
    for(auto &[x,v]:mp){
        sort(v.begin(),v.end());

    }
}
#undef int

*/
