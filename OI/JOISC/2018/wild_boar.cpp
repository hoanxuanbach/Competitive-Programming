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
const ll inf=1e18;
const int mod=998244353;
const int maxn=2005;
const int bl=650;
const int maxs=655;
const int maxL=100005;
const int maxq=1000005;
const int maxl=25;
const int maxa=1000000;
const int root=3;
const int base=131;

const int sz=5;

struct path{
    int a,b;
    ll d;
    path(ll d=0,int a=0,int b=0):d(d),a(a),b(b){}
    friend bool operator<(path x,path y){return x.d<y.d;}
    friend bool operator>(path x,path y){return x.d>y.d;}
};
struct dist{
    vector<path> p;
    dist(){}
    bool add(path x){
        if((int)p.size()>=sz) return false;
        int c1=0,c2=0;
        for(int i=0;i<(int)p.size();i++){
            if(x.a==p[i].a && x.b==p[i].b) return false;
            c1+=(x.a==p[i].a);
            c2+=(x.b==p[i].b);
        }
        if(c1<2 && c2<2){
            p.push_back(x);
            return true;
        }
        return false;
    }
    friend dist operator+(dist a,dist b){
        dist res;
        vector<path> cc;
        for(auto x:a.p) for(auto y:b.p) if(x.b!=y.a) cc.push_back(path(x.d+y.d,x.a,y.b));
        sort(cc.begin(),cc.end());
        for(auto x:cc) res.add(x);
        return res;
    }
}d[maxn][maxn],tree[4*maxL];

int n,m,T,L,X[maxL];
vector<pii> edge[maxn];

void dijisktra(int s){
    priority_queue<pair<path,int>,vector<pair<path,int>>,greater<pair<path,int>>> pq;
    for(auto &[v,w]:edge[s]) pq.push({path(w,v,s),v});
    while(!pq.empty()){
        path x=pq.top().fi;
        int u=pq.top().se;pq.pop();
        if(!d[s][u].add(x)) continue;
        for(auto [v,w]:edge[u]) if(v!=x.b) pq.push({path(x.d+w,x.a,u),v});
    }
}

void build(int l,int r,int id){
    if(l==r){
        tree[id]=d[X[l]][X[l+1]];
        return;
    }
    int mid=(l+r)>>1;
    build(l,mid,id<<1);build(mid+1,r,id<<1|1);
    tree[id]=tree[id<<1]+tree[id<<1|1];
}
void update(int l,int r,int id,int p){
    if(l==r){
        tree[id]=d[X[l]][X[l+1]];
        return;
    }
    int mid=(l+r)>>1;
    if(p<=mid) update(l,mid,id<<1,p);
    else update(mid+1,r,id<<1|1,p);
    tree[id]=tree[id<<1]+tree[id<<1|1];
}

void solve(){
    cin >> n >> m >> T >> L;
    for(int i=1;i<=m;i++){
        int u,v,w;cin >> u >> v >> w;
        edge[u].push_back({v,w});
        edge[v].push_back({u,w});
    }
    for(int i=1;i<=n;i++) dijisktra(i);
    for(int i=1;i<=L;i++) cin >> X[i];
    build(1,L-1,1);
    for(int i=1;i<=T;i++){
        int p;cin >> p >> X[p];
        if(p>1) update(1,L-1,1,p-1);
        if(p<L) update(1,L-1,1,p);
        cout << (tree[1].p.empty()?-1:tree[1].p[0].d) << '\n';
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
