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
const int mod=1e9+7;
const int maxn=500005;
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

int n,l[maxn],r[maxn],lt[maxn],rt[maxn],sl[maxn],sr[maxn];
int qq[2*maxn],d[maxn],par[maxn][maxl];

int tree[8*maxn];
void update(int l,int r,int id,int tl,int tr,int val){
    if(tr<l || r<tl) return;
    if(tl<=l && r<=tr){
        tree[id]=min(tree[id],val);
        return;
    }
    int mid=(l+r)>>1;
    update(l,mid,id<<1,tl,tr,val);update(mid+1,r,id<<1|1,tl,tr,val);
}
int query(int l,int r,int id,int p){
    if(l==r) return tree[id];
    int mid=(l+r)>>1;
    if(p<=mid) return min(tree[id],query(l,mid,id<<1,p));
    else return min(tree[id],query(mid+1,r,id<<1|1,p));
}

int bit[maxn];
void bit_update(int x){
    for(int i=x;i<=n;i+=(i&(-i))) bit[i]++;
}
int bit_query(int x){
    int res=0;
    for(int i=x;i>=1;i-=(i&(-i))) res+=bit[i];
    return res;
}

int lca(int u,int v){
    if(d[u]>d[v]) swap(u,v);
    for(int i=0;i<20;i++) if((d[v]-d[u])>>i&1) v=par[v][i];
    if(u==v) return u;
    for(int i=19;i>=0;i--) if(par[u][i]!=par[v][i]) u=par[u][i],v=par[v][i];
    return par[u][0];
}

void solve(){
    cin >> n;
    for(int i=1;i<=n;i++) cin >> l[i] >> r[i];
    for(int i=1;i<=8*n;i++) tree[i]=n+1;
    for(int i=0;i<20;i++) par[n+1][i]=n+1;
    for(int i=n;i>=1;i--){
        lt[i]=query(1,2*n,1,l[i]);
        rt[i]=query(1,2*n,1,r[i]);
        update(1,2*n,1,l[i],r[i],i);
        qq[l[i]]=-i;qq[r[i]]=i;
    }
    for(int i=1;i<=2*n;i++){
        int id=qq[i];
        if(id<0) sl[-id]=bit_query(lt[-id]-1)-bit_query(-id-1);
        else{
            bit_update(id);
            sr[id]=bit_query(rt[id]-1)-bit_query(id-1);
        }
    }
    int ans=0;
    for(int i=n;i>=1;i--){
        sl[i]+=sl[lt[i]];
        sr[i]+=sr[rt[i]];
        int s=sr[i]-sl[i],a=lca(lt[i],rt[i]);
        s-=(sr[a]-sl[a]);
        d[i]=d[a]+1;par[i][0]=a;
        for(int j=1;j<20;j++) par[i][j]=par[par[i][j-1]][j-1];
        ans=(ans+power(s,mod-2))%mod;
    }
    cout << ans << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}

