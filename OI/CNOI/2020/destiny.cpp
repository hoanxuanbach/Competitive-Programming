#include<bits/stdc++.h>
using namespace std; 
#define int long long
#define pii pair<int,int>
#define piii pair<pii,int> 
#define fi first
#define se second
const int inf = 1e18;
const int mod = 998244353;
const int inv2 = (mod+1)/2;
const int maxn = 5e5+5;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}

int fac[maxn],dfac[maxn],inv[maxn];
void combi(int n){
    fac[0]=1;
    for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;
    dfac[n]=power(fac[n],mod-2);
    for(int i=n;i>=1;i--){
        dfac[i-1]=dfac[i]*i%mod;
        inv[i]=dfac[i]*fac[i-1]%mod;
    }
}
int C(int n,int k){
    return fac[n]*dfac[k]%mod*dfac[n-k]%mod;
}

int T=0;
int lc[40*maxn],rc[40*maxn],sum[40*maxn],lsum[40*maxn],lmul[40*maxn];

void getnew(int id,int k,int d){
    (lmul[id]*=k)%=mod;
    (lsum[id]=lsum[id]*k+d)%=mod;
    (sum[id]=sum[id]*k+d)%=mod;
}

void pushdown(int id){
    if(lmul[id]==1 && lsum[id]==0) return;
    getnew(lc[id],lmul[id],lsum[id]);
    getnew(rc[id],lmul[id],lsum[id]); 
    lmul[id]=1;lsum[id]=0;
}

void update(int l,int r,int id,int x,int k,int d){
    if(l==r){
        getnew(id,k,d);
        return;
    }
    pushdown(id);
    int mid=(l+r)>>1;
	if(x<=mid){
		if(!lc[id]){
            if(!d) return;
            lc[id] = ++T;
        }
		update(l,mid,lc[id],x,k,d);
	}
	else{
		if(!rc[id]){
            if(!d) return;
            rc[id]=++T;
        }
		update(mid+1,r,rc[id],x,k,d);
	}
    sum[id]=(sum[lc[id]]+sum[rc[id]])%mod;
}

int merge(int l,int r,int x,int y,int sx,int sy){
	//cout << "merge " << l << ' ' << r << ' ' << x << ' ' << y << ' ' << sx << ' ' << sy << '\n';
    if(!x && !y) return 0;
    if(!x){
        getnew(y,sx,0);
        return y;
    }
    else if(!y){
        getnew(x,sy,0);
        return x;
    }
    if(l==r){
        sum[x]=(sum[x]*sy+sum[y]*sx+sum[x]*sum[y])%mod;
        return x;
    }
    pushdown(x);pushdown(y);
    int mid=(l+r)>>1;
	//cout << "tree " << x << ' ' << y << ' ' << tree[lc[x]].sum << ' ' << tree[rc[x]].sum << ' ' << tree[lc[y]].sum << ' ' << tree[rc[y]].sum << '\n';
	rc[x]=merge(mid+1,r,rc[x],rc[y],(sx+sum[lc[x]])%mod,(sy+sum[lc[y]])%mod);
    lc[x]=merge(l,mid,lc[x],lc[y],sx,sy);
    sum[x]=(sum[lc[x]]+sum[rc[x]])%mod;
    return x;
}


void solve(){   
    int n;cin >> n;
    vector<vector<int>> G(n+1);
    for(int i=1;i<n;i++){
        int u,v;cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    int D=0;
    vector<int> dep(n+1),mx(n+1);
    function<void(int,int)> pre_dfs = [&](int u,int p){
        dep[u]=dep[p]+1;
        D=max(D,dep[u]);
        for(int v:G[u]){
            if(v==p) continue;
            pre_dfs(v,u);
        }
    };
    pre_dfs(1,0);

    int m;cin >> m;
    for(int i=0;i<m;i++){
        int u,v;cin >> u >> v;
        if(dep[u]<dep[v]) swap(u,v);
        mx[u]=max(mx[u],dep[v]);
    }
    
    vector<int> root(n+1);
    function<void(int,int)> dfs = [&](int u,int p){
        root[u]=++T;
        update(0,D,root[u],mx[u],0,1);
        for(int v:G[u]){
            if(v==p) continue;
            dfs(v,u);
			//cout << "start merge " << u << ' ' << v << ' ' << tree[root[u]].sum << ' ' << tree[root[v]].sum << '\n';
            root[u]=merge(0,D,root[u],root[v],0,0);
        }
        int val=sum[root[u]];
        update(0,D,root[u],dep[p],0,0);
        update(0,D,root[u],0,1,val);
		//cout << u << ' ' << mx[u] << ' ' << tree[root[u]].sum << endl;
    };
    dfs(1,0);
    cout << sum[root[1]] << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}