#include "roads.h"
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int,int>
#define fi first
#define se second
const ll inf = 1e18;

struct Segtree{
    int sz;
    vector<ll> tree;
    vector<int> cnt;
    vector<pii> com;
    Segtree(){}
    void add(pii val){
        com.push_back(val);
    }
    void build(int l,int r,int id){
        if(l==r){
            tree[id]=com[l-1].fi;
            cnt[id]=1;
            return;
        }
        int mid=(l+r)>>1;
        build(l,mid,id<<1);build(mid+1,r,id<<1|1);
        tree[id]=tree[id<<1]+tree[id<<1|1];
        cnt[id]=cnt[id<<1]+cnt[id<<1|1];
    }
    void update(int l,int r,int id,int p){
        if(l==r){
            tree[id]=cnt[id]=0;
            return;
        }
        int mid=(l+r)>>1;
        if(p<=mid) update(l,mid,id<<1,p);
        else update(mid+1,r,id<<1|1,p);
        tree[id]=tree[id<<1]+tree[id<<1|1];
        cnt[id]=cnt[id<<1]+cnt[id<<1|1];
    }
    ll query(int l,int r,int id,int k){
        if(l==r) return (k>=1)*tree[id];
        int mid=(l+r)>>1;
        if(cnt[id<<1]<k) return tree[id<<1]+query(mid+1,r,id<<1|1,k-cnt[id<<1]);
        else return query(l,mid,id<<1,k);
    }
    void build(){
        sort(com.begin(),com.end(),greater<pii>());
        sz=(int)com.size();
        tree.assign(4*sz,0);
        cnt.assign(4*sz,0);
        build(1,sz,1);
    }
    void del(pii x){
        int pos=lower_bound(com.begin(),com.end(),x,greater<pii>())-com.begin()+1;
        update(1,sz,1,pos);
    }
    ll query(int k){
        return query(1,sz,1,k);
    }
};

std::vector<ll> minimum_closure_costs(int N, vector<int> U,
                                             vector<int> V,
                                             vector<int> W) {
    vector<ll> res(N),total(N);
    vector<vector<pii>> edge(N),adj(N);
    vector<vector<int>> pos(N);
    vector<Segtree> ST(N);
    vector<bool> add(N,false),vis(N,false);

    for(int i=0;i<N-1;i++){
        edge[U[i]].push_back({V[i],W[i]});
        edge[V[i]].push_back({U[i],W[i]});
    }
    for(int i=0;i<N;i++){
        pos[(int)edge[i].size()].push_back(i);
        for(auto [v,w]:edge[i]) ST[i].add({w,v}),total[i]+=w;
        ST[i].build();
    }
    vector<int> cc;
    vector<array<ll,2>> dp(N);
    for(int k=N-1;k>=0;k--){
        for(int u:pos[k]){
            cc.push_back(u);
            for(auto [v,w]:edge[u]){
                total[v]-=w;
                ST[v].del({w,u});
                if(add[v]){
                    adj[u].push_back({v,w});
                    adj[v].push_back({u,w});
                }
            }
            add[u]=true;
        }
        function<void(int)> dfs = [&](int u){
            int C=0;vis[u]=true;
            dp[u][0]=dp[u][1]=inf;
            ll num=total[u];
            vector<ll> val;
            for(auto [v,w]:adj[u]){
                if(vis[v]){C=w;continue;}
                dfs(v);num+=dp[v][0];
                if(dp[v][0]>dp[v][1]) val.push_back(dp[v][0]-dp[v][1]);
            }
            sort(val.begin(),val.end(),greater<ll>());
            ll cur=num;
            for(int i=0;i<=(int)val.size();i++){
                if(i) cur-=val[i-1];
                if(i<=k) dp[u][0]=min(dp[u][0],cur-ST[u].query(k-i)+C);
                if(i<k) dp[u][1]=min(dp[u][1],cur-ST[u].query(k-1-i));
            }
        };
        for(int u:cc) vis[u]=false;
        for(int u:cc) if(!vis[u]){
            dfs(u);
            res[k]+=min(dp[u][0],dp[u][1]);
        }
    }
    return res;
}
