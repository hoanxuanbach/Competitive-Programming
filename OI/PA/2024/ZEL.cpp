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
const long long inf=1e18;
const int mod=998244353;
const int maxn=7005;
const int B=650;
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
    int n,m,k;cin >> n >> k >> m;
    for(int i=1;i<=n;i++){
        int x,y,c;cin >> x >> y >> c;
        p[x].push_back({y,c});
    }

    vector<int> d(m,inf);d[0]=0;
    for(int i=1;i<=k;i++){
        vector<int> nd(m,inf);
        for(auto [x,c]:p[i]){
            for(int j=0;j<m;j++) nd[(j+x)%m]=min(nd[(j+x)%m],d[j]+c);
        }
        swap(d,nd);
    }

    vector<int> a(m,inf);a[0]=0;
    vector<bool> used(m,false);
    for(int i=0;i<m;i++){
        int p=-1;
        for(int j=0;j<m;j++){
            if(used[j]) continue;
            if(p==-1 || a[p]>a[j]) p=j;
        }
        used[p]=true;
        for(int j=0;j<m;j++) a[(p+j)%m]=min(a[(p+j)%m],a[p]+d[j]);
    }
    for(int i=0;i<m;i++) cout << (a[i]==inf?-1:a[i]) << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}

