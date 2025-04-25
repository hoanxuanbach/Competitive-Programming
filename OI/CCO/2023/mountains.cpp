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
const int mod=1e6+3;
const int maxn=1000005;
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

int n,h[maxn],tree[4*maxn];

void build(int l,int r,int id){
    if(l==r){
        tree[id]=h[l];
        return;
    }
    int mid=(l+r)>>1;
    build(l,mid,id<<1);build(mid+1,r,id<<1|1);
    tree[id]=min(tree[id<<1],tree[id<<1|1]);
}
void update(int l,int r,int id,int p){
    if(l==r){
        tree[id]=inf;
        return;
    }
    int mid=(l+r)>>1;
    if(p<=mid) update(l,mid,id<<1,p);
    else update(mid+1,r,id<<1|1,p);
    tree[id]=min(tree[id<<1],tree[id<<1|1]);
}

int query(int l,int r,int id,int tl,int tr){
    if(tr<l || r<tl) return inf;
    if(tl<=l && r<=tr) return tree[id];
    int mid=(l+r)>>1;
    return min(query(l,mid,id<<1,tl,tr),query(mid+1,r,id<<1|1,tl,tr));
}
map<int,vector<int>> add,del;
set<int> s;

int cal(int l,int r){
    if(s.empty()) return 0;
    int res=0;
    int x=*s.begin(),y=*s.rbegin();
    int lx=query(1,n,1,1,x),ry=query(1,n,1,y,n);
    int sum=((r-l)*(l+r-1)/2)%mod;
    if(x==y) return ((lx+ry)*(r-l)+sum)%mod;
    int add=lx+ry+r;
    res=(res+add*(r-l))%mod;
    int sz=(int)s.size();
    res=((res+(3*sum+2*(r-l))*(sz-1)-(r-l))%mod+mod)%mod;
    return res;
}

void solve(){
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> h[i];
        add[h[i]].push_back(i);
    }
    build(1,n,1);
    int p=max_element(h+1,h+n+1)-h;
    for(int i=1;i<=p;i++) h[i]=max(h[i],h[i-1]);
    for(int i=n;i>=p;i--) h[i]=max(h[i],h[i+1]);
    for(int i=1;i<=n;i++) del[h[i]].push_back(i);
    int pre=-1,ans=0;
    for(auto &it:add){
        if(pre!=-1) ans=(ans+cal(pre,it.fi))%mod;
        for(int x:it.se){
            s.insert(x);
            update(1,n,1,x);
        }
        for(int x:del[it.fi]) s.erase(x);
        pre=it.fi;
    }
    cout << ans << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}