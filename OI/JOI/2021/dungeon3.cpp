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
const int maxa=1e9;
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

int n,m,B[maxn],X[maxn];
int ans[maxn];

namespace Segtree{
    pii tree[4*maxn];
    int dist[4*maxn];
    void build(int l,int r,int id){
        if(l==r){
            dist[id]=X[l+1]-X[l];
            tree[id]={B[l],l};
            return;
        }
        int mid=(l+r)>>1;
        build(l,mid,id<<1);build(mid+1,r,id<<1|1);
        tree[id]=min(tree[id<<1],tree[id<<1|1]);
        dist[id]=max(dist[id<<1],dist[id<<1|1]);
    }
    pii query(int l,int r,int id,int tl,int tr){
        if(tr<X[l] || X[r]<tl) return {inf,-1};
        if(tl<=X[l] && X[r]<=tr) return tree[id];
        int mid=(l+r)>>1;
        return min(query(l,mid,id<<1,tl,tr),query(mid+1,r,id<<1|1,tl,tr));
    }
    int query_dist(int l,int r,int id,int tl,int tr){
        if(tr<l || r<tl) return -inf;
        if(tl<=l && r<=tr) return dist[id];
        int mid=(l+r)>>1;
        return max(query_dist(l,mid,id<<1,tl,tr),query_dist(mid+1,r,id<<1|1,tl,tr));
    }
}

vector<int> cc[maxn];
vector<pii> qq[maxn];
int L[maxn],R[maxn];

int sz;
vector<int> com;
int get_pos(int U){
    return lower_bound(com.begin(),com.end(),U)-com.begin()+1;
}

namespace ST{
    int tree[4*maxn],mul[4*maxn];
    void update(int l,int r,int id,int tl,int tr,int val,int num){
        if(tr<l || r<tl) return;
        if(tl<=l && r<=tr){
            tree[id]+=num;
            mul[id]+=val;
            return;
        }
        int mid=(l+r)>>1;
        update(l,mid,id<<1,tl,tr,val,num);update(mid+1,r,id<<1|1,tl,tr,val,num);
    }
    int query(int l,int r,int id,int p){
        int val=tree[id]+mul[id]*com[p-1];
        if(l==r) return val;
        int mid=(l+r)>>1;
        if(p<=mid) return query(l,mid,id<<1,p)+val;
        else return query(mid+1,r,id<<1|1,p)+val;
    }
}

void solve(){
    cin >> n >> m;
    for(int i=1;i<=n;i++) cin >> X[i+1],X[i+1]+=X[i];
    for(int i=1;i<=n;i++) cin >> B[i];
    Segtree::build(1,n,1);
    for(int i=1;i<=m;i++){
        int S,T,U;cin >> S >> T >> U;
        com.push_back(U);
        int D=Segtree::query_dist(1,n,1,S,T-1);
        if(D>U) ans[i]=-1;
        else{
            int T2=Segtree::query(1,n,1,max(X[S],X[T]-U),X[T]).se;
            ans[i]+=(X[T]-X[T2])*B[T2];
            //cout << T2 << '\n';
            qq[S].push_back({U,i});
            qq[T2].push_back({U,-i});
        }
    }

    sort(com.begin(),com.end());
    com.erase(unique(com.begin(),com.end()),com.end());
    sz=(int)com.size();

    vector<int> v;
    for(int i=1;i<=n;i++){
        while(!v.empty() && B[v.back()]>B[i]) v.pop_back();
        L[i]=(v.empty()?0:v.back());
        cc[L[i]].push_back(i);
        v.push_back(i);
    }
    v.clear();
    for(int i=n;i>=1;i--){
        while(!v.empty() && B[v.back()]>=B[i]) v.pop_back();
        R[i]=(v.empty()?n+1:v.back());
        v.push_back(i);
    }

    for(int i=n;i>=1;i--){
        int d = X[R[i]]-X[i];
        // U > d (X_i + U -> X_{R_i})*B_i
        int pd=get_pos(d);
        if(pd>1) ST::update(1,sz,1,1,pd-1,B[i],X[i]*B[i]);
        if(pd<=sz) ST::update(1,sz,1,pd,sz,0,X[R[i]]*B[i]);
        ST::update(1,sz,1,1,sz,0,-X[i]*B[i]);

        for(int j:cc[i]){
            int d1=X[j]-X[i],d2=X[R[j]]-X[j];
            int pd1=get_pos(d1);
            int pd3=get_pos(d1+d2);
            //U > d1 {X_i -> X_{L_i}+U}
            if(pd1<=sz) ST::update(1,sz,1,pd1,sz,-B[j],(X[j]-X[i])*B[j]);
            //U > d1 + d2 -> 0
            if(pd3<=sz) ST::update(1,sz,1,pd3,sz,B[j],-X[R[j]]*B[j]+X[i]*B[j]);
        }
        for(auto [U,id]:qq[i]){
            int val=ST::query(1,sz,1,get_pos(U));
            //cout << id << ' ' << val << '\n';
            if(id>0) ans[id]+=val;
            else ans[-id]-=val;
        }
    }
    for(int i=1;i<=m;i++) cout << ans[i] << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
