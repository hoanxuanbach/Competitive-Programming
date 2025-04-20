#include "wombats.h"
#include<bits/stdc++.h>
using namespace std;
const int maxn = 5e3+5;
const int maxm = 2e2+5;
const int B = 10;
const int maxs = 1030;
const int inf = 1e9;

int R,C,S;
int H[maxn][maxm],V[maxn][maxm];
int tree[maxs][maxm][maxm],opt[maxm];

void init(int x,int id){
    int l=x*B,r=min((x+1)*B,R);
    for(int i=0;i<C;i++) for(int j=0;j<C;j++) tree[id][i][j]=(i!=j)*inf;
    for(int t=l;t<r;t++){
        for(int i=0;i<C;i++){
            for(int j=1;j<C;j++) tree[id][i][j]=min(tree[id][i][j],tree[id][i][j-1]+H[t][j-1]);
            for(int j=C-1;j>0;j--) tree[id][i][j-1]=min(tree[id][i][j-1],tree[id][i][j]+H[t][j-1]);
            for(int j=0;j<C;j++) tree[id][i][j]+=V[t][j];
        }
    }
}
void merge(int id){
    for(int i=0;i<C;i++) opt[i]=0;
    opt[C]=C-1;
    for(int i=0;i<C;i++) for(int j=C-1;j>=0;j--){
        tree[id][i][j]=inf;
        for(int k=opt[j];k<=opt[j+1];k++){
            int val=tree[id<<1][i][k]+tree[id<<1|1][k][j];
            if(val<tree[id][i][j]) tree[id][i][j]=val,opt[j]=k;
        }
    }
}

void build(int l,int r,int id){
    if(l==r) return init(l,id);
    int mid=(l+r)>>1;
    build(l,mid,id<<1);build(mid+1,r,id<<1|1);
    merge(id);
}
void update(int l,int r,int id,int p){
    if(l==r) return init(l,id);
    int mid=(l+r)>>1;
    if(p<=mid) update(l,mid,id<<1,p);
    else update(mid+1,r,id<<1|1,p);
    merge(id);
}

void init(int _R, int _C, int _H[5000][200], int _V[5000][200]) {
    R=_R;C=_C;
    for(int i=0;i<R;i++) for(int j=0;j<C-1;j++) H[i][j]=_H[i][j];
    for(int i=0;i<R-1;i++) for(int j=0;j<C;j++) V[i][j]=_V[i][j];
    S=(R-1)/B;
    build(0,S,1);
}

void changeH(int P, int Q, int W) {
    H[P][Q]=W;
    update(0,S,1,P/B);
}

void changeV(int P, int Q, int W) {
    V[P][Q]=W;
    update(0,S,1,P/B);
}

int escape(int V1, int V2) {
    return tree[1][V1][V2];
}
