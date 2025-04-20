#include "walk.h"
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int,int>
#define pli pair<ll,int>
#define fi first
#define se second
const ll inf = 1e18;
const int maxn = 2e6+5;
vector<pii> edge[maxn];
void add_edge(int u,int v,int w){
    edge[u].push_back({v,w});
    edge[v].push_back({u,w});
}

ll min_distance(vector<int> X, vector<int> H, vector<int> L, vector<int> R, vector<int> Y, int S, int T) {
    int N=(int)H.size(),M=(int)Y.size();

    vector<pii> p(N);
    for(int i=0;i<N;i++) p[i]={H[i],i};
    sort(p.begin(),p.end(),greater<pii>());

    for(int x:{S,T}){
        vector<pii> f(M);
        for(int i=0;i<M;i++) f[i]={Y[i],i};
        sort(f.begin(),f.end(),greater<pii>());
        auto add = [&](int a,int b,int y){
            L.push_back(a);
            R.push_back(b);
            Y.push_back(y);
        };

        set<int> ss;
        int pos=0;
        for(auto [y,i]:f){
            if(R[i]<=x || x<=L[i]) continue;
            while(pos<N && p[pos].fi>=y) ss.insert(p[pos++].se);
            int b=*ss.lower_bound(x),a=*prev(ss.upper_bound(x));
            if(L[i]<a) add(L[i],a,y);
            if(a<b) add(a,b,y);
            if(b<R[i]) add(b,R[i],y);
        }
        M=(int)Y.size();
    }

    vector<pii> f(M);
    for(int i=0;i<M;i++) f[i]={Y[i],i};
    sort(f.begin(),f.end(),greater<pii>());

    int cnt=0,pos=0;
    vector<vector<pii>> g(N);
    set<int> ss;

    for(auto [y,i]:f){
        while(pos<N && p[pos].fi>=y) ss.insert(p[pos++].se);
        int a=L[i],b=R[i];ss.insert(b);
        auto it=ss.insert(a).fi;

        int k=-1;
        while(it!=ss.end() && *it<=b){
            int j=*it;
            if(!g[j].empty()) add_edge(g[j].back().se,cnt,g[j].back().fi-Y[i]);
            g[j].push_back({Y[i],cnt});
            if(k!=-1) add_edge(cnt-1,cnt,X[j]-X[k]);
            k=j;cnt++;
            if(j==a || j==b) it++;
            else it=ss.erase(it);
        }
    }
    for(int x:{S,T}){
        if(g[x].empty()) return -1;
        add_edge(g[x].back().se,cnt++,g[x].back().fi);
    }
    vector<ll> dist(cnt,inf);
    priority_queue<pli,vector<pli>,greater<pli>> pq;
    dist[cnt-2]=0;pq.push({0,cnt-2});
    while(!pq.empty()){
        auto [d,u]=pq.top();pq.pop();
        if(d!=dist[u]) continue;
        for(auto [v,w]:edge[u]){
            if(dist[u]+w<dist[v]) pq.push({dist[v]=dist[u]+w,v});
        }
    }
    return (dist[cnt-1]==inf?-1:dist[cnt-1]);
}
