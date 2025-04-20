#include "seats.h"
#include<bits/stdc++.h>
using namespace std;
const int maxn = 3000005;

int N,M,K,p[maxn],c[maxn];
int tree[4*maxn],lazy[4*maxn],cnt[4*maxn];

void update(int l,int r,int id,int tl,int tr,int val){
    if(tr<l || r<tl) return;
    if(tl<=l && r<=tr){
        lazy[id]+=val;
        tree[id]+=val;
        return;
    }
    int mid=(l+r)>>1;
    update(l,mid,id<<1,tl,tr,val);update(mid+1,r,id<<1|1,tl,tr,val);
    tree[id]=min(tree[id<<1],tree[id<<1|1]);
    cnt[id]=(tree[id]==tree[id<<1])*cnt[id<<1]+(tree[id]==tree[id<<1|1])*cnt[id<<1|1];
    tree[id]+=lazy[id];
}
void build(int l,int r,int id){
    cnt[id]=r-l+1;
    if(l==r) return;
    int mid=(l+r)>>1;
    build(l,mid,id<<1);build(mid+1,r,id<<1|1);
}

void add(int x,int val){
    vector<int> a={c[x],c[x-1],c[x-M],c[x-M-1]};
    sort(a.begin(),a.end());
    if(a[0]<a[1]) update(0,K-1,1,a[0],a[1]-1,val);
    if(a[2]<a[3]) update(0,K-1,1,a[2],a[3]-1,val);
}

void cal(int x,int val){
    add(x+1,-1);add(x,-1);add(x+M,-1);add(x+M+1,-1);
    c[x]=val;
    add(x+1,1);add(x,1);add(x+M,1);add(x+M+1,1);
}

void give_initial_chart(int _N, int _M, std::vector<int> R, std::vector<int> C) {
    K=_N*_M;N=_N+2;M=_M+2;
    for(int i=0;i<N;i++) for(int j=0;j<M;j++) c[i*M+j]=K;
    for(int i=0;i<K;i++){
        R[i]++;C[i]++;
        c[R[i]*M+C[i]]=i;
        p[i]=R[i]*M+C[i];
    }
    build(0,K-1,1);
    for(int i=1;i<N;i++) for(int j=1;j<M;j++) add(i*M+j,1);
}

int swap_seats(int a, int b) {
    int x=p[a],y=p[b];
    swap(p[a],p[b]);
    cal(x,b);cal(y,a);
    return cnt[1];
}
