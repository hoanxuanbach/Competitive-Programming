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
const int base=101;

vector<pii> p[maxn];

void solve(){
    int n,m,k;cin >> n >> m >> k;
    if(m>2*k+1){
        if(n==1) cout << "YES\n";
        else cout << "NO\n";
        return;
    }
    int E=n*(m-1)+m*(n-1),V=n*m;
    for(int i=1;i<=k;i++){
        int x1,x2,y;cin >> x1 >> x2 >> y;
        p[y].push_back({x1,x2});
        V-=x2-x1+1;
        if(y!=1) E-=(x2-x1+1);
        if(y!=m) E-=(x2-x1+1);
    }
    for(int i=1;i<=m;i++){
        sort(p[i].begin(),p[i].end());
        vector<pii> nw;
        for(pii x:p[i]){
            if(nw.empty() || nw.back().se+1<x.fi) nw.push_back(x);
            else nw.back().se=x.se;
        }
        p[i]=nw;
    }
    for(int i=1;i<=m;i++){
        int pos=0;
        for(pii x:p[i]){
            E-=(x.se-x.fi+(x.fi!=1)+(x.se!=n));
            while(pos<(int)p[i+1].size() && p[i+1][pos].se<=x.se){
                int l=max(x.fi,p[i+1][pos].fi),r=min(x.se,p[i+1][pos].se);
                if(l<=r) E+=(r-l+1);
                pos++;
            }
            if(pos<(int)p[i+1].size()){
                int l=max(x.fi,p[i+1][pos].fi),r=min(x.se,p[i+1][pos].se);
                if(l<=r) E+=(r-l+1);
            }
        }
    }
    if(E==V-1) cout << "YES\n";
    else cout << "NO\n";
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
