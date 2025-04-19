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
const int maxn=500005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=500005;
const int maxl=20;
const int maxa=250000;
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
vector<pii> edge[maxn];
int dist[maxn];
void solve(){
    int a,b,c,d,e,n;cin >> a >> b >> c >> d >> e >> n;
    b+=a;c+=b;d+=c;e+=d;
    auto dijisktra = [&](int s){
        for(int i=0;i<=e;i++) dist[i]=inf;
        priority_queue<pii,vector<pii>,greater<pii>> pq;
        dist[s]=0;pq.push({0,s});
        while(!pq.empty()){
            auto [d,u]=pq.top();pq.pop();
            if(d!=dist[u]) continue;
            for(auto [v,w]:edge[u]){
                if(d+w<dist[v]) pq.push({dist[v]=d+w,v});
            }
        }
    };
    for(int i=1;i<=n;i++){
        int l,r;cin >> l >> r;l--;
        edge[l].push_back({r,r-l});
        edge[r].push_back({l,r-l});
    }
    dijisktra(a);
    int ab=dist[b],ac=dist[c],ad=dist[d];
    dijisktra(b);
    int bc=dist[c],bd=dist[d];
    dijisktra(c);
    int cd=dist[d];
    int res=min({ab+cd,ac+bd,ad+bc});
    cout << (res>=inf?-1:res) << '\n';
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
