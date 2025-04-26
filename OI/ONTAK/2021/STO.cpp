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
const int maxl=20;
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

int n,m,k,pre[maxn],c[maxn],a[maxn],b[maxn];
int s[maxn],d[maxn];
int Min[maxn][maxl];
vector<pii> qq[maxn];
pii ans[maxn];

int bit[2*maxn];
void update(int x,int val){
    for(int i=x;i<=2*n;i+=(i&(-i))) bit[i]=max(bit[i],val);
}
int query(int x){
    int res=0;
    for(int i=x;i>=1;i-=(i&(-i))) res=max(res,bit[i]);
    return res;
}

void solve(){
    cin >> n >> m >> k;
    for(int i=1;i<=n;i++){
        cin >> c[i];
        pre[i]=pre[i-1]+(c[i]==-1?-1:1);
        Min[i][0]=pre[i];
    }
    for(int i=1;i<18;i++){
        for(int j=1;j<=(n-(1<<i)+1);j++) Min[j][i]=min(Min[j][i-1],Min[j+(1<<(i-1))][i-1]);
    }
    auto get_Min = [&](int l,int r){
        int res=inf;
        for(int i=0;i<18;i++){
            if((r-l+1)&(1<<i)){
                res=min(res,Min[l][i]);
                l+=(1<<i);
            }
        }
        return res;
    };
    vector<pii> p;
    for(int i=1;i<=m;i++){
        cin >> a[i] >> b[i];
        d[i]=get_Min(a[i],b[i])-pre[a[i]-1];
        s[i]=pre[b[i]]-pre[a[i]-1]+s[i-1];
        //cout << '*' << s[i-1]+d[i] << '\n';
        p.push_back({s[i-1]+d[i],-i});
    }
    for(int i=1;i<=k;i++){
        int x;cin >> x;
        p.push_back({x-1,i});
    }
    sort(p.begin(),p.end());
    int Max=0;
    for(pii x:p){
        if(x.se<0) Max=max(Max,-x.se);
        else{
            qq[b[Max]].push_back({x.fi+pre[a[Max]-1]-s[Max-1],x.se});
            ans[x.se].fi=Max;
        }
    }
    for(int i=1;i<=2*n;i++) bit[i]=-1;
    update(pre[0]+n,0);
    for(int i=1;i<=n;i++){
        update(pre[i]+n,i);
        for(auto [x,id]:qq[i]){
            //cout << x << ' ' << id << '\n';
            int pos=query(min(2*n,x+n));
            //cout << pos << '\n';
            ans[id].se=pos;
        }
    }
    for(int i=1;i<=k;i++){
        if(ans[i].se<b[ans[i].fi]) cout << c[ans[i].se+1] << '\n';
        else cout << c[a[ans[i].fi+1]] << '\n';
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
