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
const int inf=1e9;
const int mod=998244353;
const int maxn=30005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=20;
const int maxa=1000000;
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

int n,m,B[maxn],P[maxn];
map<pii,vector<int>> mp;
vector<int> dist,cc,pos;
vector<int> edge[maxn];

void solve(){
    cin >> n >> m;
    for(int i=1;i<=m;i++){
        cin >> B[i] >> P[i];
        mp[{P[i],B[i]%P[i]}].emplace_back(B[i]);
    }
    int cnt=n;
    cc.assign(cnt,-1);
    pos.assign(cnt,-1);

    for(auto [x,v]:mp){
        int d=x.fi,r=x.se;
        sort(v.begin(),v.end());
        for(int a:v) edge[a].push_back(cnt+a/d);
        for(int i=r;i<n;i+=d){
            int add=0;
            if(i>r) add|=1;
            if(i+d<n) add|=2;
            cc.emplace_back(add);
            pos.emplace_back(i);
            cnt++;
        }
    }
    dist.assign(cnt,inf);
    deque<pii> q;
    q.emplace_back(0,B[1]);dist[B[1]]=0;
    while(!q.empty()){
        auto [d,u]=q.front();q.pop_front();
        if(dist[u]!=d) continue;
        if(u<n){
            for(int v:edge[u]){
                if(d<dist[v]){
                    dist[v]=d;
                    q.emplace_front(d,v);
                }
            }
        }
        else{
            int p=pos[u];
            if(d<dist[p]){
                dist[p]=d;
                q.emplace_front(d,p);
            }
            if((cc[u]&1) && d+1<dist[u-1]){
                dist[u-1]=d+1;
                q.emplace_back(d+1,u-1);
            }
            if((cc[u]&2) && d+1<dist[u+1]){
                dist[u+1]=d+1;
                q.emplace_back(d+1,u+1);
            }
        }
    }
    cout << (dist[B[2]]==inf?-1:dist[B[2]]) << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
