#include "boardgames.h"
#include<bits/stdc++.h>
using namespace std;
const int maxn = 100005;
const int maxm = 200005;

struct DSU{
    int par[maxn],sz[maxn],cnt[maxm];
    vector<int> E;

    DSU(){}
    void init(int n,int m){
        for(int i=0;i<n;i++) par[i]=i,sz[i]=1;
    }
    int f(int x){
        while(x!=par[x]) x=par[x];
        return x;
    }
    void unite(int x,int y){
        x=f(x);y=f(y);
        if(x==y) return;
        if(sz[x]<sz[y]) swap(x,y);
        E.push_back(y);
        par[y]=x;sz[x]+=sz[y];
    }
    void add(int x,int y,int i){
        E.push_back(-i-1);
        if(++cnt[i]==2) unite(x,y);
    }
    int get(){
        return (int)E.size();
    }
    void roll(int s){
        while((int)E.size()>s){
            int i=E.back();E.pop_back();
            if(i<0) cnt[-i-1]--;
            else{
                int x=par[i];
                par[i]=i;sz[x]-=sz[i];
            }
        }
    }
}dsu;

int n,m,P[maxn],pos[2*maxm],ans[maxn];
array<int,3> E[2*maxm];

int del(int l,int r,int x,int m){
    int a=x,b=x,k=0;
    bool flag=false;
    auto cal = [&](int lt,int rt){
        if(lt<=P[m] && P[m]<rt){
            flag=true;
            dsu.roll(pos[lt]);
        }
        if(!flag) k++;
    };
    for(int d=(1<<20);d;d>>=1){
        if((a-d)>=P[l]) cal(a-d,a),a-=d;
        if((b+d)<=P[r]) cal(b,b+d),b+=d;
    }  
    return k;
}
void build(int l,int r,int x,int k){
    int a=x,b=x;
    auto cal = [&](int lt,int rt){
        if(k-- > 0) return;
        //cout << "add " << lt << ' ' << rt << endl;
        pos[lt]=dsu.get();
        for(int i=lt;i<rt;i++){
            auto [u,v,id]=E[i];
            dsu.add(u,v,id);
        }
    };
    for(int d=(1<<20);d>0;d>>=1){
        if((a-d)>=P[l]) cal(a-d,a),a-=d;
        if((b+d)<=P[r]) cal(b,b+d),b+=d;
    }  
}
void dnc(int l,int r,int x){
    if(l>=r) return;
    if(x==-1){
        dsu.roll(0);
        x=(P[l]+P[r])/2;
        build(l,r,x,0);
    }
    for(int i=0,a=l,b=r-1;a<b;i^=1){
        if(i){
            b--;
            if(dsu.f(b)==dsu.f(b+1)) continue;
            b++;
            if(P[b]<x) x=-1;
            else build(l,b,x,del(l,r,x,b));
            dnc(l,b,x);dnc(b,r,-1);
            return;
        }
        else{
            a++;
            if(dsu.f(a-1)==dsu.f(a)) continue;
            if(P[a]>=x) x=-1;
            else build(a,r,x,del(l,r,x,a));
            dnc(a,r,x);dnc(l,a,-1);
            return;
        }
    }
    ans[l]++;
}

vector<int> partition_players(int N, int M, vector<int> X, vector<int> Y)
{
    n=N;m=M;
    dsu.init(n,m);
    
    for(int i=0;i<m;i++){
        E[i*2]={X[i],Y[i],i};
        E[i*2+1]={Y[i],X[i],i};
        P[X[i]+1]++;
        P[Y[i]+1]++;
    }
    for(int i=1;i<=n;i++) P[i]+=P[i-1];
    sort(E,E+2*m);
    dnc(0,n,-1);

    for(int i=1;i<n;i++) ans[i]+=ans[i-1];
    vector<int> res(ans[n-1]);
    for(int i=0;i<n;i++) res[ans[i]-1]++;
    return res;
}
