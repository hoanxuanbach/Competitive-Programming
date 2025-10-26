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
const int maxn=200005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=40;
const int maxa=(1<<20)+5;
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

int n,a[maxn];
bitset<maxn> bs[maxl+5];
bool cc[maxl+5];

vector<int> edge[maxl+5];
int mask[maxl+5],f[maxl+5];

void dfs(int u){
    mask[u]|=(1LL<<u);
    for(int v:edge[u]){
        if(!mask[v]) dfs(v);
        mask[u]|=mask[v];
    }
}

int num[maxa];

void solve(){
    cin >> n;
    for(int i=0;i<n;i++){
        cin >> a[i];
        for(int j=0;j<maxl;j++) if(a[i]>>j&1) bs[j].set(i);
    }
    for(int i=0;i<maxl;i++){
        int x=bs[i].count();
        cc[i]=(x==n || x==0);
        for(int j=0;j<i;j++) cc[i]|=(bs[i]==bs[j]);
    }
    vector<pii> pos;
    for(int i=0;i<maxl;i++){
        if(cc[i]) continue;
        pos.push_back({bs[i].count(),i});
    }
    int sz=(int)pos.size();
    sort(pos.begin(),pos.end());
    for(int i=0;i<sz;i++) f[pos[i].se]=i;
    for(int i=0;i<maxl;i++){
        if(cc[i]) continue;
        for(int j=0;j<maxl;j++){
            if(j==i || cc[j]) continue;
            if(bs[i]==(bs[i]&bs[j])) edge[f[i]].push_back(f[j]);
        }
    }
    int p=sz/2;
    for(int i=0;i<sz;i++) if(!mask[i]) dfs(i);
    for(int i=0;i<(1<<(sz-p));i++){
        int cur=0;
        for(int j=0;j<sz-p;j++) if((i>>j)&1) cur|=mask[p+j];
        num[cur>>p]=1;
    }
    for(int i=0;i<sz-p;i++){
        for(int j=0;j<(1<<(sz-p));j++) if(!((j>>i)&1)) num[j]+=num[j^(1<<i)];
    }
    int ans=0;
    for(int i=0;i<(1<<p);i++){
        int cur=0;
        for(int j=0;j<p;j++) if((i>>j)&1) cur|=mask[j];
        int d=cur&((1<<p)-1);cur>>=p;
        ans+=(d==i)*num[cur];
    }
    cout << ans << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
