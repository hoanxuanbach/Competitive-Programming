
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
#define piii pair<int,pii>
#define mpp make_pair
#define fi first
#define se second
const int inf=1e8;
const int mod=998244353;
const int maxn=300005;
const int B=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=25;
const int maxa=1000000;
const int root=3;
const int base=101;

int n,k,q,sz,res[maxn];
vector<int> com;
vector<piii> cc;
multiset<int> ss[maxn],rr[maxn];

int Max[4*maxn];
void update(int l,int r,int id,int p){
    if(l==r){
        Max[id]=(rr[l].empty()?0:*rr[l].rbegin());
        return;
    }
    int mid=(l+r)>>1;
    if(p<=mid) update(l,mid,id<<1,p);
    else update(mid+1,r,id<<1|1,p);
    Max[id]=max(Max[id<<1],Max[id<<1|1]);
}
int query(int l,int r,int id,int p){
    if(l==r) return Max[id];
    int mid=(l+r)>>1;
    if(p<=mid) return query(l,mid,id<<1,p);
    else return max(Max[id<<1],query(mid+1,r,id<<1|1,p));
}

void add_range(int l,int r){
    int pos=lower_bound(com.begin(),com.end(),l)-com.begin()+1;
    //cout << "add_range " << l << ' ' << r << ' ' << pos << endl;
    rr[pos].insert(r);
    update(1,sz,1,pos);
}

void del_range(int l,int r){
    int pos=lower_bound(com.begin(),com.end(),l)-com.begin()+1;
    //cout << "del_rane " << l << ' ' << r << ' ' << pos << endl;
    rr[pos].erase(rr[pos].find(r));
    update(1,sz,1,pos);
}

void add(int t,int x){
    //cout << "add " << t << ' ' << x << '\n';
    auto it=ss[t].lower_bound(x);
    int l=1,r=(it==ss[t].end()?inf:*it-1);
    if(it!=ss[t].begin()) it--,l=*it+1;
    del_range(l,r);
    add_range(l,x-1);
    add_range(x+1,r);
    ss[t].insert(x);
}

void del(int t,int x){
    auto it=ss[t].lower_bound(x);
    it=ss[t].erase(it);
    int l=1,r=(it==ss[t].end()?inf:*it-1);
    if(it!=ss[t].begin()) it--,l=*it+1;
    del_range(l,x-1);
    del_range(x+1,r);
    add_range(l,r);
}

int query(int x){
    int l=0,r=max(inf-x,x),ans=-1;
    while(l<=r){
        int mid=(l+r)>>1;
        int L=max(x-mid,1),R=min(x+mid,inf);
        int pos=upper_bound(com.begin(),com.end(),L)-com.begin();
        int val=query(1,sz,1,pos);
        if(R<=val) l=mid+1;
        else ans=mid,r=mid-1;
    }
    return ans;
}

void solve(){
    cin >> n >> k >> q;
    com.push_back(1);
    for(int i=1;i<=n;i++){
        int x,t,a,b;cin >> x >> t >> a >> b;
        com.push_back(x+1);
        cc.push_back({a,{t,x}});
        cc.push_back({b+1,{-t,x}});
    }
    for(int i=1;i<=q;i++){
        int l,y;cin >> l >> y;
        cc.push_back({y,{inf+i,l}});
    }
    sort(cc.begin(),cc.end());
    sort(com.begin(),com.end());
    com.erase(unique(com.begin(),com.end()),com.end());
    sz=(int)com.size();
    for(int i=1;i<=k;i++) rr[1].insert(inf);
    update(1,sz,1,1);
    for(auto [_,p]:cc){
        auto [t,x]=p;
        if(t<0) del(-t,x);
        else if(t<=k) add(t,x);
        else{
            t-=inf;
            res[t]=query(x);
        }
    }
    for(int i=1;i<=q;i++) cout << res[i] << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
