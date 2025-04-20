#include "wall.h"
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e6+5;

int Max[4*maxn],Min[4*maxn],res[maxn];
void pull(int id){
    Max[id]=max(Max[id<<1],Max[id<<1|1]);
    Min[id]=min(Min[id<<1],Min[id<<1|1]);
}
void getnew(int id,int val){
    Max[id]=Min[id]=val;
}
void pushdown(int id){
    if(Min[id]!=Max[id]) return;
    getnew(id<<1,Min[id]);
    getnew(id<<1|1,Min[id]);
}
void update_Max(int l,int r,int id,int tl,int tr,int x){
    if(x<=Min[id] || tr<l || r<tl) return;
    if(tl<=l && r<=tr && x>=Max[id]){
        getnew(id,x);
        return;
    }
    pushdown(id);
    int mid=(l+r)>>1;
    update_Max(l,mid,id<<1,tl,tr,x);update_Max(mid+1,r,id<<1|1,tl,tr,x);
    pull(id);
}
void update_Min(int l,int r,int id,int tl,int tr,int x){
    if(x>=Max[id] || tr<l || r<tl) return;
    if(tl<=l && r<=tr && x<=Min[id]){
        getnew(id,x);
        return;
    }
    pushdown(id);
    int mid=(l+r)>>1;
    update_Min(l,mid,id<<1,tl,tr,x);update_Min(mid+1,r,id<<1|1,tl,tr,x);
    pull(id);
}
void build(int l,int r,int id){
    if(l==r){
        res[l]=Min[id];
        return;
    }
    pushdown(id);
    int mid=(l+r)>>1;
    build(l,mid,id<<1);build(mid+1,r,id<<1|1);
}

void buildWall(int n, int k, int op[], int left[], int right[],
               int height[], int finalHeight[]){
    for(int i=0;i<k;i++){
        if(op[i]==1) update_Max(0,n-1,1,left[i],right[i],height[i]);
        else update_Min(0,n-1,1,left[i],right[i],height[i]);
    }
    build(0,n-1,1);
    for(int i=0;i<n;i++) finalHeight[i]=res[i];
}

