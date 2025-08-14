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
const int maxn = 2e5+5;
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

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}

const int MS = 20*maxn;

int T;
int lc[MS],rc[MS],sum[MS],mul[MS];

int new_node(){
    ++T;mul[T]=1;
    return T;
}
void getnew(int id,int val){
    if(!id) return;
    sum[id]=sum[id]*val%mod;
    mul[id]=mul[id]*val%mod;
}
void pushdown(int id){
    if(mul[id]==1) return;
    getnew(lc[id],mul[id]);
    getnew(rc[id],mul[id]);
    mul[id]=1;
}
int add(int l,int r,int id,int x){
    if(!id) id=new_node();
    if(l==r){
        sum[id]++;
        return id;
    }
    pushdown(id);
    int mid=(l+r)>>1;
    if(x<=mid) lc[id]=add(l,mid,lc[id],x);
    else rc[id]=add(mid+1,r,rc[id],x);
    sum[id]=(sum[lc[id]]+sum[rc[id]])%mod;
    return id;
}
int query(int l,int r,int id,int x){
    if(!id) return 0;
    if(l==r) return sum[id];
    pushdown(id);
    int mid=(l+r)>>1;
    if(x<=mid) return query(l,mid,lc[id],x);
    else return query(mid+1,r,rc[id],x);
}
int merge(int l,int r,int x,int y,int sx,int sy){
    if(!x && !y) return 0;
    if(!x){
        getnew(y,sx);
        return y;
    }
    if(!y){
        getnew(x,sy);
        return x;
    }
    if(l==r){
        sum[x]=(sum[x]*sum[y]+sum[x]*sy+sum[y]*sx)%mod;
        return x;
    }
    pushdown(x);
    pushdown(y);
    int mid=(l+r)>>1;
    lc[x]=merge(l,mid,lc[x],lc[y],sx,sy);
    rc[x]=merge(mid+1,r,rc[x],rc[y],sx,sy);
    sum[x]=(sum[lc[x]]+sum[rc[x]])%mod;
    return x;
}

void solve(){   
    int n,m;cin >> n >> m;
    vector<int> X(n);
    for(int i=1;i<n;i++) cin >> X[i];

    vector<int> h(n+1);
    for(int i=1;i<=m;i++){
        int val=rand_int(1,inf);
        int l,r;cin >> l >> r;
        h[l]^=val;h[r]^=val;
    }
    vector<int> com;
    for(int i=1;i<=n;i++) h[i]^=h[i-1],com.push_back(h[i-1]);
    sort(com.begin(),com.end());
    com.erase(unique(com.begin(),com.end()),com.end());
    for(int i=0;i<n;i++) h[i]=lower_bound(com.begin(),com.end(),h[i])-com.begin()+1;

    int p=1;
    vector<int> lt(2*n),rt(2*n);
    function<int(int,int)> build = [&](int l,int r){
        int id=++T;
        if(l+1==r){
            lt[id]=h[l];
            return id;
        }
        int mid=X[p++];
        lt[id]=build(l,mid);
        rt[id]=build(mid,r);
        return id;
    };
    build(0,n);

    int sz=(int)com.size();
    vector<int> g(2*n),root(2*n);T=0;
    function<void(int)> dfs = [&](int u){
        if(!rt[u]){
            root[u]=new_node();g[u]=1;
            add(1,sz,root[u],lt[u]);
        }
        else{
            int x=lt[u],y=rt[u];
            dfs(x);dfs(y);
            root[u]=merge(1,sz,root[x],root[y],g[x],g[y]);
            g[u]+=(2*g[x]*g[y]+sum[root[u]])%mod;
        }
    };
    dfs(1);
    int res=g[1];
    if(com[0]==0) res=(res+query(1,sz,root[1],1))%mod;
    cout << res << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}