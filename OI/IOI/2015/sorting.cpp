#include "sorting.h"
#include<bits/stdc++.h>
using namespace std;

int findSwapPairs(int N, int S[], int M, int X[], int Y[], int P[], int Q[]) {
    auto check = [&](int d){
        vector<int> p(N);
        for(int i=0;i<N;i++) p[i]=S[i];
        for(int i=0;i<d;i++){
            swap(p[X[i]],p[Y[i]]);
            P[i]=Q[i]=0;
        }
        int k=0;
        vector<bool> vis(N);
        for(int i=0;i<N;i++){
            if(!vis[i]){
                int u=i;
                while(!vis[u]){
                    vis[u]=true;
                    if(p[u]!=i) P[k]=u,Q[k++]=p[u];
                    u=p[u];
                }
            }
        }
        if(k<=d){
            vector<int> f(N);
            for(int i=0;i<N;i++) f[S[i]]=i,p[i]=S[i];
            for(int i=0;i<k;i++){
                swap(p[X[i]],p[Y[i]]);
                swap(f[p[X[i]]],f[p[Y[i]]]);
                int x=f[P[i]],y=f[Q[i]];
                swap(p[x],p[y]);
                swap(f[p[x]],f[p[y]]);
                P[i]=x,Q[i]=y;
            }
        }
        return k<=d;
    };
    int l=0,r=M,res=M;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(mid)) res=mid,r=mid-1;
        else l=mid+1;
    }
    check(res);
	return res;
}


