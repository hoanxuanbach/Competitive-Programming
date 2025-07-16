#include"holiday.h"
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int maxn = 1e5+5;
const ll inf = 1e18;

ll tree[4*maxn];
int sz,cnt[4*maxn];
vector<int> com;

void update(int l,int r,int id,int p,int val){
    if(l==r){
        tree[id]+=val*com[l];
        cnt[id]+=val;
        return;
    }
    int mid=(l+r)>>1;
    if(p<=mid) update(l,mid,id<<1,p,val);
    else update(mid+1,r,id<<1|1,p,val);
    tree[id]=tree[id<<1]+tree[id<<1|1];
    cnt[id]=cnt[id<<1]+cnt[id<<1|1];
}
ll query(int l,int r,int id,int val){
    if(l==r) return 1LL*val*com[l];
    int mid=(l+r)>>1;
    if(cnt[id<<1|1]<val) return tree[id<<1|1]+query(l,mid,id<<1,val-cnt[id<<1|1]);
    else return query(mid+1,r,id<<1|1,val);
}

ll findMaxAttraction(int n, int s, int d, int a[]){
    for(int i=0;i<n;i++) com.push_back(a[i]);
    sort(com.begin(),com.end());
    com.erase(unique(com.begin(),com.end()),com.end());
    sz=(int)com.size();
    for(int i=0;i<n;i++) a[i]=lower_bound(com.begin(),com.end(),a[i])-com.begin();

    ll res=0;
    auto cal = [&]{
        int cl=s,cr=s-1;
        for(int i=1;i<4*sz;i++) tree[i]=cnt[i]=0;
        function<ll(int,int)> get = [&](int l,int r){
            while(cr<r) update(0,sz-1,1,a[++cr],1);
            while(cl>l) update(0,sz-1,1,a[--cl],1);
            while(cr>r) update(0,sz-1,1,a[cr--],-1);
            while(cl<l) update(0,sz-1,1,a[cl++],-1);
            int num=(s-l)+(r-l);
            if(num>d) return -inf;
            else return query(0,sz-1,1,min(d-num,r-l+1));
        };
        function<void(int,int,int,int)> dnc = [&](int l,int r,int optl,int optr){
            int mid=(l+r)>>1;
            pair<ll,int> opt={-inf,-optl};
            for(int i=optl;i<=optr;i++) opt=max(opt,{get(mid,i),-i});
            res=max(res,opt.first);opt.second=-opt.second;
            if(l<mid) dnc(l,mid-1,optl,opt.second);
            if(mid<r) dnc(mid+1,r,opt.second,optr);
        };
        dnc(0,s,s,n-1);
    };
    cal();
    reverse(a,a+n);s=n-1-s;
    cal();
    return res;
}
