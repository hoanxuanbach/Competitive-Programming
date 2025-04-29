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

int n,q,L[maxn],R[maxn],cnt;
vector<int> edge[maxn];

namespace BIT{
    int bit[maxn];
    void update(int x,int val){
        for(int i=x;i<=n;i+=(i&(-i))) bit[i]+=val;
    }
    int query(int x){
        int res=0;
        for(int i=x;i>=1;i-=(i&(-i))) res+=bit[i];
        return res;
    }
}

void dfs(int u){
    L[u]=++cnt;
    for(int v:edge[u]) dfs(v);
    R[u]=cnt;
}

int pos[maxn],f[maxn];
int X[maxn],A[maxn],B[maxn],Y[maxn];
vector<int> qq[maxn],cc;

void dfs2(int u){
    f[u]=(int)cc.size();
    cc.push_back(u);

    BIT::update(u,R[u]-L[u]+1);
    for(int id:qq[u]){
        int l=1,r=n,cur=0;
        while(l<=r){
            int mid=(l+r)>>1;
            //cout << mid << ' ' << BIT::query(mid) << '\n';
            if(BIT::query(mid)<pos[id]) l=mid+1;
            else cur=mid,r=mid-1;
        }
        A[id]=cur;
        B[id]=f[cur]+1;
        B[id]=(B[id]<(int)cc.size()?cc[B[id]]:-1);
        pos[id]-=BIT::query(cur-1);
        //cout << id << ' ' << pos[id] << ' ' << A[id] << ' ' << B[id] << ' ' << X[id] << '\n';
    }
    for(int v:edge[u]){
        BIT::update(u,-(R[v]-L[v]+1));
        dfs2(v);
        BIT::update(u,R[v]-L[v]+1);
    }
    cc.pop_back();
    BIT::update(u,-(R[u]-L[u]+1));
}

void solve(){
    cin >> n >> q;
    int root=-1;
    for(int i=1;i<=n;i++){
        int p;cin >> p;
        if(p) edge[p].push_back(i);
        else root=i;
    }
    dfs(root);
    for(int i=1;i<=q;i++){
        cin >> pos[i];
        X[i]=(pos[i]-1)/n+1;
        pos[i]=(pos[i]-1)%n+1;
        qq[X[i]].push_back(i);
    }
    dfs2(root);
    for(int i=1;i<=n;i++) qq[i].clear();
    for(int i=1;i<=q;i++) qq[(n+1)/2].push_back(i);
    function<void(int,int)> dnc = [&](int l,int r){
        int mid=(l+r)>>1;
        for(int i=l;i<=mid;i++) BIT::update(L[i],1);
        for(int id:qq[mid]){
            int total=BIT::query(R[A[id]])-BIT::query(L[A[id]]-1);
            if(B[id]!=-1) total-=BIT::query(R[B[id]])-BIT::query(L[B[id]]-1);
            //cout << id << ' ' << mid << ' ' << total << '\n';
            if(total>=pos[id]){
                Y[id]=mid;
                if(l<mid) qq[(l+mid-1)/2].push_back(id);
            }
            else if(mid<r) qq[(mid+1+r)/2].push_back(id);
        }
        if(mid<r) dnc(mid+1,r);
        for(int i=mid;i>=l;i--) BIT::update(L[i],-1);
        if(l<mid) dnc(l,mid-1);
    };
    dnc(1,n);
    for(int i=1;i<=q;i++){
        int res=(X[i]-1)*n*n+(A[i]-1)*n+(Y[i]-1);
        cout << res << '\n';
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
