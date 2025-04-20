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
#define piii pair<pii,int>
#define mpp make_pair
#define fi first
#define se second
const int inf=2e9;
const int mod=998244353;
const int maxn=200005;
const int B=650;
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

int nxt[maxn][maxl];
int n,Max[maxn];
piii p[maxn];
set<pii> ss;

int get(int l,int r){
    int pos=lower_bound(Max+1,Max+n+1,l)-Max;
    if(pos>n || p[pos].fi.fi>r) return 0;
    int val=1;
    for(int i=17;i>=0;i--){
        int u=nxt[pos][i];
        if(u<=n && p[u].fi.fi<=r) val+=(1<<i),pos=u;
    }
    return val;
}

void update(int l,int r){
    ss.insert({l,r});
}

bool query(int l,int r){
    auto it=ss.lower_bound({l,0});
    if(it!=ss.end()){
        pii x=*it;
        if(max(x.fi,l)<=min(x.se,r)) return true;
    }
    if(it!=ss.begin()){
        it--;
        pii x=*it;
        if(max(x.fi,l)<=min(x.se,r)) return true;
    }
    return false;
}

int l[maxn],r[maxn];
void solve(){
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> l[i] >> r[i];
        p[i]={{r[i],l[i]},i};
    }
    sort(p+1,p+n+1);
    for(int i=1;i<=n;i++) Max[i]=max(Max[i-1],p[i].fi.se);
    int pos=1;
    for(int i=1;i<=n;i++){
        while(pos<=n && Max[pos]<=p[i].fi.fi) pos++;
        nxt[i][0]=pos;
    }
    nxt[n+1][0]=n+1;
    for(int i=1;i<18;i++) for(int j=1;j<=n+1;j++) nxt[j][i]=nxt[nxt[j][i-1]][i-1];
    ss.insert({-inf,-inf});
    ss.insert({inf,inf});
    vector<int> ans;
    for(int i=1;i<=n;i++){
        if(query(l[i],r[i])) continue;
        auto it=ss.lower_bound({l[i],0});
        int R=it->fi-1;it--;
        int L=it->se+1;
        int cnt=get(L,R)-get(L,l[i]-1)-get(r[i]+1,R)-1;
        if(!cnt){
            ans.push_back(i);
            update(l[i],r[i]);
        }
    }
    cout << (int)ans.size() << '\n';
    for(int x:ans) cout << x << ' ';
    cout << '\n';

}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}

