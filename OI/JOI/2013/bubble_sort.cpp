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
const int maxn=100005;
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

namespace Segtree{
    int tree[4*maxn],lazy[4*maxn];
    void update(int l,int r,int id,int tl,int tr,int val){
        if(tr<l || r<tl) return;
        if(tl<=l && r<=tr){
            tree[id]+=val;
            lazy[id]+=val;
            return;
        }
        int mid=(l+r)>>1;
        update(l,mid,id<<1,tl,tr,val);update(mid+1,r,id<<1|1,tl,tr,val);
        tree[id]=max(tree[id<<1],tree[id<<1|1])+lazy[id];
    }
}

int sz;
vector<int> com;
namespace BIT{
    int bit[maxn];
    void update(int x){
        for(int i=x;i<=sz;i+=(i&(-i))) bit[i]++;
    }
    int query(int x){
        int res=0;
        for(int i=x;i>=1;i-=(i&(-i))) res+=bit[i];
        return res;
    }
}
struct rec{
    int x,y,u,v;
};
int n,a[maxn];
int lt[maxn][2],rt[maxn][2];

vector<pii> dd[maxn];

void solve(){
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> a[i];
        com.push_back(a[i]);
    }
    sort(com.begin(),com.end());
    com.erase(unique(com.begin(),com.end()),com.end());
    sz=(int)com.size();
    int total=0;
    for(int i=n;i>=1;i--){
        a[i]=lower_bound(com.begin(),com.end(),a[i])-com.begin()+1;
        total+=BIT::query(a[i]-1);
        BIT::update(a[i]);
    }
    if(!total){
        for(int i=2;i<=n;i++){
            if(a[i]==a[i-1]){
                cout << 0 << '\n';
                return;
            }
        }
        cout << 1 << '\n';
        return;
    }
    vector<pii> d;
    for(int i=1;i<=n;i++){
        int pos=lower_bound(d.begin(),d.end(),mpp(a[i],0LL))-d.begin();
        lt[i][0]=(pos==(int)d.size()?i:d[pos].se);
        if(pos<(int)d.size() && d[pos].fi==a[i]) pos++;
        lt[i][1]=(pos==(int)d.size()?i:d[pos].se);
        //cout << lt[i][0] << ' ' << lt[i][1] << '\n';
        if(d.empty() || a[i]>d.back().fi) d.push_back({a[i],i});
    }
    d.clear();
    for(int i=n;i>=1;i--){
        int pos=lower_bound(d.begin(),d.end(),a[i],[](pii x,int val){
                return x.fi>val;
        })-d.begin();
        rt[i][0]=(pos==(int)d.size()?i:d[pos].se);
        if(pos<(int)d.size() && d[pos].fi==a[i]) pos++;
        rt[i][1]=(pos==(int)d.size()?i:d[pos].se);
        if(d.empty() || a[i]<d.back().fi) d.push_back({a[i],i});
    }
    auto add = [&](int x,int u,int y,int v){
        dd[x].push_back({y,v});
        dd[u+1].push_back({-y,-v});
    };
    for(int i=1;i<=n;i++){
        for(int j=0;j<=1;j++){
            int l=lt[i][j],r=rt[i][j^1];
            if(l==i || r==i) continue;
            add(l,i-1,i+1,r);
        }
    }
    int Max=0;
    for(int i=1;i<=n;i++){
        for(auto [l,r]:dd[i]){
            if(l>0) Segtree::update(1,n,1,l,r,1);
            else Segtree::update(1,n,1,-l,-r,-1);
        }
        Max=max(Max,Segtree::tree[1]);
    }
    cout << total-Max-1 << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
