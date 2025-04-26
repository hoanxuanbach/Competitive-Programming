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
#define piii pair<int,pii>
#define mpp make_pair
#define fi first
#define se second
const int mod=998244353;
const int maxn=200005;
const int B=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=25;
const int maxa=1000000;
const int root=3;
const int base=101;

const int N = 105;
struct MaxClique { // Maximum Clique
    bitset<N> a[N], cs[N],cur,sol;
    int ans, q, d[N], n;
    void init(int _n) {
        n = _n;
        cur.reset();
        sol.reset();
        for(int i = 0; i < n; i++) a[i].reset(),a[i].flip();
    }
    void addEdge(int u, int v) { a[u][v] = a[v][u] = 0; }
    void csort(vector<int> &r, vector<int> &c) {
        int mx = 1, km = max(ans - q + 1, 1), t = 0,m = r.size();
        cs[1].reset(), cs[2].reset();
        for(int i = 0; i < m; i++) {
            int p = r[i], k = 1;
            while ((cs[k] & a[p]).count()) k++;
            if (k > mx) mx++, cs[mx + 1].reset();
            cs[k][p] = 1;
            if (k < km) r[t++] = p;
        }
        c.resize(m);
        if (t) c[t - 1] = 0;
        for (int k = km; k <= mx; k++)
            for (int p = cs[k]._Find_first(); p < N;p = cs[k]._Find_next(p))
                r[t] = p, c[t] = k, t++;
    }
    void dfs(vector<int> &r, vector<int> &c, int l,bitset<N> mask) {
        while (!r.empty()) {
            int p = r.back();
            r.pop_back(), mask[p] = 0;
            if(q + c.back() <= ans) return;
            //cout << "add " << p << '\n';
            cur[p]=1;q++;
            if (q > ans) ans = q, sol=cur;

            vector<int> nr, nc;
            bitset<N> nmask = mask & a[p];
            for(int i : r)
                if(a[p][i]) nr.push_back(i);
            if(!nr.empty()){
                if(l < 4){
                    for(int i : nr)
                    d[i] = (a[i] & nmask).count();
                    sort(nr.begin(), nr.end(),
                    [&](int x, int y) { return d[x] > d[y]; });
                }
                csort(nr, nc), dfs(nr, nc, l + 1, nmask);
            }
            c.pop_back();q--;
            cur[p]=0;
            //cout << "del " << p << '\n';
        }
    }
    int solve(bitset<N> mask = bitset<N>(string(N, '1'))) {
        vector<int> r, c;
        ans = q = 0;
        for (int i = 0; i < n; i++)
            if (mask[i]) r.push_back(i);
        for (int i = 0; i < n; i++)
            d[i] = (a[i] & mask).count();
        sort(r.begin(), r.end(),[&](int i, int j) { return d[i] > d[j]; });
        csort(r, c), dfs(r, c, 1, mask);
        return ans;
    }
}graph;

int vis[N];
vector<int> edge[N];
bitset<N> e[N];

void solve(){
    int n,m;cin >> n >> m;
    for(int i=0;i<m;i++){
        int u,v;cin >> u >> v;
        u--;v--;edge[u].push_back(v);
    }
    graph.init(n);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++) vis[j]=0;
        function<void(int)> dfs = [&](int u){
            vis[u]=1;
            for(int v:edge[u]) if(!vis[v]) dfs(v);
        };
        dfs(i);
        for(int j=0;j<n;j++){
            e[i][j]=vis[j];
            if(j!=i && vis[j]) graph.addEdge(i,j);
        }
    };
    for(int i=0;i<n;i++) for(int j=0;j<n;j++) e[i][j]=e[j][i]=e[i][j]|e[j][i];
    graph.solve();
    int res=graph.ans;
    cout << res << '\n';
    for(int i=0;i<n;i++) cout << graph.sol[i];
    cout << '\n';

    bitset<N> cc;
    for(int i=0;i<n;i++) cc[i]=1;
    for(int i=0;i<n;i++){
        graph.solve(cc^e[i]);
        if(graph.ans+1==res) cout << 1;
        else cout << 0;
    }
    cout << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
