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
#include<bits/stdc++.h>
using namespace std;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_real_distribution<> pp(0.0,1.0);
#define int long long
#define ld long double
#define pii pair<int,int>
#define piii pair<int,pii>
#define fi first
#define se second
const int inf=1e18;
const int mod=998244353;
const int mod2=1e9+7;
const int maxn=200005;
const int bl=650;
const int maxs=650;
const int maxm=200005;
const int maxq=500005;
const int maxl=20;
const int maxa=1000005;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
vector<int> edge[4*maxn];
int n,check[4*maxn],dist[4*maxn][4],pos[maxn];
namespace Segtree{
    void build(int l,int r,int id){
        if(l==r){
            pos[l]=id;
            check[id]=l;
            return;
        }
        int mid=(l+r)>>1;
        build(l,mid,id<<1);build(mid+1,r,id<<1|1);
        edge[id<<1].push_back(id);
        edge[id<<1|1].push_back(id);
    }
    void update(int l,int r,int id,int tl,int tr,int p){
        if(tr<l || r<tl) return;
        if(tl<=l && r<=tr){
            edge[id].push_back(pos[p]);
            return;
        }
        int mid=(l+r)>>1;
        update(l,mid,id<<1,tl,tr,p);update(mid+1,r,id<<1|1,tl,tr,p);
    }
}
priority_queue<piii,vector<piii>,greater<piii>> pq;
void add(int u,int d,int x){
    if(dist[u][x]>d){
        dist[u][x]=d;
        pq.push({d,{u,x}});
    }
}
void solve(){
    cin >> n;
    Segtree::build(1,n,1);
    for(int i=1;i<=4*n;i++){
        for(int j=0;j<=3;j++) dist[i][j]=n+1;
    }
    for(int i=1;i<=n;i++){
        int l,r;cin >> l >> r;
        Segtree::update(1,n,1,l,r,i);
    }
    dist[pos[1]][1]=0;
    dist[pos[n]][2]=0;
    pq.push({0,{pos[1],1}});pq.push({0,{pos[n],2}});
    while(!pq.empty()){
        int d=pq.top().fi,u=pq.top().se.fi,x=pq.top().se.se;pq.pop();
        if(dist[u][x]!=d) continue;
        for(int v:edge[u]){
            add(v,d+(check[v]>=1),x);
            if(check[v]){
                if(x==1) add(v,d+dist[v][2]+(check[v]==n),3);
                if(x==2) add(v,d+dist[v][1]+(check[v]==1),3);
            }
        }
    }
    int q;cin >> q;
    for(int i=1;i<=q;i++){
        int u;cin >> u;
        cout << (dist[pos[u]][3]==n+1?-1:dist[pos[u]][3]) << '\n';
    }
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}