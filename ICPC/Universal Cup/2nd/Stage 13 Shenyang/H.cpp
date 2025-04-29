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
#pragma GCC target("avx2,fma")
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
const int maxn=300005;
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
const int base=1000003;

struct State{
    State(int n){
        edge.assign(n,{});
    }
    vector<vector<int>> edge;
    vector<pii> e;
    void add_edge(int u,int v){
        edge[u].push_back((int)e.size());
        edge[v].push_back((int)e.size());
        e.push_back({u,v});
    }
};

int n,m,k,cnt[5];
vector<int> edge[maxn];
bool vis[maxn];

void solve(){
    cin >> n >> m >> k;
    State G(n);
    for(int i=0;i<n;i++) edge[i].clear(),vis[i]=false;
    for(int i=1;i<=m;i++){
        int u,v;cin >> u >> v;
        u--;v--;
        edge[u].push_back(v);
        edge[v].push_back(u);
        G.add_edge(u,v);
    }
    bool down=true;
    int total=0;
    auto check = [&](int s){
        for(int i=0;i<=4;i++) cnt[i]=0;
        int num=0;
        function<void(int)> dfs = [&](int u){
            vis[u]=true;num++;
            cnt[min((int)edge[u].size(),4LL)]++;
            for(int v:edge[u]) if(!vis[v]) dfs(v);
        };
        dfs(s);
        if(cnt[4]>0) return false;
        if(num==1){
            if(k==1) total++;
            return true;
        }
        if(num==4 && cnt[3]==1 && cnt[1]==3){
            if(k==1) total+=4;
            else total+=3;
            return true;
        }
        if(cnt[3]>0) return false;
        if(!cnt[1]) total+=num;
        else if(cnt[1]==2) total+=max(0LL,num-k+1);
        else return false;
        return true;
    };
    for(int i=0;i<n;i++){
        if(!vis[i]) down &= check(i);
    }
    if(down){
        cout << total << '\n';
    }
    else{
        int ans=n;
        while(k>1 && (int)G.e.size()<(int)G.edge.size()){
            ans=min(ans,(int)G.e.size());
            State nxt((int)G.e.size());
            int cur=ans;
            for(int i=0;i<(int)G.edge.size();i++){
                int num=(int)G.edge[i].size()*((int)G.edge[i].size()-1)/2;
                cur-=num;
                if(cur<0) break;
                for(int u:G.edge[i]) for(int v:G.edge[i]) if(u<v) nxt.add_edge(u,v);
            }
            if(cur<0) break;
            swap(G,nxt);k--;
        }
        cout << ans << '\n';
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}
