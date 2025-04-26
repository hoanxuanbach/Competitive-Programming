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
const int maxn=100005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=20;
const int maxa=1000000;
const int root=3;
const int base=101;

int d[maxn],cnt[4*maxn];
vector<int> tree[4*maxn];
queue<int> q;

void update(int l,int r,int id,int tl,int tr,int t){
    if(tr<l || r<tl) return;
    if(tl<=l && r<=tr){
        tree[id].push_back(t);
        d[t]++;
        return;
    }
    int mid=(l+r)>>1;
    update(l,mid,id<<1,tl,tr,t);update(mid+1,r,id<<1|1,tl,tr,t);
}


void query(int l,int r,int id,int p){
    cnt[id]++;
    if(cnt[id]==(r-l+1)){
        for(int u:tree[id]){
            d[u]--;
            if(d[u]==0) q.push(u);
        }
    }
    if(l==r) return;
    int mid=(l+r)>>1;
    if(p<=mid) query(l,mid,id<<1,p);
    else query(mid+1,r,id<<1|1,p);
}

int n,m,l[maxn],r[maxn];
vector<int> drill[maxn];
vector<pii> hole[maxn];
int pos[maxn];

void solve(){
    cin >> n;
    vector<pii> com;
    for(int i=1;i<=n;i++) cin >> l[i] >> r[i];
    cin >> m;
    for(int i=1;i<=m;i++){
        int x,k;cin >> x >> k;
        if(k==0) continue;
        com.push_back({x,i});
        drill[i].resize(k);
        for(int j=0;j<k;j++){
            cin >> drill[i][j];
            d[drill[i][j]]+=j;
            hole[drill[i][j]].push_back({x,i});
        }
    }
    sort(com.begin(),com.end());
    int sz=(int)com.size();
    auto cal = [&](int lt,int rt,int t){
        if(lt>rt) return;
        int pl=lower_bound(com.begin(),com.end(),mpp(lt,0))-com.begin()+1;
        int pr=upper_bound(com.begin(),com.end(),mpp(rt,m))-com.begin();
        if(pl<=pr) update(1,sz,1,pl,pr,t);
    };
    for(int i=1;i<=n;i++){
        sort(hole[i].begin(),hole[i].end());
        int pre=l[i];
        for(auto [x,id]:hole[i]) cal(pre,x-1,i),pre=x+1;
        cal(pre,r[i],i);
    }
    for(int i=1;i<=n;i++){
        if(d[i]==0) q.push(i);
    }
    vector<int> res;
    while(!q.empty()){
        int u=q.front();q.pop();
        res.push_back(u);
        for(auto [x,id]:hole[u]){
            pos[id]++;
            if(pos[id]==(int)drill[id].size()){
                int v=lower_bound(com.begin(),com.end(),mpp(x,id))-com.begin()+1;
                query(1,sz,1,v);
            }
            else{
                int v=drill[id][pos[id]];
                d[v]-=pos[id];
                if(d[v]==0) q.push(v);
            }
        }
    }
    for(int v:res) cout << v << ' ';
    cout << '\n';
}

signed main(){
    //freopen("DRILL.INP","r",stdin);
    //freopen("DRILL.OUT","w",stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
