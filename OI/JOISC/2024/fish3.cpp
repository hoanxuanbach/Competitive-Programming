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
const int maxn=300005;
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

int n,D,c[maxn],p[maxn],cc[maxn],pre[maxn];
int q,ans[maxn];
vector<pii> qq[maxn];

int tree[4*maxn];
int lazy[4*maxn];
void getnew(int l,int r,int id,int val){
    lazy[id]+=val;
    tree[id]+=(r-l+1)*val;
}
void pushdown(int l,int r,int id){
    if(!lazy[id]) return;
    int mid=(l+r)>>1;
    getnew(l,mid,id<<1,lazy[id]);
    getnew(mid+1,r,id<<1|1,lazy[id]);
    lazy[id]=0;
}
void update(int l,int r,int id,int tl,int tr,int val){
    if(tr<l || r<tl) return;
    if(tl<=l && r<=tr){
        getnew(l,r,id,val);
        return;
    }
    pushdown(l,r,id);
    int mid=(l+r)>>1;
    update(l,mid,id<<1,tl,tr,val);update(mid+1,r,id<<1|1,tl,tr,val);
    tree[id]=tree[id<<1]+tree[id<<1|1];
}
int query(int l,int r,int id,int tl,int tr){
    if(tr<l || r<tl) return 0;
    if(tl<=l && r<=tr) return tree[id];
    pushdown(l,r,id);
    int mid=(l+r)>>1;
    return query(l,mid,id<<1,tl,tr)+query(mid+1,r,id<<1|1,tl,tr);
}

void solve(){
    cin >> n >> D;
    for(int i=1;i<=n;i++){
        cin >> c[i];
        if(i>1 && c[i]%D<c[i-1]%D) p[i]++;
        p[i]+=p[i-1];
        cc[i]=c[i]/D-p[i];
        pre[i]=pre[i-1]+cc[i];
        //cout << cc[i] << '\n';
    }
    cin >> q;
    for(int i=1;i<=q;i++){
        int l,r;cin >> l >> r;
        qq[r].push_back({l,i});
    }
    vector<int> v;
    for(int i=1;i<=n;i++){
        while(!v.empty() && cc[v.back()]>=cc[i]){
            int r=v.back();v.pop_back();
            int l=(v.empty()?1:v.back()+1);
            update(1,n,1,l,r,-cc[r]);
        }
        int L=(v.empty()?1:v.back()+1);
        update(1,n,1,L,i,cc[i]);
        v.push_back(i);
        for(auto [l,id]:qq[i]){
            int Min=query(1,n,1,l,l);
            if(Min+p[l]<0) ans[id]=-1;
            else ans[id]=pre[i]-pre[l-1]-query(1,n,1,l,i);
        }
    }
    for(int i=1;i<=q;i++) cout << ans[i] << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}

