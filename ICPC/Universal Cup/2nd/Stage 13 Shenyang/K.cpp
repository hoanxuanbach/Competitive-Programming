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
const int base=131;

int n,q,sz,a[maxn],cur=0;
pii qq[maxn];
vector<pii> p;

namespace Segtree{
    int sum[8*maxn],cnt[8*maxn];
    void update(int l,int r,int id,int pos,int val){
        if(l==r){
            cnt[id]+=val;
            sum[id]+=val*p[l-1].fi;
            return;
        }
        int mid=(l+r)>>1;
        if(pos<=mid) update(l,mid,id<<1,pos,val);
        else update(mid+1,r,id<<1|1,pos,val);
        cnt[id]=cnt[id<<1]+cnt[id<<1|1];
        sum[id]=sum[id<<1]+sum[id<<1|1];
    }
    void query(int l,int r,int id,int cc){
        if(l==r){
            cur+=cnt[id];
            if(cc+sum[id]<=0) cur++;
            return;
        }
        int mid=(l+r)>>1;
        if(cc+sum[id<<1]<=0){
            cur+=cnt[id<<1];
            return query(mid+1,r,id<<1|1,cc+sum[id<<1]);
        }
        else return query(l,mid,id<<1,cc);
    }
}

void solve(){
    cin >> n >> q;
    for(int i=1;i<=n;i++){
        cin >> a[i];
        p.push_back({a[i],i});
    }
    for(int i=1;i<=q;i++){
        cin >> qq[i].se >> qq[i].fi;
        p.push_back(qq[i]);
    }
    sort(p.begin(),p.end());
    p.erase(unique(p.begin(),p.end()),p.end());
    sz=(int)p.size();
    int cnt=0;
    for(int i=1;i<=n;i++){
        if(a[i]>0) cnt++;
        int pos=lower_bound(p.begin(),p.end(),mpp(a[i],i))-p.begin()+1;
        Segtree::update(1,sz,1,pos,1);
    }
    for(int i=1;i<=q;i++){
        int pre=lower_bound(p.begin(),p.end(),mpp(a[qq[i].se],qq[i].se))-p.begin()+1;
        Segtree::update(1,sz,1,pre,-1);
        if(a[qq[i].se]>0) cnt--;
        a[qq[i].se]=qq[i].fi;
        if(a[qq[i].se]>0) cnt++;
        int pos=lower_bound(p.begin(),p.end(),mpp(a[qq[i].se],qq[i].se))-p.begin()+1;
        Segtree::update(1,sz,1,pos,1);
        cur=0;Segtree::query(1,sz,1,0);
        //cout << cur << ' ';
        cout << cnt-(n-cur) << '\n';
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
