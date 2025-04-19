#include "airline.h"
#include <bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
#define fi first
#define se second

void Alice( int N, int M, int A[], int B[]){
    int cur=1000;
    vector<int> c(N,0);
    for(int i=0;i<N;i++){
        if(__builtin_popcount(i)<=8) c[i]=i;
        else{
            while(__builtin_popcount(cur)>8) cur++;
            c[i]=cur++;
        }
    }
    vector<pii> p;
    for(int i=0;i<M;i++) p.push_back({A[i],B[i]});
    for(int i=0;i<N;i++){
        p.push_back({i,N+10});p.push_back({i,N+11});
        for(int j=0;j<=9;j++) if(c[i]&(1<<j)) p.push_back({i,N+j});
    }
    for(int i=0;i<=9;i++) p.push_back({N+i,N+11});
    for(int i=0;i<9;i++) p.push_back({N+i,N+i+1});
    for(int i=2;i<=4;i++) p.push_back({N,N+i});
    InitG(N+12,(int)p.size());
    for(int i=0;i<(int)p.size();i++) MakeG(i,p[i].fi,p[i].se);
}
void Bob( int V, int U, int C[], int D[] ){
    int N=V-12,s11=0;
    vector<pii> ans;
    vector<int> deg(V,0);
    vector<vector<int>> edge(V);
    for(int i=0;i<U;i++){
        deg[C[i]]++,deg[D[i]]++;
        edge[C[i]].push_back(D[i]);
        edge[D[i]].push_back(C[i]);
        //cout << C[i] << ' ' << D[i] << '\n';
    }
    for(int i=0;i<V;i++) if(deg[i]==N+10) s11=i;
    int s10=s11;
    for(int i=0;i<V;i++) s10^=i;
    for(int v:edge[s11]) s10^=v;
    vector<int> c(V,1);
    c[s10]=c[s11]=0;
    for(int v:edge[s10]) c[v]=0;
    vector<int> sl(10,-1),dl(V,0);
    for(int i=0;i<V;i++){
        if(c[i]) for(int v:edge[i]) dl[i]+=c[v];
    }

    for(int i=0;i<V;i++){
        if(dl[i]==4){
            sl[0]=i;
            for(int v:edge[i]) if(dl[v]==2) sl[1]=v;
            c[sl[0]]=c[sl[1]]=0;
            int cur=sl[1];
            for(int j=2;j<=9;j++){
                int nw=-1;
                for(int v:edge[cur]) if(c[v]) nw=v;
                sl[j]=cur=nw;c[cur]=0;
            }
        }
    }
    //for(int i=0;i<=9;i++) cout << sl[i] << ' ';
    //cout << '\n';
    vector<int> num(V,0);
    for(int i=0;i<=9;i++){
        for(int v:edge[sl[i]]) num[v]+=(1<<i);
    }
    vector<int> f(1025,0);
    int cur=1000;
    for(int i=0;i<N;i++){
        if(__builtin_popcount(i)<=8) f[i]=i;
        else{
            while(__builtin_popcount(cur)>8) cur++;
            f[cur++]=i;
        }
    }
    num[s10]=num[s11]=-1;
    for(int i=0;i<=9;i++) num[sl[i]]=-1;
    for(int i=0;i<V;i++){
        if(num[i]==-1) continue;
        for(int v:edge[i]){
            if(num[v]!=-1 && i<v) ans.push_back({f[num[i]],f[num[v]]});
        }
    }
    InitMap(N,(int)ans.size());
    for(auto &[u,v]:ans) MakeMap(u,v);
}
