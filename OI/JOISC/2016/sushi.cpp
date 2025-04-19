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
//const int inf=1e18;
const int mod=1e9+7;
const int maxn=400005;
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
int n,q,a[maxn];
struct block{
    priority_queue<int> pq;
    vector<int> add;
    int lt,rt;
    void build(){
        if(add.empty()) return;
        priority_queue<int,vector<int>,greater<int>> qq;
        for(int x:add) qq.push(x);
        for(int i=lt;i<=rt;i++){
            int x=qq.top();
            if(x<a[i]) qq.pop(),qq.push(a[i]),a[i]=x;
        }
        add.clear();
    }
    int update(int l,int r,int p){
        if(r<lt || rt<l) return p;
        if(l<=lt && rt<=r){
            int Max=pq.top();
            if(p<Max) pq.pop(),pq.push(p),add.push_back(p);
            return max(Max,p);
        }
        else{
            build();
            while(!pq.empty()) pq.pop();
            for(int i=max(lt,l);i<=min(rt,r);i++) if(p<a[i]) swap(a[i],p);
            for(int i=lt;i<=rt;i++) pq.push(a[i]);
            return p;
        }
    }
}ss[maxs];

void solve(){
    cin >> n >> q;
    for(int i=0;i<=(n-1)/bl;i++) ss[i].lt=i*bl,ss[i].rt=min(n,(i+1)*bl)-1;
    for(int i=0;i<n;i++) cin >> a[i],ss[i/bl].pq.push(a[i]);
    while(q--){
        int s,t,p;cin >> s >> t >> p;s--;t--;
        if(s<=t){
            for(int i=0;i<=(n-1)/bl;i++) p=ss[i].update(s,t,p);
        }
        else{
            for(int i=0;i<=(n-1)/bl;i++) p=ss[i].update(s,n-1,p);
            for(int i=0;i<=(n-1)/bl;i++) p=ss[i].update(0,t,p);
        }
        cout << p << '\n';
    }
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
