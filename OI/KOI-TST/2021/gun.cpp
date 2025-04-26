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
//#define int long long
#define ld long double
#define pii pair<int,int>
#define piii pair<int,pii>
#define mpp make_pair
#define fi first
#define se second
const long long inf=1e18;
const int mod=998244353;
const int maxn=100005;
const int B=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=25;
const int maxa=1000000;
const int root=3;
const int base=101;

struct BIT{
    int sz;
    vector<int> com,bit;
    void add(int x){
        com.push_back(x);
    }
    void build(){
        sort(com.begin(),com.end());
        com.erase(unique(com.begin(),com.end()),com.end());
        sz=(int)com.size();bit.assign(sz,0);
    }
    void update(int x,int val){
        x=lower_bound(com.begin(),com.end(),x)-com.begin()+1;
        for(int i=x;i<=sz;i+=(i&(-i))) bit[i-1]=max(bit[i-1],val);
    }
    int query(int x){
        x=upper_bound(com.begin(),com.end(),x)-com.begin();
        int res=0;
        for(int i=x;i>=1;i-=(i&(-i))) res=max(res,bit[i-1]);
        return res;
    }
};

struct Segtree{
    BIT tree[4*maxn];
    void pre_update(int l,int r,int id,int x,int y){
        tree[id].add(y);
        if(l==r) return;
        int mid=(l+r)>>1;
        if(x<=mid) pre_update(l,mid,id<<1,x,y);
        else pre_update(mid+1,r,id<<1|1,x,y);
    }
    void build(int n){
        for(int i=1;i<=4*n;i++) tree[i].build();
    }
    void update(int l,int r,int id,int x,int y,int val){
        tree[id].update(y,val);
        if(l==r) return;
        int mid=(l+r)>>1;
        if(x<=mid) update(l,mid,id<<1,x,y,val);
        else update(mid+1,r,id<<1|1,x,y,val);
    }
    int query(int l,int r,int id,int tl,int tr,int x){
        if(tr<l || r<tl) return 0;
        if(tl<=l && r<=tr) return tree[id].query(x);
        int mid=(l+r)>>1;
        return max(query(l,mid,id<<1,tl,tr,x),query(mid+1,r,id<<1|1,tl,tr,x));
    }
}S1,S2;

int n,A[maxn],level[maxn];
vector<int> pos[maxn];
int tin[maxn],T;

set<pii> ss;
struct Segtree2{
    pii tree[4*maxn];
    void update(int l,int r,int id,int p,pii val){
        if(l==r){
            tree[id]=val;
            return;
        }
        int mid=(l+r)>>1;
        if(p<=mid) update(l,mid,id<<1,p,val);
        else update(mid+1,r,id<<1|1,p,val);
        tree[id]=max(tree[id<<1],tree[id<<1|1]);
    }
    pii query(int l,int r,int id,int tl,int tr){
        if(tr<l || r<tl) return {0,0};
        if(tl<=l && r<=tr) return tree[id];
        int mid=(l+r)>>1;
        return max(query(l,mid,id<<1,tl,tr),query(mid+1,r,id<<1|1,tl,tr));
    }
}ST;

vector<pii> min_shooting_buildings(vector<int> _A){
    n=(int)_A.size();
    for(int i=0;i<n;i++) A[i+1]=_A[i];
    BIT cc;
    for(int i=1;i<=n;i++) cc.add(i);
    cc.build();
    for(int i=n;i>=1;i--){
        level[i]=cc.query(A[i])+1;
        cc.update(A[i],level[i]);
        pos[level[i]].push_back(i);
    }
    for(int i=1;i<=n;i++){
        S1.pre_update(1,n,1,i,A[i]);
        S2.pre_update(1,n,1,A[i],n-i+1);
    }
    S1.build(n);
    S2.build(n);
    for(int i=1;i<=n;i++){
        sort(pos[i].begin(),pos[i].end(),[](int x,int y){
            if(x<y){
                if(A[x]>A[y]) return false;
                else return S1.query(1,n,1,x,y-1,A[x])<S2.query(1,n,1,A[x]+1,A[y],n-y+1);
            }
            else{
                if(A[x]<A[y]) return true;
                else return S2.query(1,n,1,A[y]+1,A[x],n-x+1)<S1.query(1,n,1,y,x-1,A[y]);
            }
        });
        for(int x:pos[i]){
            tin[x]=++T;
            S1.update(1,n,1,x,A[x],T);
            S2.update(1,n,1,A[x],n-x+1,T);
        }
    }

    priority_queue<pii> pq;
    pii Max={0,0};
    for(int i=1;i<=n;i++){
        pii val={A[i],i};
        if(val>Max){
            Max=val;
            ss.insert(val);
            pq.push({tin[i],i});
        }
        ST.update(1,n,1,i,val);
    }
    auto del = [&](int x){
        pii val={A[x],x};
        ST.update(1,n,1,x,{0,0});
        ss.erase(val);
        auto it=ss.lower_bound(val);
        int r=(it==ss.end()?n:it->se-1);
        int pre=0;
        if(it!=ss.begin()){
            it--;
            pre=it->fi;
        }
        while(x<=r){
            pii num=ST.query(1,n,1,x,r);
            if(num.fi>pre){
                ss.insert(num);
                pq.push({tin[num.se],num.se});
            }
            else break;
            r=num.se-1;
        }
    };

    vector<pii> ans;
    while(!pq.empty()){
        int x=pq.top().se;pq.pop();
        if(!pq.empty()){
            int y=pq.top().se;pq.pop();
            del(y);
            ans.push_back({A[x],A[y]});
        }
        else ans.push_back({A[x],A[x]});
        del(x);
    }
    return ans;
}
/*
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
*/
