#include "highway.h"
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5+5;
#define ll long long
#define pii pair<int,int>
#define fi first
#define se second

int dd[2][maxn];
vector<pii> edge[maxn];

void find_pair(int N, std::vector<int> U, std::vector<int> V, int A, int B) {
    vector<int> S(2,0),T(2,0);
    int M=(int)U.size();
    for(int i=0;i<M;i++){
        edge[U[i]].push_back({V[i],i});
        edge[V[i]].push_back({U[i],i});
    }

    vector<int> w(M,0);
    ll dist=ask(w);
    int l=1,r=M;
    while(l<r){
        int mid=(l+r)>>1;
        w.assign(M,0);
        for(int i=0;i<mid;i++) w[i]=1;
        if(ask(w)!=dist) r=mid;
        else l=mid+1;
    }
    S[0]=U[l-1],S[1]=V[l-1];
    //cout << S[0] << ' ' << S[1] << '\n';
    for(int i=0;i<=1;i++){
        queue<int> qq;
        for(int u=0;u<N;u++) dd[i][u]=-1;
        dd[i][S[i]]=0;qq.push(S[i]);
        while(!qq.empty()){
            int u=qq.front();qq.pop();
            for(auto [v,id]:edge[u]) if(dd[i][v]==-1){
                dd[i][v]=dd[i][u]+1;
                qq.push(v);
            }
        }
    }
    vector<vector<int>> cc(2);
    for(int u=0;u<N;u++){
        if(dd[0][u]<dd[1][u]) cc[0].push_back(u);
        else if(dd[0][u]>dd[1][u]) cc[1].push_back(u);
    }

    for(int i=0;i<=1;i++){
        sort(cc[i].begin(),cc[i].end(),[&](int x,int y){
            return dd[i][x]>dd[i][y];
        });
        //for(int x:cc[i]) cout << x << ' ';
        //cout << '\n';
        T[i]=cc[i].back();
        l=0,r=(int)cc[i].size()-2;
        while(l<=r){
            int mid=(l+r)>>1;
            w.assign(M,0);
            for(int j=0;j<=mid;j++) for(auto [v,id]:edge[cc[i][j]]) w[id]=1;
            if(ask(w)!=dist) T[i]=cc[i][mid],r=mid-1;
            else l=mid+1;
        }
    }
    answer(T[0],T[1]);
}
