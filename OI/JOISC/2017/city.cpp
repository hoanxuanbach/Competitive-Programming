#include "City_lib.h"
#include<bits/stdc++.h>
using namespace std;
const int N=500000;

namespace{
    const int maxn = 250005;
    vector<int> edge[maxn];
    int pos=0,L[maxn];
}

void Encode(int n, int A[], int B[])
{
    for(int i=0;i<n-1;i++){
        edge[A[i]].push_back(B[i]);
        edge[B[i]].push_back(A[i]);
    }
    function<void(int,int)> dfs = [&](int u,int p){
        L[u]=pos++;
        for(int v:edge[u]) if(v!=p) dfs(v,u);
        double cur=1.0,w=1.05;
        int num=0;
        while(L[u]+(int)cur<pos) cur*=w,num++;
        pos=L[u]+(int)cur;
        Code(u,1LL*num*N+L[u]);
    };
    dfs(0,0);
}

namespace{
    double w=1.05;
    double d[2025];
}

void InitDevice()
{
    d[0]=1;
    for(int i=1;i<=2000;i++) d[i]=d[i-1]*w;
}

int Answer(long long S, long long T)
{
    int ls=S%N,rs=ls+(int)d[S/N];
    int lt=T%N,rt=lt+(int)d[T/N];
    if(ls<=lt && rt<=rs) return 1;
    if(lt<=ls && rs<=rt) return 0;
	return 2;
}
