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
const int base=131;

struct ST{
    int L[4*maxn],R[4*maxn],nL[maxn],nR[maxn];
    void build(int l,int r,int id){
        if(l==r){
            L[id]=nL[l];
            R[id]=nR[r];
            return;
        }
        int mid=(l+r)>>1;
        build(l,mid,id<<1);build(mid+1,r,id<<1|1);
        L[id]=min(L[id<<1],L[id<<1|1]);
        R[id]=max(R[id<<1],R[id<<1|1]);
    }
    pii query(int l,int r,int id,int tl,int tr){
        if(tr<l || r<tl) return {inf,-inf};
        if(tl<=l && r<=tr) return {L[id],R[id]};
        int mid=(l+r)>>1;
        pii pl=query(l,mid,id<<1,tl,tr);
        pii pr=query(mid+1,r,id<<1|1,tl,tr);
        return {min(pl.fi,pr.fi),max(pl.se,pr.se)};
    }
}S[maxl];

int n,k,m;
vector<pii> pL[maxn],pR[maxn];

void solve(){
    cin >> n >> k >> m;
    for(int i=1;i<=m;i++){
        int l,r;cin >> l >> r;
        if(l<=r){
            int nl=min(r,l+k);
            pR[l].push_back({r,i});
            pR[nl].push_back({r,-i});
        }
        else{
            swap(l,r);
            int nr=max(l,r-k);
            pL[r].push_back({l,i});
            pL[nr].push_back({l,-i});
        }
    }
    set<pii> s;
    for(int i=1;i<=n;i++){
        for(auto x:pR[i]){
            if(x.se>0) s.insert(x);
            else s.erase({x.fi,-x.se});
        }
        S[0].nR[i]=i;
        if(!s.empty()) S[0].nR[i]=s.rbegin()->fi;
        //cout << S[0].nR[i] << ' ';
    }
    //cout << '\n';
    s.clear();
    for(int i=n;i>=1;i--){
        for(auto x:pL[i]){
            if(x.se>0) s.insert(x);
            else s.erase({x.fi,-x.se});
        }
        S[0].nL[i]=i;
        if(!s.empty()) S[0].nL[i]=s.begin()->fi;
        //cout << S[0].nL[i] << ' ';
    }
    //cout << '\n';
    S[0].build(1,n,1);
    for(int j=1;j<18;j++){
        for(int i=1;i<=n;i++){
            int l=S[j-1].nL[i],r=S[j-1].nR[i];
            tie(S[j].nL[i],S[j].nR[i])=S[j-1].query(1,n,1,l,r);
        }
        S[j].build(1,n,1);
    }
    int q;cin >> q;
    for(int i=1;i<=q;i++){
        int l,r,t,cnt=1;
        cin >> l >> t;r=l;
        for(int j=17;j>=0;j--){
            auto [nl,nr] = S[j].query(1,n,1,l,r);
            if(t<nl || nr<t) cnt+=(1<<j),l=nl,r=nr;
        }
        if(cnt==(1<<18)) cout << -1 << '\n';
        else cout << cnt << '\n';
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
