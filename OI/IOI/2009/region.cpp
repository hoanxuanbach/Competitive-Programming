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
#define ll long long
#define ld long double
#define pii pair<int,int>
#define piii pair<int,pii>
#define mpp make_pair
#define fi first
#define se second
const long long inf=1e18;
const int mod=998244353;
const int maxn=200005;
const int B=450;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=25;
const int maxa=1000000;
const int root=3;
const int base=101;

int n,rr,q;
int c[maxn],L[maxn],R[maxn],T;
vector<int> edge[maxn];
vector<pii> qq[maxn];
vector<int> pos[maxn];
vector<int> res1[maxn],res2[maxn];
int num[maxn];

void dfs(int u){
    L[u]=++T;
    pos[c[u]].push_back(L[u]);
    for(int v:edge[u]) dfs(v);
    R[u]=T;
    qq[c[u]].push_back({L[u],R[u]});
    //cout << u << ' ' << c[u] << ' ' << L[u] << ' ' << R[u] << '\n';
}

void dfs2(int u,int C,int d){
    res1[C][c[u]]+=d;
    d+=(num[u]=(c[u]==C));
    for(int v:edge[u]){
        dfs2(v,C,d);
        num[u]+=num[v];
    }
    res2[C][c[u]]+=num[u];
}

void solve(){
    cin >> n >> rr >> q;
    for(int i=1;i<=n;i++){
        if(i>1){
            int p;cin >> p;
            edge[p].push_back(i);
        }
        cin >> c[i];
    }
    dfs(1);
    for(int i=1;i<=rr;i++){
        if((int)pos[i].size()>B){
            res1[i].assign(rr+1,0);
            res2[i].assign(rr+1,0);
            dfs2(1,i,0);
        }
    }
    for(int i=1;i<=q;i++){
        int x,y;cin >> x >> y;
        if((int)pos[x].size()>B) cout << res1[x][y] << endl;
        else if((int)pos[y].size()>B) cout << res2[y][x] << endl;
        else{
            int total=0,j=0;
            vector<pii> cc;
            //cout << '*' << x << '\n';
            for(auto [l,r]:qq[x]){
                //cout << l << ' ' << r << '\n';
                while(j<(int)pos[y].size() && pos[y][j]<=r) cc.push_back({pos[y][j++],1});
                while((int)cc.size()>=2 && cc.end()[-2].fi>=l){
                    int x=cc.back().se;cc.pop_back();
                    cc.back().se+=x;
                }
                if(!cc.empty() && cc.back().fi>=l) total+=cc.back().se;
            }
            cout << total << endl;
        }
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
