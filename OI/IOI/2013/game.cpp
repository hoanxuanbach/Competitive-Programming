#include "game.h"
#include<bits/stdc++.h>
using namespace std;
#define ll long long

int N,M;

int T=0;
struct node{
    ll v=0;
    int p=0,l=0,r=0;
}S[20000005];
struct Segtree{
    int root=0;
    ll update(int l,int r,int &id,int x,ll val){
        if(r<x || x<l) return (id?S[id].v:0);
        if(!id){
            id=++T,S[id].p=x;
            return S[id].v=val;
        }
        if(l==r) return S[id].v=val;
        int mid=(l+r)>>1;
        if(S[id].p) update(l,mid,S[id].l,S[id].p,S[id].v),update(mid+1,r,S[id].r,S[id].p,S[id].v),S[id].p=0;
        return S[id].v=__gcd(update(l,mid,S[id].l,x,val),update(mid+1,r,S[id].r,x,val));
    }
    ll query(int l,int r,int id,int tl,int tr){
        if(tr<l || r<tl || !id) return 0;
        if(tl<=l && r<=tr) return S[id].v;
        if(S[id].p) return ((tl<=S[id].p && S[id].p<=tr)?S[id].v:0);
        int mid=(l+r)>>1;
        return __gcd(query(l,mid,S[id].l,tl,tr),query(mid+1,r,S[id].r,tl,tr));
    };
};

int T2=0;
struct Node{
    Segtree *s;
    int l=0,r=0;
}S2[1000005];
struct Segtree2{
    int root=0;
    ll update(int l,int r,int &id,int x,int y,ll val){
        if(r<x || x<l) return (id?S2[id].s->query(1,M,S2[id].s->root,y,y):0);
        if(!id) S2[id=++T2].s=new Segtree();
        if(l==r){
            S2[id].s->update(1,M,S2[id].s->root,y,val);
            return val;
        }
        int mid=(l+r)>>1;
        val=__gcd(update(l,mid,S2[id].l,x,y,val),update(mid+1,r,S2[id].r,x,y,val));
        S2[id].s->update(1,M,S2[id].s->root,y,val);
        return val;
    }
    ll query(int l,int r,int id,int x,int y,int u,int v){
        if(r<x || u<l || !id) return 0;
        if(x<=l && r<=u) return S2[id].s->query(1,M,S2[id].s->root,y,v);
        int mid=(l+r)>>1;
        return __gcd(query(l,mid,S2[id].l,x,y,u,v),query(mid+1,r,S2[id].r,x,y,u,v));
    }
}ST;

void init(int _N,int _M){
    N=_N;M=_M;
}

void update(int P, int Q, ll K) {
    P++;Q++;
    ST.update(1,N,ST.root,P,Q,K);
}

ll calculate(int P, int Q, int U, int V) {
    P++;Q++;U++;V++;
    return ST.query(1,N,ST.root,P,Q,U,V);
}
