#include "breakthru.h"
#include<bits/stdc++.h>
using namespace std;
using i32=int;
#define int long long
#define pii pair<int,int>
#define fi first
#define se second
const int inf = 1e18;
const int maxn = 20005;
const int Max = 1e9;

int N,M;
vector<int> L,R;
vector<pii> C;

namespace Segtree{
    struct node{
        pii val={0,0};
        int add=0;
        pii lazy={inf,inf};
        node(){}
        friend node operator+(node a,node b){
            node res;
            res.val=min(a.val,b.val);
            return res;
        }
    }tree[4*maxn];
    void init(){
        for(int i=1;i<4*M;i++) tree[i]=node();
    }
    void getnew(int id,int add,pii val){
        tree[id].add+=add;
        tree[id].lazy.fi+=add;
        tree[id].val.fi+=add;
        tree[id].lazy=min(tree[id].lazy,val);
        tree[id].val=min(tree[id].val,val);
    }
    void pushdown(int id){
        getnew(id<<1,tree[id].add,tree[id].lazy);
        getnew(id<<1|1,tree[id].add,tree[id].lazy);
        tree[id].add=0;
        tree[id].lazy={inf,inf};
    }
    void update_add(int l,int r,int id,int tl,int tr,int val){
        if(tr<l || r<tl) return;
        if(tl<=l && r<=tr){
            getnew(id,val,{inf,inf});
            return;
        }
        pushdown(id);
        int mid=(l+r)>>1;
        update_add(l,mid,id<<1,tl,tr,val);update_add(mid+1,r,id<<1|1,tl,tr,val);
        tree[id]=tree[id<<1]+tree[id<<1|1];
    }
    void update_Min(int l,int r,int id,int tl,int tr,pii val){
        if(tr<l || r<tl) return;
        if(tl<=l && r<=tr){
            getnew(id,0,val);
            return;
        }
        pushdown(id);
        int mid=(l+r)>>1;
        update_Min(l,mid,id<<1,tl,tr,val);update_Min(mid+1,r,id<<1|1,tl,tr,val);
        tree[id]=tree[id<<1]+tree[id<<1|1];
    }
}

pii solve(int A,int B){
    Segtree::init();
    for(int i=0;i<N;i++){
        Segtree::update_add(1,M,1,L[i],R[i],B);
        pii val=Segtree::tree[1].val;
        Segtree::update_Min(1,M,1,1,M,{val.fi+A,val.se+1});
    }
    auto [val,cA]=Segtree::tree[1].val;
    //cout << A << ' ' << B << ' ' << val << ' ' << cA << ' ' << (val-cA*A)/B << '\n';
    return {cA,(val-cA*A)/B};
}

int cost(pii T,int A,int B){
    return T.fi*A+T.se*B;
}
void dnc(pii A,pii B){
    int X=A.se-B.se,Y=B.fi-A.fi;
    pii T=solve(X,Y);
    if(cost(T,X,Y)==cost(A,X,Y)) C.push_back(B);
    else dnc(A,T),dnc(T,B);
}

void init(i32 _N,i32 _M, std::vector<i32> Y1, std::vector<i32> Y2)
{
    N=_N;M=_M;
    vector<int> com;
    com.push_back(0);
    com.push_back(M);
    for(int i=0;i<N;i++){
        com.push_back(Y1[i]);
        com.push_back(Y2[i]+1);
    }
    sort(com.begin(),com.end());
    com.erase(unique(com.begin(),com.end()),com.end());
    L.assign(N,-1);
    R.assign(N,-1);
    for(int i=0;i<N;i++){
        L[i]=lower_bound(com.begin(),com.end(),Y1[i])-com.begin()+1;
        R[i]=lower_bound(com.begin(),com.end(),Y2[i]+1)-com.begin();
    }
    M=(int)com.size()-1;
    pii A=solve(Max,1),B=solve(1,Max);
    C.push_back(A);
    if(A!=B) dnc(A,B);
}

int minimize(i32 _A,i32 _B)
{
    int A=_A,B=_B;
    int l=0,r=(int)C.size()-1;
    while(l<r){
        int mid=(l+r)>>1;
        if(cost(C[mid],A,B)<cost(C[mid+1],A,B)) r=mid;
        else l=mid+1;
    }
    return cost(C[l],A,B);
}

#undef int