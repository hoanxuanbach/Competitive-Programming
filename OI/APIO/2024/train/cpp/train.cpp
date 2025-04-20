#include "train.h"
#include <bits/stdc++.h>
using namespace std;
using i32 = int;
#define int long long
const int inf = 1e18;
const int B = 1000;
const int D = 350;
const int maxn = 1e5+5;
const int maxs = 105;

struct Sum{
    vector<int> com;
    void add(int x){
        com.push_back(x);
    }
    void build(){
        sort(com.begin(),com.end());
        com.erase(unique(com.begin(),com.end()),com.end());
    }
    int cnt[maxn],total[maxn];
    void update(int x){
        //cout << "update " << x << '\n';
        x=lower_bound(com.begin(),com.end(),x)-com.begin()-1;
        if(x<0) return;
        for(int i=x/D-1;i>=0;i--) total[i]++;
        for(int i=x;i>=(x/D)*D;i--) cnt[i]++;
    }
    int get(int x){
        //cout << "get " << x << '\n';
        return cnt[x]+total[x/D];
    }
}V;

struct Block{
    int sz;
    vector<int> com;
    int tree[4*maxn],lazy[4*maxn];
    void add(int x){
        com.push_back(x);
    }
    void build(){
        sort(com.begin(),com.end());
        com.erase(unique(com.begin(),com.end()),com.end());
        sz=(int)com.size();
        for(int i=0;i<4*sz;i++) tree[i]=inf;
    }
    void update_pos(int l,int r,int id,int x,int val){
        if(l==r){
            tree[id]=min(tree[id],val);
            return;
        }
        int mid=(l+r)>>1;
        if(x<=mid) update_pos(l,mid,id<<1,x,val);
        else update_pos(mid+1,r,id<<1|1,x,val);
        tree[id]=min(tree[id<<1],tree[id<<1|1])+lazy[id];
    }
    void update_val(int l,int r,int id,int x,int val){
        if(x<l) return;
        if(r<=x){
            lazy[id]+=val;
            tree[id]+=val;
            return;
        }
        int mid=(l+r)>>1;
        update_val(l,mid,id<<1,x,val);
        update_val(mid+1,r,id<<1|1,x,val);
        tree[id]=min(tree[id<<1],tree[id<<1|1])+lazy[id];
    }
    int query(int l,int r,int id,int x){
        if(x<l) return inf;
        if(r<=x) return tree[id];
        int mid=(l+r)>>1;
        return min(query(l,mid,id<<1,x),query(mid+1,r,id<<1|1,x))+lazy[id];
    }

    void update_pos(int x,int val){
        x=lower_bound(com.begin(),com.end(),x)-com.begin();
        update_pos(0,sz-1,1,x,val);
    }
    void update_val(int x,int val){
        x=lower_bound(com.begin(),com.end(),x)-com.begin()-1;
        if(x<0) return;
        update_val(0,sz-1,1,x,val);
    }
    int query(int x){
        x=upper_bound(com.begin(),com.end(),x)-com.begin()-1;
        if(x<0) return inf;
        return query(0,sz-1,1,x);
    }
}S[maxs];
int f[maxn],pos[maxn],cnt;
vector<int> g[maxn];

int solve(i32 N, i32 M, i32 W, std::vector<i32> T, std::vector<i32> X, std::vector<i32> Y,
                std::vector<i32> P, std::vector<i32> Q, std::vector<i32> C, std::vector<i32> L,
                std::vector<i32> R) {

    for(int i=0;i<M;i++) f[Y[i]]++;
    for(int i=0;i<N;i++){
        if(f[i]>B) f[i]=++cnt,pos[cnt]=i;
        else f[i]=0;
    }
    for(int i=0;i<M;i++){
        if(f[Y[i]]) S[f[Y[i]]].add(Q[i]);
        V.add(Q[i]);
    }
    V.build();
    for(int i=1;i<=cnt;i++) S[i].build();

    vector<int> ord(M),meal(W),F(M);
    iota(ord.begin(),ord.end(),0);
    iota(meal.begin(),meal.end(),0);
    sort(ord.begin(),ord.end(),[&](int x,int y){return P[x]<P[y];});
    sort(meal.begin(),meal.end(),[&](int x,int y){return R[x]<R[y];});
    for(int i=0;i<M;i++) F[i]=lower_bound(V.com.begin(),V.com.end(),Q[i])-V.com.begin();

    int p=0;
    vector<int> dp(M,inf);
    int res=inf;
    auto add = [&](int id){
        //cout << "add " << id << '\n';
        V.update(L[id]);
        for(int i=1;i<=cnt;i++) S[i].update_val(L[id],T[pos[i]]);
    };
    for(int i:ord){
        while(p<W && R[meal[p]]<P[i]) add(meal[p++]);
        //cout << '*' << i << ' ' << p << '\n';
        if(!X[i]) dp[i]=1LL*p*T[X[i]];
        if(f[X[i]]) dp[i]=min(dp[i],S[f[X[i]]].query(P[i]));
        else{
            for(int j:g[X[i]]) if(Q[j]<=P[i]) dp[i]=min(dp[i],dp[j]+1LL*V.get(F[j])*T[X[i]]);
        }
        dp[i]+=C[i];
        if(f[Y[i]]) S[f[Y[i]]].update_pos(Q[i],dp[i]);
        else g[Y[i]].push_back(i);
    }

    sort(ord.begin(),ord.end(),[&](int x,int y){return Q[x]>Q[y];});
    sort(meal.begin(),meal.end(),[&](int x,int y){return L[x]>L[y];});
    p=0;
    for(int i:ord){
        while(p<W && L[meal[p]]>Q[i]) p++;
        if(Y[i]==N-1) res=min(res,dp[i]+1LL*p*T[N-1]);
    }
    return (res==inf?-1:res);
}
#undef int
