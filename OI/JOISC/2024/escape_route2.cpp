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
#define ll long long
#define ld long double
#define pii pair<int,int>
#define pil pair<int,ll>
#define piii pair<int,pii>
#define mpp make_pair
#define fi first
#define se second
const ll inf=1e18;
const int mod=998244353;
const int maxn=100005;
const int B=50;
const int maxs=655;
const int maxm=200005;
const int maxq=300005;
const int maxl=25;
const int maxa=1000000;
const int root=3;
const int base=101;

int N,T,Q,M[maxn];
vector<pii> P[maxn];
vector<int> jmp[maxn];
vector<pil> tree[4*maxn];

void build(int l,int r,int id){
    if(l==r){
        for(int i=0;i<M[l];i++) tree[id].push_back({i,P[l][i].se-P[l][i].fi});
        return;
    }
    int mid=(l+r)>>1;
    build(l,mid,id<<1);build(mid+1,r,id<<1|1);
    for(int i=0;i<M[l];i++){
        auto [p,val]=tree[id<<1][i];
        int cc=P[mid][p].se,pos=jmp[mid][p];
        int nxt=P[mid+1][pos].fi;
        tree[id].push_back({tree[id<<1|1][pos].fi,val+(nxt-cc+T)%T+tree[id<<1|1][pos].se});
    }
}
pil query(int l,int r,int id,int tl,int tr,pil cur){
    if(tr<l || r<tl) return cur;
    if(tl<=l && r<=tr){
        auto [p,val]=cur;
        int cc=P[l-1][p].se,pos=jmp[l-1][p];
        int nxt=P[l][pos].fi;
        return {tree[id][pos].fi,val+(nxt-cc+T)%T+tree[id][pos].se};
    }
    int mid=(l+r)>>1;
    return query(mid+1,r,id<<1|1,tl,tr,query(l,mid,id<<1,tl,tr,cur));
}

int f[maxn],cnt;
ll D[2005][maxn];

void build_ans(int i){
    int t=f[i];
    vector<ll> cur(M[i]);
    D[t][i]=inf;
    for(int j=0;j<M[i];j++){
        cur[j]=P[i][j].se-P[i][j].fi;
        D[t][i]=min(D[t][i],cur[j]);
    }
    for(int r=i+1;r<N;r++){
        D[t][r]=inf;
        vector<ll> nw(M[r],inf);
        for(int j=0;j<M[r-1];j++){
            if(cur[j]==inf) continue;
            int cc=P[r-1][j].se,pos=jmp[r-1][j];
            int nxt=P[r][pos].fi;
            nw[pos]=min(nw[pos],cur[j]+(nxt-cc+T)%T+P[r][pos].se-P[r][pos].fi);
        }
        swap(cur,nw);
        for(int j=0;j<M[r];j++) D[t][r]=min(D[t][r],cur[j]);
    }
}

void solve(){
    cin >> N >> T;
    for(int i=1;i<N;i++){
        cin >> M[i];
        P[i].resize(M[i]);
        for(int j=0;j<M[i];j++) cin >> P[i][j].fi >> P[i][j].se;
        sort(P[i].begin(),P[i].end());
        vector<pii> cc;
        for(auto [x,y]:P[i]){
            while(!cc.empty() && cc.back().se>=y) cc.pop_back();
            if(cc.empty() || cc.back().fi!=x) cc.push_back({x,y});
        }
        P[i]=cc;
        M[i]=(int)cc.size();
        if(M[i]>B) f[i]=++cnt;
    }
    for(int i=1;i<N-1;i++){
        jmp[i].resize(M[i]);
        for(int j=0;j<M[i];j++){
            int cc=P[i][j].se;
            int pos=lower_bound(P[i+1].begin(),P[i+1].end(),mpp(cc,0))-P[i+1].begin();
            jmp[i][j]=pos%M[i+1];
        }
    }
    for(int i=1;i<N;i++){
        if(M[i]>B) build_ans(i);
    }
    build(1,N-1,1);
    cin >> Q;
    for(int i=1;i<=Q;i++){
        int l,r;cin >> l >> r;r--;
        if(M[l]<=B){
            ll ans=inf;
            for(int j=0;j<M[l];j++){
                if(l+1<=r) ans=min(ans,query(1,N-1,1,l+1,r,{j,P[l][j].se-P[l][j].fi}).se);
                else ans=min(ans,1LL*(P[l][j].se-P[l][j].fi));
            }
            cout << ans << '\n';
        }
        else cout << D[f[l]][r] << '\n';
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
