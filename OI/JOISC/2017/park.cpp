#include "park.h"
#include<bits/stdc++.h>
using namespace std;
const int maxn=1405;

namespace park{
    int N,Place[maxn],vis[maxn],a[maxn];
    vector<int> edge[maxn];
    void add(int u){
        while(true){
            memset(Place,0,sizeof(Place));
            for(int i=0;i<N;i++) Place[i]=a[i];
            Place[u]=true;
            if(Ask(0,u,Place)) break;
            int l=0,r=N-1,v=-1;
            while(l<=r){
                int mid=(l+r)>>1;
                memset(Place,0,sizeof(Place));
                for(int i=0;i<N;i++) Place[i]=(a[i] || i<=mid);
                Place[u]=1;
                if(Ask(0,u,Place)) v=mid,r=mid-1;
                else l=mid+1;
            }
            add(v);
        }
        vector<int> root;
        root.push_back(0);
        while(!root.empty()){
            int x=root.back();root.pop_back();
            if(a[x]==3) continue;
            memset(vis,0,sizeof(vis));
            vector<int> d;
            function<void(int)> dfs = [&](int u){
                vis[u]=1;
                d.push_back(u);
                for(int v:edge[u]) if(!vis[v] && a[v]!=3) dfs(v);
            };
            dfs(x);
            memset(Place,0,sizeof(Place));
            for(int v:d) Place[v]=1;
            Place[u]=1;
            if(!Ask(min(u,x),max(u,x),Place)) continue;

            int l=0,r=(int)d.size()-1,v=-1;
            while(l<=r){
                int mid=(l+r)>>1;
                memset(Place,0,sizeof(Place));
                for(int i=0;i<=mid;i++) Place[d[i]]=1;
                Place[u]=1;
                if(Ask(min(u,x),max(u,x),Place)) v=d[mid],r=mid-1;
                else l=mid+1;
            }

            for(int nxt:edge[v]) if(a[nxt]!=3) root.push_back(nxt);

            edge[u].push_back(v);
            edge[v].push_back(u);
            Answer(min(u,v),max(u,v));
            a[v]=3;

        }
        for(int i=0;i<N;i++) a[i]=(a[i] || (i==u));
    }
    void Detect(int T, int n) {
        a[0]=1;N=n;
        for(int i=1;i<N;i++) if(!a[i]) add(i);
    }
}


void Detect(int T, int N) {
	park::Detect(T,N);
}
