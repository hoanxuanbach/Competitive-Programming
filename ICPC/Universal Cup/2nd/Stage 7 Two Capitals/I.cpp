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
#define int long long
#define ld long double
#define pii pair<int,int>
#define piii pair<int,pii>
#define mpp make_pair
#define fi first
#define se second
const int inf=1e18;
const int mod=998244353;
const int maxn=1000005;
const int bl=650;
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
const int base=131;

int n,m;
int num[maxn],low[maxn],pos;
vector<pii> edge[maxn];

pii e[maxn];
int col[maxn];

int cc[maxn];
bool check=false;
vector<int> st;

void check_cycle_bcc(vector<int> num){
    vector<int> ver;
    int all=0;
    for(int id:num){
        if(!cc[e[id].fi]) ver.push_back(e[id].fi);
        if(!cc[e[id].se]) ver.push_back(e[id].se);
        cc[e[id].fi]|=(1<<col[id]);
        cc[e[id].se]|=(1<<col[id]);
        all|=(1<<col[id]);
    }
    int cnt=0;
    for(int u:ver) if(cc[u]!=2 && cc[u]!=4 && cc[u]!=8) cnt++;
    if(cnt>=3 && all==14) check=true;
    for(int id:num) cc[e[id].fi]=cc[e[id].se]=0;
}

void dfs(int u,int p){
    low[u]=num[u]=++pos;
    for(auto [v,id]:edge[u]){
        if(v==p) continue;
        if(!num[v]){
            st.push_back(id);
            dfs(v,u);
            low[u]=min(low[u],low[v]);
            if(low[v]>=num[u]){
                vector<int> cur;
                while(true){
                    int x=st.back();
                    cur.push_back(x);
                    st.pop_back();
                    if(x==id) break;
                }
                check_cycle_bcc(cur);
            }
        }
        else{
            low[u]=min(low[u],num[v]);
            if(num[v]<num[u]) st.push_back(id);
        }
    }
}

void solve(){
    cin >> n >> m;

    pos=0;check=false;
    for(int i=1;i<=n;i++){
        num[i]=low[i]=0;
        edge[i].clear();
    }

    for(int i=1;i<=m;i++){
        int u,v;cin >> u >> v >> col[i];
        e[i]={u,v};
        edge[u].push_back({v,i});
        edge[v].push_back({u,i});
    }
    dfs(1,0);
    cout << (check?"Yes":"No") << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}
