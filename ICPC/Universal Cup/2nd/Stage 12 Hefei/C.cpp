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
const int maxn=6000005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=25;
const int maxa=1000000;
const int root=3;
const int base=131;


struct node {
    int nxt[10];
    int len,slink,num;
};
string s;
node tree[maxn];
int n,num,suff;
vector<int> edge[maxn];

void addLetter(int pos) {
    int cur = suff, curlen = 0;
    int let = s[pos] - '0';

    while (true) {
        curlen = tree[cur].len;
        if (pos - 1 - curlen >= 0 && s[pos - 1 - curlen] == s[pos]) break;
        cur = tree[cur].slink;
    }

    if (tree[cur].nxt[let]) {
        suff = tree[cur].nxt[let];
        if(pos>=n) tree[suff].num++;
        return;
    }
    suff = ++num;
    tree[num].len = tree[cur].len + 2;
    tree[cur].nxt[let] = num;

    if (tree[num].len == 1) {
        tree[num].slink = 2;
        edge[2].push_back(num);
        if(pos>=n) tree[num].num++;
        return;
    }

    while (true) {
        cur = tree[cur].slink;
        curlen = tree[cur].len;
        if (pos - 1 - curlen >= 0 && s[pos - 1 - curlen] == s[pos]) {
            tree[num].slink = tree[cur].nxt[let];
            edge[tree[num].slink].push_back(num);
            break;
        }
    }
    if(pos>=n) tree[num].num++;
}

void initTree() {
    num = 2; suff = 2;
    tree[1].len = -1; tree[1].slink = 1;
    tree[2].len = 0; tree[2].slink = 1;
    edge[1].push_back(2);
}

long long ans=0;

void dfs(int u){
    for(int v:edge[u]) dfs(v),tree[u].num+=tree[v].num;
    if(tree[u].len<=n && tree[u].len>=0) ans=(ans+1LL*tree[u].num*tree[u].num%mod*tree[u].len%mod)%mod;
}

void solve(){
    cin >> n >> s;s+=s;
    initTree();
    for(int i=0;i<2*n;i++) addLetter(i);
    dfs(1);
    cout << ans << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}

