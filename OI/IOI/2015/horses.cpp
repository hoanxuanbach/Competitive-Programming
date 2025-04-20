#include "horses.h"
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll inf=1e9+1;
const ll mod=1e9+7;
const int maxn = 5e5+5;
ll mul(ll a,ll b){
    return min(a*b,inf);
}
ll n,x[maxn],y[maxn];
struct node{
    ll p,pre,suf;
    ll pm,sm;
    node(ll pos=0):p(pos){
        pre=pm=x[p];
        suf=sm=1;
    }
    friend node operator+(node a,node b){
        node res;
        ll mm=mul(a.suf,b.pre);
        if(y[a.p]>mul(mm,y[b.p])){
            res.p=a.p;
            res.pre=a.pre;res.pm=a.pm;
            res.suf=mul(a.suf,mul(b.pre,b.suf));
            res.sm=a.sm*b.pm%mod*b.sm%mod;
        }
        else{
            res.p=b.p;
            res.suf=b.suf;res.sm=b.sm;
            res.pre=mul(b.pre,mul(a.pre,a.suf));
            res.pm=b.pm*a.pm%mod*a.sm%mod;
        }
        return res;
    }
};

node tree[4*maxn];
void update(int l,int r,int id,int p){
    if(l==r){
        tree[id]=node(l);
        return;
    }
    int mid=(l+r)>>1;
    if(p<=mid) update(l,mid,id<<1,p);
    else update(mid+1,r,id<<1|1,p);
    tree[id]=tree[id<<1]+tree[id<<1|1];
}
void build(int l,int r,int id){
    if(l==r){
        tree[id]=node(l);
        return;
    }
    int mid=(l+r)>>1;
    build(l,mid,id<<1);build(mid+1,r,id<<1|1);
    tree[id]=tree[id<<1]+tree[id<<1|1];
}

int init(int N, int X[], int Y[]) {
    n=N;
    for(int i=1;i<=n;i++) x[i]=X[i-1],y[i]=Y[i-1];
    build(1,n,1);
    return tree[1].pm*y[tree[1].p]%mod;
}

int updateX(int pos, int val) {
    x[pos+1]=val;
    update(1,n,1,pos+1);
    return tree[1].pm*y[tree[1].p]%mod;
}

int updateY(int pos, int val) {
    y[pos+1]=val;
    update(1,n,1,pos+1);
    //cout << tree[1].p << '\n';
    return tree[1].pm*y[tree[1].p]%mod;
}
