// Judges with GCC >= 12 only needs Ofast
// #pragma GCC optimize("O3,no-stack-protector,fast-math,unroll-loops,tree-vectorize")
// MLE optimization
// #pragma GCC optimize("conserve-stack")
// Old judges
// #pragma GCC target("sse4.2,popcnt,lzcnt,abm,mmx,fma,bmi,bmi2")
// New judges. Test with assert(__builtin_cpu_supports("avx2"));
// #pragma GCC target("avx2,popcnt,lzcnt,abm,bmi,bmi2,fma,tune=native")
// Atcoder
// #pragma GCC target("avx2,popcnt,lzcnt,abm,bmi,bmi2,fma")
/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;
- insert(x),erase(x)
- find_by_order(k): return iterator to the k-th smallest element
- order_of_key(x): the number of elements that are strictly smaller
*/
#include<bits/stdc++.h>
using namespace std;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_real_distribution<> pp(0.0,1.0);
//#define int long long
#define ld long double
#define pii pair<int,int>
#define piii pair<pii,int>
#define mpp make_pair
#define fi first
#define se second
//const int inf=1e18;
const int mod=1e9+7;
const int maxn=200005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=500005;
const int maxl=20;
const int maxa=4000005;
const int root=3;
/*
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
const int iroot=power(3,mod-2);
*/
const int base=101;
int c[256];
struct BIT{
    int n,bit[maxn];
    BIT(){}
    void init(int N){n=N;}
    void update(int x,int val){
        for(int i=x;i<=n;i+=(i&(-i))) bit[i]+=val;
    }
    int query(int x){
        int res=0;
        for(int i=x;i>=1;i-=(i&(-i))) res+=bit[i];
        return res;
    }
    int query_range(int l,int r){
        return query(r)-query(l-1);
    }
}bit;
struct trie{
    int nxt[maxa][4],leaf[maxa],L[maxa],R[maxa];
    int num,pos;
    vector<int> edge[maxn];
    trie(){}
    int add(string s){
        int u=0;
        for(char ch:s){
            int a=c[ch];
            if(nxt[u][a]==0) nxt[u][a]=++num;
            u=nxt[u][a];
        }
        leaf[u]=1;
        return u;
    }
    void dfs(int u,int d){
        if(leaf[u]){
            L[u]=++pos;
            edge[d].push_back(pos);d=pos;
        }
        for(int i=0;i<4;i++){
            if(nxt[u][i]) dfs(nxt[u][i],d);
        }
        if(leaf[u]) R[u]=pos;
    }
}sf,pf;
vector<pii> add[maxn];
int ans[maxn],child[maxn],son[maxn];
void dfs_sz(int u){
    child[u]=1;
    for(int v:pf.edge[u]){
        dfs_sz(v);child[u]+=child[v];
        if(child[v]>child[son[u]]) son[u]=v;
    }
}
void cal(int u,int val){
    for(auto &[y,id]:add[u]){
        if(id==0) bit.update(y,val);
    }
    for(int v:pf.edge[u]) cal(v,val);
}
void dfs(int u,int t){
    for(int v:pf.edge[u]){
        if(v==son[u]) continue;
        dfs(v,1);
    }
    if(son[u]) dfs(son[u],0);
    for(int v:pf.edge[u]){
        if(v==son[u]) continue;
        cal(v,1);
    }
    for(auto &[y,id]:add[u]){
        if(id==0) bit.update(y,1);
        else ans[id]=bit.query_range(sf.L[y],sf.R[y]);
    }
    if(t) cal(u,-1);
}
void solve(){
    vector<pii> a,b;
    c['A']=0;c['G']=1;c['U']=2;c['C']=3;
    int n,m;cin >> n >> m;
    for(int i=1;i<=n;i++){
        string s;cin >> s;
        int x=pf.add(s);
        reverse(s.begin(),s.end());
        int y=sf.add(s);
        a.push_back({x,y});
    }
    for(int i=1;i<=m;i++){
        string p,q;cin >> p >> q;
        reverse(q.begin(),q.end());
        b.push_back({pf.add(p),sf.add(q)});
    }
    pf.dfs(0,0);sf.dfs(0,0);
    for(auto &[x,y]:a) add[pf.L[x]].push_back({sf.L[y],0});
    for(int i=1;i<=m;i++){
        int x=b[i-1].fi,y=b[i-1].se;
        add[pf.L[x]].push_back({y,i});
    }
    bit.init(sf.pos);
    dfs_sz(0);dfs(0,0);
    for(int i=1;i<=m;i++) cout << ans[i] << '\n';
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
