#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 998244353;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
 
const int maxn = 5e5+5;
const int inf = 1e18;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}

int n,d[maxn];
vector<int> g[maxn];
int fac[maxn],dfac[maxn];

int L[maxn],R[maxn],cn[maxn],T;

int f[maxn],lt[maxn],rt[maxn];
set<int> ss;

void dfs2(int u){
    auto it=ss.upper_bound(f[u]);
    rt[u]=(it==ss.end()?n:*it-1);
    if(it!=ss.begin()){
        it=prev(it);
        lt[u]=*it+1;
    }
    else lt[u]=1;
    ss.insert(f[u]);
    for(int v:g[u]) dfs2(v);
    ss.erase(f[u]);
}

void dfs(int u){
    L[u]=++T;cn[T]=u;
    for(int v:g[u]) dfs(v);
    R[u]=T;
}

int cnttest=0;

void solve(){
    cnttest++;

    cin >> n;
    for(int i=1;i<=n;i++) g[i].clear(),d[i]=1;
    for(int i=2;i<=n;i++){
        int x;cin >> x;
        d[i]=d[x]+1;
        g[x].push_back(i);
    }
    vector<int> a(n+1);
    for(int i=1;i<=n;i++) cin >> a[i];


    fac[0]=dfac[0]=1;
    for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;
    dfac[n]=power(fac[n],mod-2);
    for(int i=n;i>=1;i--) dfac[i-1]=dfac[i]*i%mod;

    T=0;
    dfs(1);

    vector<int> lazy(4*n);
    vector<pii> tree(4*n);
    function<void(int,int,int)> build = [&](int l,int r,int id){
        if(l==r){
            tree[id]={a[cn[l]],cn[l]};
            return;
        }
        int mid=(l+r)>>1;
        build(l,mid,id<<1);build(mid+1,r,id<<1|1);
        tree[id]=min(tree[id<<1],tree[id<<1|1]);
    };
    build(1,n,1);

    function<void(int,int,int,int)> change = [&](int l,int r,int id,int x){
        if(l==r){
            tree[id]={inf,-1};
            return;
        }
        int mid=(l+r)>>1;
        if(x<=mid) change(l,mid,id<<1,x);
        else change(mid+1,r,id<<1|1,x);
        tree[id]=min(tree[id<<1],tree[id<<1|1]);
        tree[id].first-=lazy[id];
    };
    function<void(int,int,int,int,int)> update = [&](int l,int r,int id,int tl,int tr){
        if(tr<l || r<tl) return;
        if(tl<=l && r<=tr){
            tree[id].first--;
            lazy[id]++;
            return;
        }  
        int mid=(l+r)>>1;
        update(l,mid,id<<1,tl,tr);update(mid+1,r,id<<1|1,tl,tr);
        tree[id]=min(tree[id<<1],tree[id<<1|1]);
        tree[id].first-=lazy[id];
    };


    set<pii> S;
    while(tree[1].first==0){
        int x=tree[1].second;
        S.insert({d[x],x});
        change(1,n,1,L[x]);
    }
    vector<int> ord;
    while(!S.empty()){
        pii x=*S.rbegin();S.erase(x);
        auto [dd,u]=x;
        ord.push_back(u);
        update(1,n,1,L[u],R[u]);
        while(tree[1].first==0){
            int v=tree[1].second;
            S.insert({d[v],v});
            change(1,n,1,L[v]);
        }
    }

    int res=fac[n];
    for(int i=0;i<n;i++) f[ord[i]]=i+1;
    dfs2(1);ss.clear();

    vector<int> sl(n+1),sr(n+1);
    vector<vector<int>> qq(n+1);
    for(int i=1;i<=n;i++){
        qq[R[i]].push_back(i);
        qq[L[i]-1].push_back(-i);
    }

    vector<int> bit(n+1);
    auto fix = [&](int x){
        for(int i=x;i<=n;i+=(i&(-i))) bit[i]++;
    };
    auto query = [&](int x){
        int cnt=0;
        for(int i=x;i>=1;i-=(i&(-i))) cnt+=bit[i];
        return cnt;
    };
    for(int i=1;i<=n;i++){
        fix(f[cn[i]]);
        for(int u:qq[i]){
            int val=1;
            if(u<0) val=-1,u=-u;
            //lt[u]->f[u]-1
            int cl=0,cr=0;
            if(lt[u]<f[u]) cl=query(f[u]-1)-query(lt[u]-1);
            if(f[u]<rt[u]) cr=query(rt[u])-query(f[u]);
            sl[u]+=val*cl;
            sr[u]+=val*cr;
        }
    }

    for(int i=1;i<=n;i++) res=res*dfac[sl[i]+sr[i]+1]%mod*fac[sl[i]]%mod*fac[sr[i]]%mod;

    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}
