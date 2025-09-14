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
#define ld long double
#define pii pair<int,int>
#define piii pair<pii,int>
#define mpp make_pair
#define fi first
#define se second
const int mod=998244353;
const int maxn=500005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=20;
const int maxa=1000000;
const int root=3;
const int base=101;

int n,m,l[maxn],r[maxn],cnt[maxn];
vector<int> com;

namespace Segtree{
    pii tree[4*maxn];
    void update(int l,int r,int id,int tl,int tr,pii val){
        if(tr<l || r<tl) return;
        if(tl<=l && r<=tr){
            tree[id]=max(tree[id],val);
            return;
        }
        int mid=(l+r)>>1;
        update(l,mid,id<<1,tl,tr,val);update(mid+1,r,id<<1|1,tl,tr,val);
    }
    pii query(int l,int r,int id,int p){
        if(l==r) return tree[id];
        int mid=(l+r)>>1;
        if(p<=mid) return max(tree[id],query(l,mid,id<<1,p));
        else return max(tree[id],query(mid+1,r,id<<1|1,p));
    }
}
namespace BIT{
    int bit[maxn];
    void update(int x,int val){
        for(int i=x;i<=m+1;i+=(i&(-i))) bit[i]+=val;
    }
    int query(int x){
        int res=0;
        for(int i=x;i>=1;i-=(i&(-i))) res+=bit[i];
        return res;
    }
}
void solve(){
    cin >> n >> m;
    l[0]=0;r[0]=n+1;cnt[0]=n;
    com.push_back(0);
    for(int i=1;i<=m;i++){
        cin >> l[i] >> r[i];
        cnt[i]=r[i]-l[i]-1;
        com.push_back(l[i]);
    }
    int total=n/2;
    sort(com.begin(),com.end());
    for(int i=1;i<=m;i++){
        int pl=lower_bound(com.begin(),com.end(),l[i])-com.begin()+1;
        int pr=upper_bound(com.begin(),com.end(),r[i])-com.begin();
        int pos=Segtree::query(1,m+1,1,pl).se,sum=BIT::query(pr)-BIT::query(pl-1);
        total-=cnt[pos]/2;
        cnt[pos]=cnt[pos]+sum-(r[i]-l[i]+1);cnt[i]-=sum;
        total+=cnt[pos]/2+cnt[i]/2;
        Segtree::update(1,m+1,1,pl,pr,mpp(l[i],i));
        BIT::update(pl,(r[i]-l[i]+1)-sum);
        pl=lower_bound(com.begin(),com.end(),l[pos])-com.begin()+1;
        BIT::update(pl,sum-(r[i]-l[i]+1));
        cout << total << '\n';
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();

}
