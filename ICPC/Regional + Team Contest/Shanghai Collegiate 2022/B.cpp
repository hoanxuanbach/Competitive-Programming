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
#define piii pair<pii,int>
#define mpp make_pair
#define fi first
#define se second
const int inf=1e18;
const int mod=998244353;
const int maxn=3005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=20;
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

int n,q,d[maxn],cnt[maxn];
bool inq[maxn],vis[maxn],check=true;
vector<pii> adj[maxn],edge[maxn];

void dfs(int u,int a){
    vis[u]=true;
    if(u!=a){
        edge[a].push_back({u,d[u]});
        edge[u].push_back({a,-d[u]});
    }
    for(auto [v,w]:adj[u]){
        if(!vis[v]){
            d[v]=d[u]+w;
            dfs(v,a);
        }
        else if(d[v]!=d[u]+w) check=false;
    }
}

void solve(){
    cin >> n >> q;
    for(int i=1;i<=q;i++){
        int l,r,w;cin >> l >> r >> w;l--;
        w=((r-l)-w);
        if(w%2!=0){
            cout << "?\n";
            return;
        }
        w/=2;
        adj[l].push_back({r,w});
        adj[r].push_back({l,-w});
    }

    edge[n].push_back({0,-n/2});
    edge[0].push_back({n,n/2});

    for(int i=0;i<=n;i++){
        edge[0].push_back({i,i/2});
        if(i<n) edge[i].push_back({i+1,1});
        if(i) edge[i+1].push_back({i,0});
        if(!vis[i]) dfs(i,i);
        if(!check){
            cout << "?\n";
            return;
        }
    }
    for(int i=0;i<=n;i++) d[i]=inf;
    queue<int> q;
    d[0]=0;q.push(0);inq[0]=true;cnt[0]++;
    while(!q.empty()){
        int u=q.front();q.pop();inq[u]=false;
        for(auto [v,w]:edge[u]){
            if(d[u]+w<d[v]){
                d[v]=d[u]+w;
                if(!inq[v]){
                    q.push(v);
                    inq[v]=true;
                    cnt[v]++;
                    if(v==0 || cnt[v]>n){
                        cout << "?\n";
                        return;
                    }
                }
            }
        }
    }
    string res;
    for(int i=1;i<=n;i++) res+=(d[i]>d[i-1]?')':'(');
    cout << "! " << res << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
