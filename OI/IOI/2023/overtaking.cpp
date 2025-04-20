#include "overtaking.h"

#include<bits/stdc++.h>
using namespace std;
const long long inf=LLONG_MAX;
const int maxn=1e3+5;
#define pii pair<int,int>
#define fi first
#define se second

struct bus{
    long long s,t;
    int id;
    bool operator<(bus o){
        if(s!=o.s) return s<o.s;
        else return t<o.t;
    }
};

int M,N;
long long X,L;
vector<long long> T,S,W;

bus B[maxn][maxn];
long long res[maxn][maxn];

namespace Segtree{
    int n;
    vector<pii> tree;
    vector<long long> com;
    void add(long long x){
        com.push_back(x);
    }
    void build(){
        sort(com.begin(),com.end());
        com.erase(unique(com.begin(),com.end()),com.end());
        n=(int)com.size();
        tree.assign(4*n,make_pair(M,0));
    }
    void update(int l,int r,int id,int tl,int tr,pii x){
        if(tr<l || r<tl) return;
        if(tl<=l && r<=tr) return tree[id]=min(tree[id],x),void();
        int mid=(l+r)>>1;
        update(l,mid,id<<1,tl,tr,x);update(mid+1,r,id<<1|1,tl,tr,x);
    }
    void update(long long l,long long r,pii x){
        if(l>r) return;
        int pl=upper_bound(com.begin(),com.end(),l)-com.begin();
        int pr=upper_bound(com.begin(),com.end(),r)-com.begin();
        update(1,n,1,pl,pr,x);
    }
    pii query(int l,int r,int id,int x){
        if(l==r) return tree[id];
        int mid=(l+r)>>1;
        pii res=tree[id];
        if(x<=mid) res=min(res,query(l,mid,id<<1,x));
        else res=min(res,query(mid+1,r,id<<1|1,x));
        return res;
    }
    pii query(long long x){
        int px=upper_bound(com.begin(),com.end(),x)-com.begin();
        return query(1,n,1,px);
    }
}

void init(int l, int n, vector<long long> st, vector<int> w, int x, int m, vector<int> s)
{
    L=l;N=n;X=x;M=m;T=st;
    W.resize(N);S.resize(M);
    for(int i=0;i<N;i++) W[i]=w[i];
    for(int i=0;i<M;i++) S[i]=s[i];

    for(int i=0;i<N;i++) B[0][i]={0,T[i],i};
    for(int i=1;i<M;i++){
        for(int j=0;j<N;j++){
            auto [ss,tt,id]=B[i-1][j];
            B[i][j]={tt,tt+(S[i]-S[i-1])*W[id],id};
        }
        sort(B[i],B[i]+N);
        for(int j=1;j<N;j++) B[i][j].t=max(B[i][j].t,B[i][j-1].t);
        for(int j=0;j<N;j++){
            Segtree::add(B[i][j].s-X*S[i-1]+1);
            Segtree::add(B[i][j].t-X*S[i]);
        }
    }
    Segtree::add(-inf);
    Segtree::build();
    for(int i=M-1;i>=1;i--){
        for(int j=0;j<N;j++){
            pii pos=Segtree::query(B[i][j].t-X*S[i]);pos.se=-pos.se;
            if(pos.fi==M) res[i][j]=B[i][j].t+X*(L-S[i]);
            else res[i][j]=res[pos.fi][pos.se];
            //cout << res[i][j] << ' ';
        }
        for(int j=0;j<N;j++) Segtree::update(B[i][j].s-X*S[i-1]+1,B[i][j].t-X*S[i]-1,{i,-j});
        //cout << '\n';
    }
}

long long arrival_time(long long cur)
{
    pii pos=Segtree::query(cur);pos.se=-pos.se;
    //cout << pos.fi << ' ' << pos.se << ' ' << B[pos.fi][pos.se].id << '\n';
    if(pos.fi==M) return cur+X*L;
    else return res[pos.fi][pos.se];
}
