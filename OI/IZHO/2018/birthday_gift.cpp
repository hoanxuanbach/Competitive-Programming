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
#define ld long double
#define pii pair<int,int>
#define piii pair<pii,int>
#define mpp make_pair
#define fi first
#define se second
const int mod=998244353;
const int maxn=200005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=20;
const int maxa=1000000;
const int root=3;
const int base=101;

namespace Tree{
    vector<vector<int>> edge,Min;
    vector<int> lg2,dep,L,R;
    int pos;
    int cmp(int u,int v){
        return (dep[u]<dep[v]?u:v);
    }
    int lca(int u,int v){
        u=L[u];v=L[v];
        if(u>v) swap(u,v);
        int p=lg2[v-u+1];
        return cmp(Min[u][p],Min[v-(1<<p)+1][p]);
    }
    int dist(int u,int v){
        return dep[u]+dep[v]-2*dep[lca(u,v)];
    }
    void dfs(int u,int p){
        L[u]=++pos;Min[pos][0]=u;
        dep[u]=dep[p]+1;
        for(int v:edge[u]){
            if(v==p) continue;
            dfs(v,u);Min[++pos][0]=u;
        }
        R[u]=pos;
    }
    void init(int n){
        lg2.assign(2*n+1,0);
        dep.assign(n+1,0);
        L.assign(n+1,0);
        R.assign(n+1,0);
        edge.resize(n+1);
        Min.assign(2*n+1,vector<int>(maxl,0));
    }
    void build(int n){
        init(n);
        for(int i=1;i<n;i++){
            int u,v;cin >> u >> v;
            edge[u].push_back(v);
            edge[v].push_back(u);
        }
        dfs(1,0);
        for(int i=2;i<=pos;i++) lg2[i]=lg2[i/2]+1;
        for(int i=1;i<20;i++){
            for(int j=1;j<=(pos-(1<<i)+1);j++) Min[j][i]=cmp(Min[j][i-1],Min[j+(1<<(i-1))][i-1]);
        }
    }
}

int n,m,q,a[maxn];
set<pii> s[maxn];

void solve(){
    cin >> n >> m >> q;
    Tree::build(n);
    for(int i=1;i<=m;i++){
        cin >> a[i];
        s[a[i]].insert({i,0});
        if(i>=2) s[Tree::lca(a[i-1],a[i])].insert({i-1,1});
    }
    for(int i=1;i<=q;i++){
        int id,l,r,v;cin >> id;
        if(id==1){
            cin >> l >> v;
            s[a[l]].erase({l,0});
            if(l>=2) s[Tree::lca(a[l-1],a[l])].erase({l-1,1});
            if(l<m) s[Tree::lca(a[l],a[l+1])].erase({l,1});
            a[l]=v;
            s[a[l]].insert({l,0});
            if(l>=2) s[Tree::lca(a[l-1],a[l])].insert({l-1,1});
            if(l<m) s[Tree::lca(a[l],a[l+1])].insert({l,1});
        }
        else{
            cin >> l >> r >> v;
            auto it=s[v].lower_bound({l,0});
            if(it==s[v].end()) cout << -1 << ' ' << -1 << '\n';
            else if(it->se==0){
                if(it->fi<=r) cout << it->fi << ' ' << it->fi << '\n';
                else cout << -1 << ' ' << -1 << '\n';
            }
            else{
                if(it->fi+1<=r) cout << it->fi << ' ' << it->fi+1 << '\n';
                else cout << -1 << ' ' << -1 << '\n';
            }
        }
    }
}
/*
5 4 4
1 2
3 1
3 4
5 3
4 5 2 3
2 1 3 1
1 3 5
2 3 4 5
2 1 3 1
*/
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
