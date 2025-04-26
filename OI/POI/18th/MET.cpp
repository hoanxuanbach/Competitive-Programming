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
#include<bits/stdc++.h>
using namespace std;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_real_distribution<> pp(0.0,1.0);
#define pii pair<int,int>
const long long inf=1e18;
const int mod=998244353;
const int maxn=300005;
const int maxl=20;
const int maxa=1000005;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
struct qry{
    int l,r,val;
};
int n,m,q,a[maxn],p[maxn],ans[maxn];
vector<int> x[maxn],ss[maxn];
qry que[maxn];
namespace BIT{
    long long bit[maxn];
    void update(int l,int r,int val){
        for(int i=l;i<=m;i+=(i&(-i))) bit[i]+=val;
        for(int i=r+1;i<=m;i+=(i&(-i))) bit[i]-=val;
    }
    void up(int l,int r,int val){
        if(l>r){update(l,m,val);update(1,r,val);}
        else update(l,r,val);
    }
    long long query(int x){
        long long res=0;
        for(int i=x;i>=1;i-=(i&(-i))) res+=bit[i];
        return res;
    }
}
void cal(int l,int r){
    int mid=(l+r)>>1,lt=(l+mid-1)>>1,rt=(mid+r+1)>>1;
    for(int v:ss[mid]){
        long long sum=0;
        for(int d:x[v]) sum=min(sum+BIT::query(d),inf);
        if(sum>=p[v]) ans[v]=mid;
        if(sum>=p[v] && l<mid) ss[lt].push_back(v);
        else if(sum<p[v] && r>mid) ss[rt].push_back(v);
    }
    if(r>mid){
        for(int i=mid+1;i<=rt;i++) BIT::up(que[i].l,que[i].r,que[i].val);
        cal(mid+1,r);
        for(int i=mid+1;i<=rt;i++) BIT::up(que[i].l,que[i].r,-que[i].val);
    }
    if(l<mid){
        for(int i=lt+1;i<=mid;i++) BIT::up(que[i].l,que[i].r,-que[i].val);
        cal(l,mid-1);
        for(int i=lt+1;i<=mid;i++) BIT::up(que[i].l,que[i].r,que[i].val);
    }
}
void solve(){
    cin >> n >> m;
    for(int i=1;i<=m;i++){cin >> a[i];x[a[i]].push_back(i);}
    for(int i=1;i<=n;i++) cin >> p[i];
    cin >> q;
    for(int i=1;i<=q;i++) cin >> que[i].l >> que[i].r >> que[i].val;
    int mid=(1+q)>>1;
    for(int i=1;i<=n;i++) ss[mid].push_back(i);
    for(int i=1;i<=mid;i++) BIT::up(que[i].l,que[i].r,que[i].val);
    cal(1,q);
    for(int i=1;i<=n;i++){
        if(ans[i]) cout << ans[i] << '\n';
        else cout << "NIE\n";
    }
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int t=1;//cin >> t;
    while(t--) solve();
}
