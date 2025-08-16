#include "lawn.h"
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll inf = 1e18;

ll mow(int n, int _C, int _B, std::vector<int> &_A, std::vector<int> &_V) {
  int C=_C,B=_B; 
  vector<int> A(n+1),V(n+1);
  for(int i=1;i<=n;i++) A[i]=_A[i-1],V[i]=_V[i-1];
  
  ll base=0;
  vector<int> S(n+1),com={0};
  for(int i=1;i<=n;i++){
    base+=A[i],S[i]=(S[i-1]+V[i])%C;
    com.push_back(S[i]);
  }
  sort(com.begin(),com.end());
  com.erase(unique(com.begin(),com.end()),com.end());
  int sz=(int)com.size();

  vector<ll> dp(n+1);

  vector<ll> tree(4*sz,inf),lazy(4*sz,0);
  function<void(int,int,int,int,ll)> change = [&](int l,int r,int id,int x,ll val){
    if(l==r){
      tree[id]=min(tree[id],val);
      return;
    }
    int mid=(l+r)>>1;
    if(x<=mid) change(l,mid,id<<1,x,val-lazy[id]);
    else change(mid+1,r,id<<1|1,x,val-lazy[id]);
    tree[id]=min(tree[id<<1],tree[id<<1|1])+lazy[id];
  };
  function<void(int,int,int,int,int,ll)> upd = [&](int l,int r,int id,int tl,int tr,ll val){
    if(tr<l || r<tl) return;
    if(tl<=l && r<=tr){
      lazy[id]+=val;
      tree[id]+=val;
      return;
    }
    int mid=(l+r)>>1;
    upd(l,mid,id<<1,tl,tr,val);upd(mid+1,r,id<<1|1,tl,tr,val);
    tree[id]=min(tree[id<<1],tree[id<<1|1])+lazy[id];
  };
  function<ll(int,int,int,int)> query = [&](int l,int r,int id,int x){
    if(l==r) return tree[id];
    int mid=(l+r)>>1;
    if(x<=mid) return query(l,mid,id<<1,x)+lazy[id];
    else return query(mid+1,r,id<<1|1,x)+lazy[id];
  };

  auto get = [&](int x){
    return lower_bound(com.begin(),com.end(),x)-com.begin();
  };
  auto update = [&](int l,int r,ll val){
    if(l>r) return;
    if(l<0) l+=C;
    if(r<0) r+=C;
    //cout << "update " << l << ' ' << r << ' ' << val << '\n';
    if(l<=r){
      l=get(l);
      r=get(r+1)-1;
      upd(0,sz-1,1,l,r,val);
    }
    else{
      l=get(l);
      r=get(r+1)-1;
      if(l<sz) upd(0,sz-1,1,l,sz-1,val);
      if(r>=0) upd(0,sz-1,1,0,r,val);
    }
  };

  change(0,sz-1,1,get(0),0);
  for(int i=1;i<=n;i++){
    ll val=A[i]+B,K=(V[i]-1)/C,T=(C-V[i]%C)%C;
    update(S[i-1]-T+1,S[i-1],K*val);
    update(S[i-1]-C+1,S[i-1]-T,(K+1)*val);
    //0->C-(V[i]%C)

    dp[i]=min(tree[1]+B,query(0,sz-1,1,get(S[i]))-A[i]);
    //cout << dp[i] << '\n';
    change(0,sz-1,1,get(S[i]),dp[i]);
  }
  return base+dp[n];
}
