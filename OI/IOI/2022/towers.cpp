#include "towers.h"
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5+5;
const int inf = 1e9;
#define pii pair<int,int>
#define piii pair<int,pii>
#define mpp make_pair
#define fi first
#define se second

int N,mn[maxn];
vector<int> H;

namespace ST{
    struct node{
        int mn=inf,mx=-inf;
        int lv=0,rv=0;
        node(){}
        friend node operator+(node a,node b){
            node res;
            res.mn=min(a.mn,b.mn);
            res.mx=max(a.mx,b.mx);
            res.lv=max({a.lv,b.lv,a.mx-b.mn});
            res.rv=max({a.rv,b.rv,b.mx-a.mn});
            return res;
        }
    }tree[4*maxn];
    void build(int l,int r,int id){
        if(l==r){
            tree[id].mn=tree[id].mx=H[l];
            return;
        }
        int mid=(l+r)>>1;
        build(l,mid,id<<1);build(mid+1,r,id<<1|1);
        tree[id]=tree[id<<1]+tree[id<<1|1];
    }
    node query(int l,int r,int id,int tl,int tr){
        if(tr<l || r<tl) return node();
        if(tl<=l && r<=tr) return tree[id];
        int mid=(l+r)>>1;
        return query(l,mid,id<<1,tl,tr)+query(mid+1,r,id<<1|1,tl,tr);
    }
}
namespace ST2{
    vector<piii> tree[4*maxn];
    void build(int l,int r,int id){
        for(int i=l;i<=r;i++) tree[id].push_back({mn[i],{i,i}});
        sort(tree[id].begin(),tree[id].end());
        for(int i=(int)tree[id].size()-2;i>=0;i--){
            tree[id][i].se.fi=min(tree[id][i].se.fi,tree[id][i+1].se.fi);
            tree[id][i].se.se=max(tree[id][i].se.se,tree[id][i+1].se.se);
        }
        if(l==r) return;
        int mid=(l+r)>>1;
        build(l,mid,id<<1);build(mid+1,r,id<<1|1);
    }
    piii query(int l,int r,int id,int tl,int tr,int d){
        if(tr<l || r<tl) return {0,{inf,-inf}};
        if(tl<=l && r<=tr){
            int sz=(int)tree[id].size();
            int pos=lower_bound(tree[id].begin(),tree[id].end(),mpp(d,mpp(0,0)))-tree[id].begin();
            if(pos==sz) return {0,{inf,-inf}};
            else return {sz-pos,tree[id][pos].se};
        }
        int mid=(l+r)>>1;
        piii a=query(l,mid,id<<1,tl,tr,d),b=query(mid+1,r,id<<1|1,tl,tr,d);
        return {a.fi+b.fi,{min(a.se.fi,b.se.fi),max(a.se.se,b.se.se)}};
    }
}

void init(int _N, std::vector<int> _H){
    N=_N;H=_H;
    for(int i=0;i<N;i++) mn[i]=inf;
    ST::build(0,N-1,1);
    vector<int> v;
    for(int i=0;i<N;i++){
        while(!v.empty() && H[v.back()]>H[i]) v.pop_back();
        mn[i]=min(mn[i],ST::query(0,N-1,1,(v.empty()?0:v.back()+1),i).mx);
        v.push_back(i);
    }
    v.clear();
    for(int i=N-1;i>=0;i--){
        while(!v.empty() && H[v.back()]>H[i]) v.pop_back();
        mn[i]=min(mn[i],ST::query(0,N-1,1,i,(v.empty()?N-1:v.back()-1)).mx);
        v.push_back(i);
    }
    for(int i=0;i<N;i++){
        mn[i]-=H[i];
        //cout << i << ' ' << mn[i] << '\n';
    }
    ST2::build(0,N-1,1);
}

int max_towers(int L, int R, int D){
    int lt=N,rt=-1;
    int l=L,r=R;
    while(l<=r){
        int mid=(l+r)>>1;
        if(ST::query(0,N-1,1,L,mid).rv>=D) lt=mid,r=mid-1;
        else l=mid+1;
    }
    l=L;r=R;
    while(l<=r){
        int mid=(l+r)>>1;
        if(ST::query(0,N-1,1,mid,R).lv>=D) rt=mid,l=mid+1;
        else r=mid-1;
    }
    //cout << lt << ' ' << rt << '\n';
    auto [cnt,p]=ST2::query(0,N-1,1,L,R,D);
    if(p.fi==inf){
        if(lt<=rt) return 2;
        else return 1;
    }
    if(lt<=p.fi && ST::query(0,N-1,1,lt,p.fi).mx>=H[p.fi]+D) cnt++;
    if(p.se<=rt && ST::query(0,N-1,1,p.se,rt).mx>=H[p.se]+D) cnt++;
    return cnt;
    return 0;
}
