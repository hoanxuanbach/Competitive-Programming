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
const int maxn=1000005;
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

int n,pre[maxn],nxt[maxn],a[maxn],sz[maxn];
vector<int> pos[maxn];

void unions(int x,int y){
    sz[x]+=sz[y];
    pre[nxt[y]]=x;
    nxt[x]=nxt[y];
    int l=pre[x],r=nxt[x];
    if(a[l]>a[x] && a[x]<a[r]) pos[sz[x]].push_back(x);
}

void solve(){
    cin >> n;
    for(int i=1;i<=n;i++) pos[i].clear();
    a[0]=inf;
    int N=0,total=0;
    for(int i=1;i<=n;i++){
        int x;cin >> x;total+=x;
        if(a[N]==x) sz[N]++;
        else a[++N]=x,sz[N]=1;
    }
    swap(n,N);
    a[n+1]=inf;
    int val=-a[1];
    for(int i=1;i<n;i++) if(a[i]>a[i+1]) val+=a[i]-a[i+1];
    for(int i=1;i<=n;i++) if(a[i]<a[i+1] && a[i]<a[i-1]) pos[sz[i]].push_back(i);
    for(int i=0;i<=n+1;i++) nxt[i]=i+1,pre[i]=i-1;
    for(int x=1;x<=N;x++){
        if(val<=0) break;
        while(!pos[x].empty()){
            int i=pos[x].back();pos[x].pop_back();
            int l=pre[i],r=nxt[i];
            int k=min(val,min(a[l],a[r])-a[i]);
            //cout << i << ' ' << k << ' ' << sz[i] << '\n';
            total+=k*sz[i];a[i]+=k;val-=k;
            if(a[l]==a[i]) unions(l,i),i=l;
            if(a[i]==a[r]) unions(i,r);
            if(val<=0) break;
        }
    }
    cout << total << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}
