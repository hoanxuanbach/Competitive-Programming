#include "kanji.h"
#include<bits/stdc++.h>
using namespace std;

#define ll long long
const int maxn = 305;
const int maxm = maxn*maxn;
const ll inf = 4e18;
ll dist[maxn][maxn];
bool check[maxm];

void Anna(int N, int M, int A[], int B[], ll C[], int Q, int S[], int T[], int K, int U[]) {
    for(int i=0;i<N;i++) for(int j=0;j<N;j++) dist[i][j]=inf;
    for(int i=0;i<K;i++) check[U[i]]=true;
    for(int i=0;i<M;i++){
        if(!check[i]) dist[A[i]][B[i]]=C[i];
    }
    for(int i=0;i<N;i++) dist[i][i]=0;
    for(int k=0;k<N;k++){
        for(int i=0;i<N;i++) for(int j=0;j<N;j++) dist[i][j]=min(dist[i][j],dist[i][k]+dist[k][j]);
    }
    vector<vector<int>> g(K+1);
    for(int i=0;i<Q;i++) g[0].push_back(i);
    auto f = [&](int s,int t,int id){
        if(id==K) return dist[s][t];
        else return min(inf,dist[s][A[U[id]]]+dist[B[U[id]]][t]);
    };
    vector<pair<int,int>> p;
    for(int i=1;i<=K;i++){
        ll c=(i==K?0:C[U[i]]);
        for(int j=0;j<i;j++){
            sort(g[j].begin(),g[j].end(),[f,S,T,i,j](int x,int y){
                ll dx=f(S[x],T[x],i)-f(S[x],T[x],j);
                ll dy=f(S[y],T[y],i)-f(S[y],T[y],j);
                return dx<dy;
            });
            ll dd=C[U[j]]-c;
            int pos=0;
            while(pos<(int)g[j].size()){
                int x=g[j][pos];
                ll dx=f(S[x],T[x],i)-f(S[x],T[x],j);
                if(dx<=dd) pos++;
                else break;
            }
            p.push_back({pos,(int)g[j].size()+1});
            for(int k=0;k<pos;k++) g[i].push_back(g[j][k]);
            g[j].erase(g[j].begin(),g[j].begin()+pos);
        }
    }
    __int128 total=0;
    for(int i=(int)p.size()-1;i>=0;i--) total=total*p[i].second+p[i].first;
    while(total) Tap(total&1),total/=2;
}

int w[maxn][maxn];
void Bruno(int N, int M, int A[], int B[], long long C[], int Q, int S[], int T[], int K, int U[], int L, int X[]) {
    __int128 total=0;
    for(int i=L-1;i>=0;i--) total=total*2+X[i];

    for(int i=0;i<N;i++) for(int j=0;j<N;j++) w[i][j]=-1,dist[i][j]=inf;
    for(int i=0;i<K;i++) check[U[i]]=true;
    for(int i=0;i<M;i++){
        if(!check[i]){
            dist[A[i]][B[i]]=C[i];
            w[A[i]][B[i]]=i;
        }
    }
    for(int i=0;i<N;i++) dist[i][i]=0;
    for(int k=0;k<N;k++){
        for(int i=0;i<N;i++) for(int j=0;j<N;j++) dist[i][j]=min(dist[i][j],dist[i][k]+dist[k][j]);
    }
    int cur=0;
    vector<vector<int>> g(K+1);
    for(int i=0;i<Q;i++) g[0].push_back(i);
    auto f = [&](int s,int t,int id){
        if(id==K) return dist[s][t];
        else return min(inf,dist[s][A[U[id]]]+dist[B[U[id]]][t]);
    };
    for(int i=1;i<=K;i++){
        for(int j=0;j<i;j++){
            sort(g[j].begin(),g[j].end(),[f,S,T,i,j](int x,int y){
                ll dx=f(S[x],T[x],i)-f(S[x],T[x],j);
                ll dy=f(S[y],T[y],i)-f(S[y],T[y],j);
                return dx<dy;
            });
            int pos=total%((int)g[j].size()+1);
            total/=((int)g[j].size()+1);
            for(int k=0;k<pos;k++) g[i].push_back(g[j][k]);
            g[j].erase(g[j].begin(),g[j].begin()+pos);
        }
    }
    vector<int> num(Q,-1);
    for(int i=0;i<=K;i++) for(int x:g[i]) num[x]=i;
    function<void(int,int)> path = [&](int s,int t){
        if(s==t) return;
        for(int u=0;u<N;u++){
            if(w[s][u]==-1) continue;
            if(C[w[s][u]]+dist[u][t]==dist[s][t]){
                Answer(w[s][u]);
                return path(u,t);
            }
        }
    };
    for(int i=0;i<Q;i++){
        int id=num[i];
        //cout << i << ' ' << id << '\n';
        if(id<K){
            path(S[i],A[U[id]]);
            Answer(U[id]);
            path(B[U[id]],T[i]);
        }
        else path(S[i],T[i]);
        Answer(-1);
    }
}

