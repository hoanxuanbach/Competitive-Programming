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
#define ll long long
#define ld long double
#define pii pair<int,int>
#define piii pair<int,pii>
#define mpp make_pair
#define fi first
#define se second
const ll inf=1e18;
const int mod=998244353;
const int maxn=200005;
int B,D;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=20;
const int maxa=1000000;
const int root=3;
const int base=101;
const int S=3;
 
int n,q;
vector<pii> edge[maxn];
ll dd[maxn];
int c[maxn],dep[maxn],par[maxn],jmp[maxn];
int Min[2*maxn][maxl],lg2[2*maxn],P[maxn],pos;
int L[maxn],R[maxn],T;
vector<int> ord;
 
void dfs(int u,int p){
    ord.push_back(u);par[u]=p;
    dep[u]=dep[p]+1;L[u]=++T;
    Min[++pos][0]=u;P[u]=pos;
    if(dep[u]%D==1) jmp[u]=u;
    else jmp[u]=jmp[p];
    //cout << "jmp " << u << ' ' << jmp[u] << '\n';
    for(auto [v,w]:edge[u]){
        if(v==p) continue;
        dd[v]=dd[u]+w;
        dfs(v,u);
        Min[++pos][0]=u;
    }
    for(int i=0;i<(int)edge[u].size();i++){
        if(edge[u][i].fi==p){
            edge[u].erase(edge[u].begin()+i);
            break;
        }
    }
    R[u]=T;
}
 
bool anc(int u,int v){
    return L[v]>=L[u] && L[v]<=R[u];
}
int cmp(int u,int v){
    return (L[u]<L[v]?u:v);
}
 
int lca(int u,int v){
    u=P[u];v=P[v];
    if(u>v) swap(u,v);
    int p=lg2[v-u+1];
    return cmp(Min[u][p],Min[v-(1<<p)+1][p]);
}
 
ll dist(int u,int v){
    return dd[u]+dd[v]-2*dd[lca(u,v)];
}
 
struct query{
    int op;
    int u,v,t,k;
}qq[maxn];
bool cn[maxn];
 
struct node{
    ll val[3];
    node(){
        for(int i=0;i<S;i++) val[i]=-inf;
    }
    void del(ll x){
        for(int i=0;i<S;i++) if(val[i]!=-inf) val[i]-=x;
    }
    void add(ll x){
        for(int i=0;i<S;i++) if(x>val[i]) swap(x,val[i]);
    }
};
node mid;
void merge(node &a,node &b){
    int pa=0,pb=0;
    for(int i=0;i<S;i++){
        if(a.val[pa]>b.val[pb]) mid.val[i]=a.val[pa++];
        else mid.val[i]=b.val[pb++];
    }
    swap(a,mid);
}
 
node all[maxn][2],pp[maxn][2],ff[maxn][2];
vector<int> cur;
node cc[2];
 
void cal1(int u){
    for(int i=0;i<=1;i++){
        all[u][i]=node();
        pp[u][i]=node();
    }
    //for(auto &[v,w]:edge[u]) if(v!=p) dfs1(v,u);
    cc[0]=cc[1]=node();
    for(auto &[v,w]:edge[u]){
        for(int i=0;i<=1;i++){
            merge(pp[v][i],cc[i]);
            merge(all[u][i],all[v][i]);
            merge(cc[i],all[v][i]);
        }
    }
    //cout << "dfs1 " << u << ' ' << cn[u] << '\n';
    if(!cn[u]) all[u][c[u]].add(dd[u]);
    else cur.push_back(u);
    cc[0]=cc[1]=node();
    for(int i=(int)edge[u].size()-1;i>=0;i--){
        int v=edge[u][i].fi;
        if(!cn[u]) pp[v][c[u]].add(dd[u]);
        for(int j=0;j<=1;j++){
            merge(pp[v][j],cc[j]);
            pp[v][j].del(2*dd[u]);
            merge(cc[j],all[v][j]);
            //cout << "pp " << v << ' ' << j << ' ' << pp[v][j].val[0] << ' ' << pp[v][j].val[1] << '\n';
        }
    }
    //cout << "pp u:" << u << ' ' << pp[u][0].val[0] << ' ' << pp[u][1].val[1] << '\n';
}
void cal2(int u){
    int p=par[u];
    ff[u][0]=pp[u][0];
    ff[u][1]=pp[u][1];
    if(jmp[u]!=u){
        merge(ff[u][0],ff[p][0]);
        merge(ff[u][1],ff[p][1]);
    }
    //for(auto &[v,w]:edge[u]) if(v!=p) dfs2(v,u);
}
void solve(){
    cin >> n >> q;
    B=max(1,n/30);D=sqrt(n)+1;
    for(int i=1;i<=n;i++) cin >> c[i];
    for(int i=1;i<n;i++){
        int u,v,w;cin >> u >> v >> w;
        edge[u].push_back({v,w});
        edge[v].push_back({u,w});
    }
    dfs(1,0);
    for(int i=2;i<=pos;i++) lg2[i]=lg2[i/2]+1;
    for(int i=1;i<20;i++){
        for(int j=1;j<=(pos-(1<<i)+1);j++) Min[j][i]=cmp(Min[j][i-1],Min[j+(1<<(i-1))][i-1]);
    }
 
    for(int i=1;i<=q;i++){
        cin >> qq[i].op;
        if(qq[i].op==1) cin >> qq[i].u;
        else cin >> qq[i].u >> qq[i].v >> qq[i].t >> qq[i].k;
    }
    //cout << dist(4,2) << '\n';
    for(int i=1;i<=q;i+=B){
        cur.clear();
        for(int j=i;j<=min(i+B-1,q);j++) if(qq[j].op==1) cn[qq[j].u]=true;
        for(int j=n-1;j>=0;j--) cal1(ord[j]);
        for(int u:ord) cal2(u);
        for(int j=i;j<=min(i+B-1,q);j++){
            if(qq[j].op==1){
                int u=qq[j].u;
                c[u]^=1;
            }
            else{
                int u=qq[j].u,v=qq[j].v,t=qq[j].t,k=qq[j].k;
                node res=all[v][t];res.del(dd[v]);
                for(int x:cur) if(c[x]==t && anc(u,x)) res.add(dist(x,v));
                node cur=node();
                //cout << "val " << res.val[0] << ' ' << res.val[1] << '\n';
                int V=v;
                while(v!=u){
                    //cout << "query " << v << '\n';
                    int x=jmp[v];
                    if(x!=u && anc(u,x)){
                        merge(cur,ff[v][t]);
                        v=par[x];
                    }
                    else{
                        merge(cur,pp[v][t]);
                        v=par[v];
                    }
                }
                //cout << "cur " << cur.val[0] << ' ' << cur.val[1] << '\n';
                cur.del(-dd[V]);
                merge(res,cur);
                for(int i=0;i<k;i++) cout << res.val[i] << ' ';
                cout << '\n';
            }
        }
        for(int j=i;j<=min(i+B-1,q);j++) if(qq[j].op==1) cn[qq[j].u]=false;
    }
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
