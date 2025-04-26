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
#define ld long double
#define pii pair<int,int>
#define piii pair<int,pii>
#define mpp make_pair
#define fi first
#define se second
const int mod=998244353;
const int maxn=50005;
const int B=250;
const int maxs=255;
const int maxm=200005;
const int maxq=200005;
const int maxl=25;
const int maxa=1000000;
const int root=3;
const int base=101;

int n,q,bit[maxn];
int c[maxn],ans[maxq];
vector<pii> pos[maxn];

void update(int x){
    for(int i=x;i<=n;i+=(i&(-i))) bit[i]++;
}
int query(int x){
    int res=0;
    for(int i=x;i>=1;i-=(i&(-i))) res+=bit[i];
    return res;
}

struct YT{
    int f[maxs][maxn],sign=0;
    void add(int t,int r,int x){
        if(t>B) return;
        int l=1;r=min(r,f[t][0]+1);
        while(l<r){
            int mid=(l+r)>>1;
            if(sign^(f[t][mid]<x)) r=mid;
            else l=mid+1;
        }
        f[t][0]=max(f[t][0],l);
        swap(f[t][l],x);
        if(x) add(t+1,l,x);
        else{
            if(sign){
                if(l>B) update(l);
            }
            else update(t);
        }
    };
}T,T2;

void solve(){
    cin >> n >> q;
    for(int i=1;i<=n;i++) cin >> c[i];
    for(int i=1;i<=q;i++){
        int m,k;cin >> m >> k;
        pos[m].push_back({k,i});
    }
    T2.sign=1;
    for(int i=1;i<=n;i++){
        T.add(1,n,c[i]);
        T2.add(1,n,c[i]);
        for(auto [k,id]:pos[i]) ans[id]=query(k);
    }
    for(int i=1;i<=q;i++) cout << ans[i] << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
