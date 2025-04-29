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
#pragma GCC target("popcnt,lzcnt")

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
const int maxn=250005;
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


int a[maxn],b[maxn],c[maxn],cnt[maxn];
namespace Segtree{
    int tree[4*maxn],add[4*maxn];
    void build(int l,int r,int id){
        if(l==r){
            tree[id]=cnt[l];
            return;
        }
        int mid=(l+r)>>1;
        build(l,mid,id<<1);build(mid+1,r,id<<1|1);
        tree[id]=min(tree[id<<1],tree[id<<1|1]);
    }

    void update(int l,int r,int id,int tl,int tr,int val){
        if(tr<l || r<tl) return;
        if(tl<=l && r<=tr){
            add[id]+=val;
            tree[id]+=val;
            return;
        }
        int mid=(l+r)>>1;
        update(l,mid,id<<1,tl,tr,val);update(mid+1,r,id<<1|1,tl,tr,val);
        tree[id]=min(tree[id<<1],tree[id<<1|1])+add[id];
    }
}

void solve(){
    int n,m;cin >> n >> m;
    for(int i=1;i<=n;i++) cin >> a[i],c[i]=a[i];
    for(int i=1;i<=m;i++) cin >> b[i],cnt[b[i]]++;
    sort(c+1,c+n+1,greater<int>());cnt[0]=0;
    for(int i=250000;i>=1;i--) cnt[i]+=cnt[i+1];
    for(int i=1;i<=n;i++) cnt[i]+=cnt[i-1]-c[i];
    Segtree::build(1,n,1);
    int q;cin >> q;
    for(int i=1;i<=q;i++){
        int id,p;cin >> id >> p;
        if(id==1){
            int l=1,r=n,pos=n+1;
            while(r>=l){
                int mid=(l+r)>>1;
                if(c[mid]<=a[p]) pos=mid,r=mid-1;
                else l=mid+1;
            }
            c[pos]++;a[p]++;
            Segtree::update(1,n,1,pos,n,-1);
        }
        else if(id==2){
            int l=1,r=n,pos=n+1;
            while(r>=l){
                int mid=(l+r)>>1;
                if(c[mid]<a[p]) pos=mid,r=mid-1;
                else l=mid+1;
            }
            pos--;c[pos]--;a[p]--;
            Segtree::update(1,n,1,pos,n,1);
        }
        else if(id==3){
            b[p]++;
            if(b[p]<=n) Segtree::update(1,n,1,b[p],n,1);
        }
        else if(id==4){
            if(b[p]<=n) Segtree::update(1,n,1,b[p],n,-1);
            b[p]--;
        }
        cout << (Segtree::tree[1]>=0?1:0) << '\n';
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
