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
const int maxn=200005;
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

int n,m,k;
vector<pii> X[maxn],Y[maxn];
vector<pii> edge[maxn][2];
int dist[maxn][2];
bool check[maxn];

void solve(){
    cin >> n >> m >> k;

    vector<piii> p;
    auto add = [&](int x,int y,int id){
        p.push_back({{x,y},id});
        X[x].push_back({y,id});
        Y[y].push_back({x,id});
    };

    for(int i=1;i<=k;i++){
        check[i]=true;
        int x,y;cin >> x >> y;
        add(x,y,i);
    }
    sort(p.begin(),p.end());

    bool st=(p[0].fi==mpp(1LL,1LL)),en=(p.back().fi==mpp(1LL,1LL));
    int S=-1,E=-1;
    if(st) S=p[0].se;
    else S=0,add(1,1,0);
    if(en) E=p.back().se;
    else E=k+1,add(n,m,k+1);

    for(int i=1;i<=n;i++){
        sort(X[i].begin(),X[i].end());
        for(int j=0;j<(int)X[i].size()-1;j++){
            int u=X[i][j].se,v=X[i][j+1].se,w=X[i][j+1].fi-X[i][j].fi;
            edge[u][0].push_back({v,w});
            edge[v][0].push_back({u,w});
        }
    }

    for(int i=1;i<=m;i++){
        sort(Y[i].begin(),Y[i].end());
        for(int j=0;j<(int)Y[i].size()-1;j++){
            int u=Y[i][j].se,v=Y[i][j+1].se,w=Y[i][j+1].fi-Y[i][j].fi;
            edge[u][1].push_back({v,w});
            edge[v][1].push_back({u,w});
        }
    }

    for(int i=0;i<=k+1;i++) dist[i][0]=dist[i][1]=inf;
    priority_queue<piii,vector<piii>,greater<piii>> pq;
    pq.push({{0,S},0});dist[S][0]=0;
    while(!pq.empty()){
        int u=pq.top().fi.se,d=pq.top().fi.fi,t=pq.top().se;pq.pop();
        if(dist[u][t]!=d) continue;
        if(u==E){
            cout << d << '\n';
            return;
        }
        for(int i=0;i<=check[u];i++){
            for(auto [v,w]:edge[u][t^i]){
                if(dist[v][t^i]>d+w+i){
                    dist[v][t^i]=d+w+i;
                    pq.push({{d+w+i,v},t^i});
                }
            }
        }
    }
    cout << -1 << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
