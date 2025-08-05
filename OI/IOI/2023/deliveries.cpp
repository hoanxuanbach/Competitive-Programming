#include "deliveries.h"
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
#define pii pair<int,int>
#define fi first
#define se second
const int maxn = 1e5+5;

vector<pii> G[maxn];

int N;
int T,L[maxn],R[maxn],cn[maxn],head[maxn];
int sz[maxn],son[maxn],par[maxn];

ll S[maxn],sd[maxn],X[maxn],d[maxn],SW;

void dfs(int u,int p){
	sz[u]=1;par[u]=p;
	sd[u]=sd[p]+d[u];
	for(auto [v,w]:G[u]){
		if(v==p) continue;
		d[v]=w;dfs(v,u);
		sz[u]+=sz[v];
		S[u]+=S[v];
		if(sz[v]>sz[son[u]]) son[u]=v;
	} 
}
void hld_dfs(int u,int p,int t){
	if(!t) head[u]=u;
	else head[u]=head[p];
	L[u]=++T;cn[T]=u;
	cerr << "dfs " << u << ' ' << p << ' ' << head[u] << endl;
	if(son[u]) hld_dfs(son[u],u,1);
	for(auto [v,w]:G[u]) if(v!=p && v!=son[u]) hld_dfs(v,u,0);
	R[u]=T;
}

struct node{
	ll total=0,sd=0,mx=0;
	node(){}
	friend node operator+(node a,node b){
		node res;
		res.mx=max(a.mx,b.mx);
		res.total=a.total+b.total;
		res.sd=a.sd+b.sd;
		return res;
	};
}tree[4*maxn];
ll lazy[4*maxn];

void getnew(int id,ll val){
	lazy[id]+=val;
	tree[id].mx+=val;
	tree[id].total+=val*tree[id].sd;
}
void pushdown(int id){
	if(lazy[id]==0) return;
	getnew(id<<1,lazy[id]);
	getnew(id<<1|1,lazy[id]);
	lazy[id]=0;
}

void build(int l,int r,int id){
	if(l==r){
		int x=cn[l];
		tree[id].mx=S[x];
		tree[id].total=S[x]*d[x];
		tree[id].sd=d[x];
		return;
	}
	int mid=(l+r)>>1;
	build(l,mid,id<<1);build(mid+1,r,id<<1|1);
	tree[id]=tree[id<<1]+tree[id<<1|1];
}

void init(int _N, std::vector<int> U, std::vector<int> V, std::vector<int> W, std::vector<int> _X){
	N=_N;
	for(int i=1;i<=N;i++) S[i]=X[i]=_X[i-1];
	for(int i=0;i<N-1;i++){
		U[i]++;V[i]++;
		G[U[i]].push_back({V[i],W[i]});
		G[V[i]].push_back({U[i],W[i]});
	}
	dfs(1,0);
	SW=S[1]+1;
	hld_dfs(1,0,0);
	build(1,N,1);
	return;
}


void update(int l,int r,int id,int tl,int tr,ll val){
	if(tr<l || r<tl) return;
	if(tl<=l && r<=tr){
		getnew(id,val);
		return;
	}
	pushdown(id);
	int mid=(l+r)>>1;
	update(l,mid,id<<1,tl,tr,val);update(mid+1,r,id<<1|1,tl,tr,val);
	tree[id]=tree[id<<1]+tree[id<<1|1];
}
void hld_update(int u,ll val){
	while(u){
		int v=head[u];
		update(1,N,1,L[v],L[u],val);
		u=par[v];
	}
}

int query_mx(int l,int r,int id,ll val){
	if(l==r) return l;
	pushdown(id);
	int mid=(l+r)>>1;
	if(tree[id<<1|1].mx>=val) return query_mx(mid+1,r,id<<1|1,val);
	else return query_mx(l,mid,id<<1,val);
}

ll query(int l,int r,int id,int tl,int tr){
	if(tr<l || r<tl) return 0;
	if(tl<=l && r<=tr) return tree[id].total;
	pushdown(id);
	int mid=(l+r)>>1;
	return query(l,mid,id<<1,tl,tr)+query(mid+1,r,id<<1|1,tl,tr);
}

ll hld_query(int u){
	ll res=0;
	while(u){
		int v=head[u];
		res+=query(1,N,1,L[v],L[u]);
		u=par[v];
	}
	return res;
};

ll max_time(int u, int val){
	u++;
	hld_update(u,val-X[u]);
	SW+=val-X[u];X[u]=val;
	
	if(SW==1) return 0;
	u=cn[query_mx(1,N,1,(SW+1)/2)];

	ll A=hld_query(u);
	ll total=tree[1].total-A;
	total+=SW*sd[u]-A;
	return total*2;
}
