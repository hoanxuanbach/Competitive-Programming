#include "candies.h"
#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5+5;
#define ll long long
ll sum[4*maxn],mx[4*maxn],mn[4*maxn];

void update(int l,int r,int id,int p,int val){
    if(l==r){
        if(sum[id]) sum[id]=0;
        else sum[id]=val;
        mx[id]=max(0LL,sum[id]);
        mn[id]=min(0LL,sum[id]);
        return;
    }
    int mid=(l+r)>>1;
    if(p<=mid) update(l,mid,id<<1,p,val);
    else update(mid+1,r,id<<1|1,p,val);
    sum[id]=sum[id<<1]+sum[id<<1|1];
    mx[id]=max(mx[id<<1],sum[id<<1]+mx[id<<1|1]);
    mn[id]=min(mn[id<<1],sum[id<<1]+mn[id<<1|1]);
}
int query(int l,int r,int id,int c){
    if(l==r) return min(max(sum[id],0LL),(ll)c);
    int mid=(l+r)>>1;
    if(mx[id<<1|1]-mn[id<<1|1]>c) return query(mid+1,r,id<<1|1,c);
    int cc=query(l,mid,id<<1,c);
    if(cc+mx[id<<1|1]>c) return c+sum[id<<1|1]-mx[id<<1|1];
    if(cc+mn[id<<1|1]<0) return sum[id<<1|1]-mn[id<<1|1];
    return cc+sum[id<<1|1];
}

std::vector<int> distribute_candies(std::vector<int> c, std::vector<int> l,
                                    std::vector<int> r, std::vector<int> v) {
    int n=(int)c.size(),q=(int)l.size();
    vector<int> a(n);
    vector<vector<int>> g(n+1);
    for(int i=0;i<q;i++) g[l[i]].push_back(i+1),g[r[i]+1].push_back(-i-1);
    for(int i=0;i<n;i++){
        for(int id:g[i]){
            int p=abs(id)-1;
            update(0,q-1,1,p,v[p]);
        }
        a[i]=query(0,q-1,1,c[i]);
    }
    return a;
}
