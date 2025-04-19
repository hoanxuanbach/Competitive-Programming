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
const int mod=1e9+7;
const int maxn=200005;
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

void solve(){
    int n,ans=0;cin >> n;
    vector<int> Max(n+1,0),sum(n+1,0),deg(n+1,0),a(n+1),c(n+1);
    for(int i=1;i<=n;i++) cin >> a[i] >> c[i],deg[a[i]]++;
    queue<int> q;
    for(int i=1;i<=n;i++) if(deg[i]==0) q.push(i);
    int cc=0;
    while(!q.empty()){
        int u=q.front();q.pop();cc=2;
        deg[a[u]]--;sum[a[u]]+=c[u];
        Max[a[u]]=max(Max[a[u]],c[u]);
        if(deg[a[u]]==0) q.push(a[u]);
    }
    for(int i=1;i<=n;i++){
        ans+=sum[i]-Max[i];
        if(deg[i]){
            int u=i;cc++;
            vector<int> ver;
            do{
                ver.push_back(u);
                deg[u]=0,u=a[u];
            }while(u!=i);
            int add=0,ok=0;
            for(int v:ver) add+=min(Max[a[v]],c[v]),ok|=(c[v]<=Max[a[v]]);
            if(ok) ans+=add;
            else{
                int res=inf;
                for(int v:ver) res=min(res,add+c[v]-Max[a[v]]);
                ans+=res;
            }
        }
    }
    if(cc<=1) cout << 0 << '\n';
    else cout << ans << '\n';
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
