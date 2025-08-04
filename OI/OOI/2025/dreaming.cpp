#include<bits/stdc++.h>
using namespace std;
/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;
*/
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_real_distribution<> pp(0.0,1.0);
#define int long long
#define ld long double
#define pii pair<int,int>
#define piii pair<int,pii>
#define mpp make_pair
#define fi first
#define se second
const long long inf=1e18;
const int mod=998244353;
//int mod=998244353;
const int maxn=300005;
const int B=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=25;
const int maxa=1000000;
const int root=3;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
const int iroot=power(3,mod-2);
const int base=101;

int rand(int l,int r){
    return l+rng()%(r-l+1);
}

int fac[maxn],dfac[maxn],inv[maxn],p2[maxn];

void combi(int n){
    fac[0]=p2[0]=1;
    for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod,p2[i]=p2[i-1]*2%mod;
    dfac[n]=power(fac[n],mod-2);
    for(int i=n;i>=1;i--){
        dfac[i-1]=dfac[i]*i%mod;
        inv[i]=dfac[i]*fac[i-1]%mod;
    }
}

int C(int n,int k){
    if(k>n || k<0 || n<0) return 0;
    return fac[n]*dfac[k]%mod*dfac[n-k]%mod;
}

void solve(){
    int n,q;cin >> n >> q;
    vector<vector<int>> edge(n+1);
    vector<int> s(n+1),f(n+1),ans(n+1);

    vector<int> par(n+1);
    for(int i=2;i<=n;i++){
        cin >> par[i];
        edge[par[i]].push_back(i);
    }
    for(int i=1;i<=n;i++) cin >> s[i],f[s[i]]=i;

    set<int> ss;
    for(int v:edge[1]) ss.insert(s[v]);

    vector<int> order;
    order.push_back(1);
    while(!ss.empty()){
        int u=f[*ss.rbegin()];
        ss.erase(s[u]);
        order.push_back(u);
        for(int v:edge[u]) ss.insert(s[v]);
        //cout << u << '\n';
    }
    
    int T=0;
    vector<int> L(n+1),R(n+1),head(n+1),child(n+1);

    function<void(int)> pre_dfs = [&](int u){
        child[u]=1;
        for(int v:edge[u]) pre_dfs(v),child[u]+=child[v];
    };
    pre_dfs(1);

    function<void(int,int)> dfs = [&](int u,int t){
        if(t) head[u]=head[par[u]];
        else head[u]=u;
        L[u]=++T;

        int son=0;
        for(int v:edge[u]) if(child[v]>child[son]) son=v;
        
        if(son) dfs(son,1);
        for(int v:edge[u]) if(v!=son) dfs(v,0);

        R[u]=T;
    };
    dfs(1,0);

    vector<int> tree(4*n),lazy(4*n);
    function<void(int,int,int,int,int)> update = [&](int l,int r,int id,int tl,int tr){
        if(tr<l || r<tl) return;
        if(tl<=l && r<=tr){
            lazy[id]++;
            tree[id]++;
            return;
        }
        int mid=(l+r)>>1;
        update(l,mid,id<<1,tl,tr);update(mid+1,r,id<<1|1,tl,tr);
        tree[id]=max(tree[id<<1],tree[id<<1|1])+lazy[id];
    };

    function<int(int,int,int,int,int)> query = [&](int l,int r,int id,int tl,int tr){
        if(tr<l || r<tl) return -inf;
        if(tl<=l && r<=tr) return tree[id];
        int mid=(l+r)>>1;
        return max(query(l,mid,id<<1,tl,tr),query(mid+1,r,id<<1|1,tl,tr))+lazy[id];
    };

    auto hld_update = [&](int u){
        while(u){
            int v=head[u];
            update(1,n,1,L[v],L[u]);
            u=par[v];
        }
    };

    auto hld_query =  [&](int u){
        int res=0;
        if(L[u]<n) res=query(1,n,1,L[u]+1,n);
        while(u){
            int v=head[u];u=par[v];
            if(u && L[u]+1<L[v]) res=max(res,query(1,n,1,L[u]+1,L[v]-1));
        }
        return res;
    };

    for(int i=0;i<n;i++){
        hld_update(order[i]);
        ans[order[i]]=i-hld_query(order[i]);
    }

    for(int i=1;i<=q;i++){
        int v;cin >> v;
        cout << ans[v] << ' ';
    }
    cout << '\n';
}   

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
