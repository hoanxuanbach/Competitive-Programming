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
const int maxn=500005;
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

int n,a[maxn],b[maxn];

int sz;
vector<int> com;
vector<pii> la[maxn],ra[maxn];

int use[2*maxn],lazy[8*maxn];

struct node{
    int Min=0,Min1=0,cnt=0;
    node(){};
    void add(int x){
        Min+=x;
        if(Min1!=inf) Min1+=x;
    }
    friend node operator+(node a,node b){
        node res;
        res.Min=min(a.Min,b.Min);
        res.Min1=min(a.Min1,b.Min1);
        res.cnt=(a.Min1==res.Min1)*a.cnt+(b.Min1==res.Min1)*b.cnt;
        return res;
    }
}tree[8*maxn];

void update(int l,int r,int id,int tl,int tr,int val){
    if(tr<l || r<tl) return;
    if(tl<=l && r<=tr){
        tree[id].add(val);
        lazy[id]+=val;
        return;
    }
    int mid=(l+r)>>1;
    update(l,mid,id<<1,tl,tr,val);update(mid+1,r,id<<1|1,tl,tr,val);
    tree[id]=tree[id<<1]+tree[id<<1|1];
    tree[id].add(lazy[id]);
}

void build(int l,int r,int id){
    if(l==r){
        if(!use[l]) tree[id].Min1=inf;
        else tree[id].cnt=1;
        return;
    }
    int mid=(l+r)>>1;
    build(l,mid,id<<1);build(mid+1,r,id<<1|1);
    tree[id]=tree[id<<1]+tree[id<<1|1];
}

void solve(){
    cin >> n;
    for(int i=1;i<=n;i++) cin >> a[i],com.push_back(a[i]);
    for(int i=1;i<=n;i++) cin >> b[i],com.push_back(b[i]);
    
    sort(com.begin(),com.end());
    com.erase(unique(com.begin(),com.end()));
    sz=(int)com.size()+1;
    for(int i=1;i<=n;i++) a[i]=lower_bound(com.begin(),com.end(),a[i])-com.begin()+1;
    for(int i=1;i<=n;i++){
        b[i]=lower_bound(com.begin(),com.end(),b[i])-com.begin()+1;
        use[b[i]+1]=1;
    }
    vector<pii> v;
    for(int i=1;i<=n;i++){
        int cnt=1;
        while(!v.empty() && v.back().first>=a[i]){
            la[i].push_back({v.back().first,-v.back().second});
            cnt+=v.back().second;v.pop_back();
        }
        la[i].push_back({a[i],cnt});
        v.push_back({a[i],cnt});
    }

    v.clear();
    for(int i=n;i>=1;i--){
        int cnt=1;
        while(!v.empty() && v.back().first>=a[i]){
            ra[i].push_back({v.back().first,-v.back().second});
            cnt+=v.back().second;v.pop_back();
        }
        ra[i].push_back({a[i],cnt});
        v.push_back({a[i],cnt});
    }

    build(1,sz,1);
    for(auto &[x,d]:v){
        update(1,sz,1,1,x,d);
        //cout << "add " << x << ' ' << d << '\n';
    }
    for(int i=1;i<=n;i++) update(1,sz,1,1,b[i],-1);

    int res=inf;
    for(int i=1;i<=n;i++){
        for(auto &[x,d]:la[i]) update(1,sz,1,1,x,d);
        for(auto &[x,d]:ra[i-1]) update(1,sz,1,1,x,-d);
        update(1,sz,1,1,a[i],-1);

        if(tree[1].Min>=0) res=min(res,(tree[1].Min1==0?tree[1].cnt:0LL));
        update(1,sz,1,1,a[i],1);
    }
    cout << (res==inf?-1:res) << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
