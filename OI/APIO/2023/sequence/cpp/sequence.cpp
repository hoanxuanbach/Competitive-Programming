#include "sequence.h"
#include<bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
#define piii pair<int,pii>
#define fi first
#define se second
struct rn{//range
    int l=0,r=0;
    friend rn operator+(rn a,rn b){
        return {a.l+b.l,a.r+b.r};
    }
};
struct node{
    int sum=0;
    rn p,s;
    node(int x=0){
        p.r=max(p.r,x);p.l=min(p.l,x);
        s.r=max(s.r,x);s.l=min(s.l,x);
        sum+=x;
    }
    friend node operator+(node a,node b){
        node res;res.sum=a.sum+b.sum;
        res.p.r=max(a.p.r,a.sum+b.p.r);
        res.p.l=min(a.p.l,a.sum+b.p.l);
        res.s.r=max(b.s.r,b.sum+a.s.r);
        res.s.l=min(b.s.l,b.sum+a.s.l);
        return res;
    }
};
vector<int> a,com;
namespace Segtree{
    vector<node> tree;
    void build(int l,int r,int id){
        if(id==1) tree.resize(4*r);
        if(l==r){tree[id]=node(1);return;}
        int mid=(l+r)>>1;
        build(l,mid,id<<1);build(mid+1,r,id<<1|1);
        tree[id]=tree[id<<1]+tree[id<<1|1];
    }
    void update(int l,int r,int id,int p){
        if(l==r){tree[id]=node(-1);return;}
        int mid=(l+r)>>1;
        if(p<=mid) update(l,mid,id<<1,p);
        else update(mid+1,r,id<<1|1,p);
        tree[id]=tree[id<<1]+tree[id<<1|1];
    }
    node query(int l,int r,int id,int tl,int tr){
        if(r<tl || tr<l || tl>tr) return node(0);
        if(tl<=l && r<=tr) return tree[id];
        int mid=(l+r)>>1;
        return query(l,mid,id<<1,tl,tr)+query(mid+1,r,id<<1|1,tl,tr);
    }
};
int sequence(int n,vector<int> A){
    a.resize(n+1);
    for(int i=1;i<=n;i++){a[i]=A[i-1];com.push_back(a[i]);}
    sort(com.begin(),com.end());
    com.erase(unique(com.begin(),com.end()),com.end());
    vector<vector<int>> pos(n+1,vector<int>());
    for(int i=1;i<=n;i++){
        a[i]=lower_bound(com.begin(),com.end(),a[i])-com.begin()+1;
        pos[a[i]].push_back(i);
    }
    int ans=0;
    {//cal cnt(l,r) with (r-l+1)%2==0
        Segtree::build(1,n,1);
        for(int i=1;i<=(int)com.size();i++){
            int sz=(int)pos[i].size(),sum=Segtree::tree[1].sum;
            vector<rn> lt(sz),rt(sz);
            for(int j=sz-1;j>=0;j--) rt[j]=Segtree::query(1,n,1,pos[i][j]+1,n).s;
            for(int j=0;j<sz;j++){
                lt[j]=Segtree::query(1,n,1,1,pos[i][j]-1).p;
                Segtree::update(1,n,1,pos[i][j]);
            }
            auto check = [&](int mid){
                for(int j=0;j<=sz-mid;j++){
                    rn x=lt[j]+rt[j+mid-1];
                    if(max(x.l,sum-2*j-2*mid)<=min(x.r,sum-2*j)) return true;
                }
                return false;
            };
            int l=1,r=sz,res=1;
            while(r>=l){
                int mid=(l+r)>>1;
                if(check(mid)) res=mid,l=mid+1;
                else r=mid-1;
            }
            ans=max(ans,res);
        }
    }
    {//cal cnt(1,n)
        int res=0;sort(a.begin(),a.end());
        for(int i=1;i<=n;i++) res+=(a[i]==a[(n+1)/2]);
        ans=max(ans,res);
    }
    return ans;
}
