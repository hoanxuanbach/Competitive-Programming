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
//#define int long long
#define ld long double
#define pii pair<int,int>
#define piii pair<int,pii>
#define mpp make_pair
#define fi first
#define se second
const long long inf=1e18;
const int mod=1e9+7;
const int maxn=100005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=500005;
const int maxl=20;
const int maxa=250000;
const int root=3;
/*
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
const int iroot=power(3,mod-2);
*/
const int base=101;
struct treat{
    int t,l,r,c;
    bool operator<(treat o){return t<o.t;}
};
int cur,cc[maxn];
vector<vector<int>> edge;
struct BIT{
    int n;
    vector<int> bit;
    void init(int N){n=N;bit.assign(n+1,0);}
    void update(int x,int val){
        for(int i=x;i<=n;i+=(i&(-i))){
            if(bit[i]) edge.push_back({bit[i],val}),bit[i]=cur++;
            else bit[i]=val;
        }
    }
    void query(int x,int val){
        for(int i=x;i>=1;i-=(i&(-i))) if(bit[i]) edge[val].push_back(bit[i]);
    }
};
treat S[maxn];
void solve(){
    int n,m;cin >> n >> m;
    cur=m+1;edge.resize(cur);
    for(int i=1;i<=m;i++) cin >> S[i].t >> S[i].l >> S[i].r >> S[i].c,S[i].l--;
    sort(S+1,S+m+1);
    BIT ss;ss.init(m);
    vector<pii> com;
    auto get = [&](int x,int y){return upper_bound(com.begin(),com.end(),mpp(x,y))-com.begin();};
    for(int i=1;i<=m;i++) com.push_back({S[i].l-S[i].t,i});
    sort(com.begin(),com.end());
    for(int i=1;i<=m;i++){
        int p=get(S[i].r-S[i].t,m),q=get(S[i].l-S[i].t,i);
        ss.query(p,i);ss.update(q,i);
    }
    ss.init(m);com.clear();
    for(int i=1;i<=m;i++) com.push_back({S[i].l+S[i].t,i});
    sort(com.begin(),com.end());
    for(int i=m;i>=1;i--){
        int p=get(S[i].r+S[i].t,m),q=get(S[i].l+S[i].t,i);
        ss.query(p,i);ss.update(q,i);
    }
    vector<long long> dist(cur,inf);
    priority_queue<pair<long long,int>,vector<pair<long long,int>>,greater<pair<long long,int>>> pq;
    for(int i=1;i<=m;i++) if(S[i].l==0) pq.push({dist[i]=S[i].c,i});
    while(!pq.empty()){
        auto [d,u]=pq.top();pq.pop();
        if(u<=m && S[u].r==n){
            cout << d << '\n';
            return;
        }
        if(dist[u]!=d) continue;
        for(int v:edge[u]){
            long long nd=d+(v<=m?S[v].c:0);
            if(nd<dist[v]) pq.push({dist[v]=nd,v});
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
