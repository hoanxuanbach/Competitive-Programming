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

#pragma GCC optimize("Ofast,unroll-loops")

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
    int dep[maxn],par[maxn][maxl];
    vector<int> edge[maxn];

    int jmp(int u,int d){
        for(int i=0;i<18;i++) if(d&(1<<i)) u=par[u][i];
        return u;
    }
    int lca(int u,int v){
        if(dep[u]>dep[v]) swap(u,v);
        v=jmp(v,dep[v]-dep[u]);
        if(u==v) return u;
        for(int i=17;i>=0;i--){
            if(par[u][i]!=par[v][i]){
                u=par[u][i];
                v=par[v][i];
            }
        }
        return par[u][0];
    }
    void dfs(int u,int p){
        dep[u]=dep[p]+1;par[u][0]=p;
        for(int i=1;i<18;i++) par[u][i]=par[par[u][i-1]][i-1];
        for(int v:edge[u]){
            if(v==p) continue;
            dfs(v,u);
        }
    }
    void init(int n){
        for(int i=1;i<=n;i++) edge[i].clear();
    }
    void build(int n){
        init(n);
        for(int i=1;i<n;i++){
            int u,v;cin >> u >> v;
            edge[u].push_back(v);
            edge[v].push_back(u);
        }
        dfs(1,0);
    }
}

namespace TSAT{
    int n,cur;
    vector<int> edge[14*maxn];
    void add_edge(int u,int v){
        edge[u].push_back(v);
    }

    int val[14*maxn],comp[14*maxn],values[14*maxn];
    vector<int> z;
    int time = 0;

	int dfs(int i) {
		int low = val[i] = ++time, x; z.push_back(i);
		for(int e : edge[i]) if (!comp[e])
			low = min(low, val[e] ?: dfs(e));
		if (low == val[i]) do {
			x = z.back(); z.pop_back();
			comp[x] = low;
			if (values[x>>1] == -1)
				values[x>>1] = x&1;
		} while (x != i);
		return val[i] = low;
	}

    void init(int N){
        n=N;cur=n+1;
        time=0;z.clear();
        for(int i=0;i<14*n;i++){
            edge[i].clear();
            val[i]=comp[i]=0;
            values[i]=-1;
        }
    }

    void solve(){
        for(int i=0;i<2*cur;i++){
            if(!comp[i]) dfs(i);
        }
        for(int i=1;i<=n;i++){
            if(comp[2*i-2]==comp[2*i-1]){
                cout << -1 << '\n';
                return;
            }
        }
        for(int i=1;i<=n;i++){
            if(!values[i-1]) cout << i << ' ';
        }
        cout << '\n';
    }
}

int n,c[maxn],p[maxn];
map<pii,int> mp;

void build_edge(int u,int v){
    int a=Tree::lca(u,v);
    int pu=a,pv=a;
    if(u!=a) pu=Tree::par[u][0];
    else pu=Tree::jmp(v,Tree::dep[v]-Tree::dep[a]-1);
    if(v!=a) pv=Tree::par[v][0];
    else pv=Tree::jmp(u,Tree::dep[u]-Tree::dep[a]-1);
    pu=mp[{u,pu}];pv=mp[{v,pv}];
    TSAT::add_edge(2*u-1,2*v-2);
    TSAT::add_edge(2*v-1,2*u-2);
    TSAT::add_edge(2*u-2,2*pv-1);
    TSAT::add_edge(2*v-2,2*pu-1);
    TSAT::add_edge(2*pu-2,2*u-2);
    TSAT::add_edge(2*pv-2,2*v-2);
    //cout << u << ' ' << v << ' ' << pu << ' ' << pv << '\n';
}

void solve(){
    cin >> n;
    mp.clear();
    for(int i=1;i<=n;i++) p[i]=0;
    for(int i=1;i<=2*n;i++) cin >> c[i];
    Tree::build(2*n);
    TSAT::init(2*n);

    for(int i=1;i<=2*n;i++){
        for(int v:Tree::edge[i]){
            int cc=TSAT::cur++;
            mp[{i,v}]=cc;
            TSAT::add_edge(2*cc-1,2*i-1);
            TSAT::add_edge(2*i-2,2*cc-2);
        }
    }

    for(int i=1;i<=2*n;i++){
        int cc=TSAT::cur,sz=(int)Tree::edge[i].size();
        for(int j=0;j<sz;j++){
            int v=Tree::edge[i][j];
            if(j){
                TSAT::add_edge(2*(cc+j)-1,2*(cc+j-1)-1);
                TSAT::add_edge(2*(cc+sz+j-1)-1,2*(cc+sz+j)-1);
                TSAT::add_edge(2*(cc+j)-2,2*(cc+j-1)-2);
                TSAT::add_edge(2*(cc+sz+j-1)-2,2*(cc+sz+j)-2);
            }
            int s=mp[{i,v}],t=mp[{v,i}];
            TSAT::add_edge(2*(cc+j)-1,2*t-1);
            TSAT::add_edge(2*(cc+sz+j)-1,2*t-1);
            TSAT::add_edge(2*(cc+j)-2,2*s-2);
            TSAT::add_edge(2*(cc+sz+j)-2,2*s-2);
            if(j){
                TSAT::add_edge(2*s-1,2*(cc+j-1)-1);
                TSAT::add_edge(2*t-2,2*(cc+j-1)-2);
            }
            if(j<sz-1){
                TSAT::add_edge(2*s-1,2*(cc+sz+j+1)-1);
                TSAT::add_edge(2*t-2,2*(cc+sz+j+1)-2);
            }
        }
        TSAT::cur+=2*sz;
    }

    for(int i=1;i<=2*n;i++){
        if(p[c[i]]) build_edge(p[c[i]],i);
        p[c[i]]=i;
    }
    TSAT::solve();
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}
