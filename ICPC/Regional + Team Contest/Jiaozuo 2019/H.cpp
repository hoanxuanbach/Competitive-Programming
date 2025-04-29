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
const int maxn=200005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=25;
const int maxa=1000000;
const int root=3;
const int base=131;

int A[maxn];
pii Range[maxn];
vector<int> com;

int s[maxn];
namespace SA{
    int c[maxn],cn[maxn],p[maxn],r[maxn],r2[maxn],lcp[maxn],cnt[maxn];
    void init(int n){
        for(int i=0;i<=n+1;i++) c[i]=cn[i]=p[i]=r[i]=r2[i]=lcp[i]=cnt[i]=0;
    }
    void build(int n){
        int v=(int)com.size()+1;s[n++]=0;
        for(int i=0;i<n;i++) cnt[s[i]]++;
        for(int i=1;i<v;i++) cnt[i]+=cnt[i-1];
        for(int i=0;i<n;i++) c[--cnt[s[i]]]=i;
        r[c[0]]=0;v=1;
        for(int i=1;i<n;i++){
            if(s[c[i]]!=s[c[i-1]]) v++;
            r[c[i]]=v-1;
        }
        for(int len=2;len<=2*n;len<<=1){
            for(int i=0;i<n;i++) cn[i]=(c[i]+n-len/2)%n;
            for(int i=0;i<v;i++) cnt[i]=0;
            for(int i=0;i<n;i++) cnt[r[i]]++;
            for(int i=1;i<v;i++) cnt[i]+=cnt[i-1];
            for(int i=n-1;i>=0;i--) c[--cnt[r[cn[i]]]]=cn[i];
            r2[c[0]]=0;v=1;
            for(int i=1;i<n;i++){
                pii cur={r[c[i]],r[(c[i]+len/2)%n]};
                pii pre={r[c[i-1]],r[(c[i-1]+len/2)%n]};
                if(cur!=pre) v++;
                r2[c[i]]=v-1;
            }
            for(int i=0;i<n;i++) r[i]=r2[i];
        }


        for(int i=1;i<n;i++) p[c[i]]=i;
        int k=0;
        for(int i=0;i<n;i++){
            int u=p[i];
            if(u==n-1){lcp[u]=k=0;continue;}
            int j=c[u+1];
            while(i+k<n && j+k<n && s[i+k]==s[j+k]) k++;
            lcp[u]=k;
            if(k) k--;
        }
        for(int i=0;i<n;i++){
            int u=p[i];
            Range[i+1]={i+1+lcp[u],n-1};
        }
    }

}

namespace Segtree{
    long long tree[4*maxn];
    int lazy[4*maxn];

    void init(int n){
        for(int i=1;i<=4*n;i++) tree[i]=lazy[i]=0;
    }

    void getnew(int l,int r,int id,int val){
        lazy[id]=val;
        tree[id]=1LL*(r-l+1)*val;
    }

    void pushdown(int l,int r,int id){
        if(lazy[id]==0) return;
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

    long long query(int l,int r,int id,int tl,int tr){
        if(tr<l || r<tl) return 0;
        if(tl<=l && r<=tr) return tree[id];
        pushdown(l,r,id);
        int mid=(l+r)>>1;
        return query(l,mid,id<<1,tl,tr)+query(mid+1,r,id<<1|1,tl,tr);
    }
}

void solve(){
    int n;cin >> n;com.clear();
    SA::init(n);Segtree::init(n);
    for(int i=1;i<=n;i++){
        cin >> A[i];
        com.push_back(A[i]);
    }
    sort(com.begin(),com.end());
    com.erase(unique(com.begin(),com.end()),com.end());
    for(int i=1;i<=n;i++) s[i-1]=lower_bound(com.begin(),com.end(),A[i])-com.begin()+1;
    SA::build(n);
    long long ans=0;
    vector<int> v;
    for(int i=n;i>=1;i--){
        while(!v.empty() && A[i]>=A[v.back()]) v.pop_back();
        Segtree::update(1,n,1,i,(v.empty()?n:v.back()-1),A[i]);
        if(Range[i].fi<=Range[i].se) ans+=Segtree::query(1,n,1,Range[i].fi,Range[i].se);
        v.push_back(i);
    }
    cout << ans << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}
