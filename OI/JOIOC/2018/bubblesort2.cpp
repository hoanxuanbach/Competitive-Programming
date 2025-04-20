#include "bubblesort2.h"
#include<bits/stdc++.h>
using namespace std;
#define maxn 1000005
#define pii pair<int,int>
#define fi first
#define se second
const int inf=1e9;

namespace Segtree{
    int tree[4*maxn],lazy[4*maxn];
    void getnew(int id,int val){
        tree[id]+=val;
        lazy[id]+=val;
    }
    void pushdown(int id){
        if(lazy[id]==0) return;
        getnew(id<<1,lazy[id]);
        getnew(id<<1|1,lazy[id]);
        lazy[id]=0;
    }
    void update(int l,int r,int id,int pos,int x,int val){
        if(l==r){
            tree[id]+=x;
            return;
        }
        pushdown(id);
        int mid=(l+r)>>1;
        if(pos<=mid){
            getnew(id<<1|1,val);
            update(l,mid,id<<1,pos,x,val);
        }
        else update(mid+1,r,id<<1|1,pos,x,val);
        tree[id]=max(tree[id<<1],tree[id<<1|1]);
    }
}

std::vector<int> countScans(std::vector<int> A,std::vector<int> X,std::vector<int> V){
    int n=(int)A.size(),q=(int)X.size();
    vector<int> ans(q);
    vector<pii> com;
    for(int i=0;i<n;i++) com.push_back({A[i],i});
    for(int i=0;i<q;i++) com.push_back({V[i],X[i]});
    sort(com.begin(),com.end());
    com.erase(unique(com.begin(),com.end()),com.end());
    int sz=(int)com.size();
    for(int i=1;i<=4*sz;i++) Segtree::tree[i]=-inf;
    for(int i=0;i<n;i++){
        int pos=lower_bound(com.begin(),com.end(),make_pair(A[i],i))-com.begin()+1;
        Segtree::update(1,sz,1,pos,i+inf,-1);
    }
    //cout << Segtree::tree[1] << '\n';
    for(int i=0;i<q;i++){
        int pos=lower_bound(com.begin(),com.end(),make_pair(A[X[i]],X[i]))-com.begin()+1;
        Segtree::update(1,sz,1,pos,-inf-X[i],1);
        A[X[i]]=V[i];
        pos=lower_bound(com.begin(),com.end(),make_pair(A[X[i]],X[i]))-com.begin()+1;
        Segtree::update(1,sz,1,pos,X[i]+inf,-1);
        ans[i]=Segtree::tree[1];
    }
    return ans;
}
