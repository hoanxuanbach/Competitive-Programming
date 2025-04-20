#include "closing.h"
#include <bits/stdc++.h>
using namespace std;
const int maxn=200005;
#define pii pair<int,int>
#define pll pair<long long,long long>
#define fi first
#define se second

long long pre[maxn],suf[maxn];
long long dX[maxn],dY[maxn];
vector<pii> edge[maxn];


int max_score(int N, int X, int Y, long long K,
              vector<int> U, vector<int> V, vector<int> W)
{

    for(int i=0;i<N;i++) dX[i]=dY[i]=0,edge[i].clear();

    for(int i=0;i<N-1;i++){
        edge[U[i]].push_back({V[i],W[i]});
        edge[V[i]].push_back({U[i],W[i]});
    }

    function<void(int,int)> dfsX = [&](int u,int p){
        for(auto [v,w]:edge[u]) if(v!=p){dX[v]=dX[u]+w;dfsX(v,u);}
    };
    function<void(int,int)> dfsY = [&](int u,int p){
        for(auto [v,w]:edge[u]) if(v!=p){dY[v]=dY[u]+w;dfsY(v,u);}
    };
    dfsX(X,-1);dfsY(Y,-1);

    int res=0;
    long long sum=0;
    vector<long long> dd;
    for(int i=0;i<N;i++){
        dd.push_back(dX[i]);
        dd.push_back(dY[i]);
    }
    sort(dd.begin(),dd.end());
    for(int i=0;i<2*N;i++){
        sum+=dd[i];
        if(sum<=K) res=i+1;
    }

    int cnt=0;
    sum=0;dd.clear();
    vector<pll> pp;
    for(int i=0;i<N;i++){
        long long mn=min(dX[i],dY[i]),mx=max(dX[i],dY[i]);
        if(dX[i]+dY[i]==dX[Y]){
            cnt++;sum+=mn;
            dd.push_back(mx-mn);
        }
        else if(mn<=mx-mn){
            dd.push_back(mn);
            dd.push_back(mx-mn);
        }
        else pp.push_back({mx,mn});
    }
    sort(dd.begin(),dd.end());sort(pp.begin(),pp.end());
    for(int i=1;i<(int)dd.size();i++) dd[i]+=dd[i-1];
    for(int i=0;i<(int)pp.size();i++){
        pre[i]=pp[i].fi-pp[i].se;
        if(i) pre[i]=max(pre[i],pre[i-1]);
    }
    for(int i=(int)pp.size()-1;i>=0;i--){
        suf[i]=pp[i].se;
        if(i<(int)pp.size()-1) suf[i]=min(suf[i],suf[i+1]);
    }
    auto cal = [&](long long num){
        if(num<0) return -2*N;
        return (int)(upper_bound(dd.begin(),dd.end(),num)-dd.begin());
    };
    for(int i=0;i<=(int)pp.size();i++){
        if(i) sum+=pp[i-1].fi;
        res=max(res,cnt+2*i+cal(K-sum));
        if(i) res=max(res,cnt+2*i-1+cal(K-sum+pre[i-1]));
        if(i<(int)pp.size()) res=max(res,cnt+2*i+1+cal(K-sum-suf[i]));
    }

    return res;
}
