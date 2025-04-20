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

multiset<int> l,r;
int sl,sr,cost,cc[maxn];

void update(){
    while((int)r.size()>(int)l.size()){
        int d=*r.begin();
        l.insert(d);sl+=d;
        r.erase(r.begin());sr-=d;
    }
    while((int)l.size()>(int)r.size()){
        int d=*l.rbegin();
        r.insert(d);sr+=d;
        l.erase(l.lower_bound(d));sl-=d;
    }
    int d=*r.begin();
    cost=d*(int)l.size()-sl+sr-d*(int)r.size();
}
void add(int x){
    if(r.empty() || *r.begin()>=x) l.insert(x),sl+=x;
    else r.insert(x),sr+=x;
    update();
}
bool cmp(pii x,pii y){
    if(x.fi+x.se!=y.fi+y.se) return x.fi+x.se<y.fi+y.se;
    else return x.fi<y.fi;
}
void solve(){
    int k,n,ans=0;cin >> k >> n;
    vector<pii> x;
    for(int i=1;i<=n;i++){
        char a,b;int xa,xb;cin >> a >> xa >> b >> xb;
        if(a==b) ans+=abs(xa-xb);
        else{
            ans++;
            if(xa>xb) swap(xa,xb);
            x.push_back({xa,xb});
        }
    }
    sort(x.begin(),x.end(),cmp);
    int sz=(int)x.size(),res=(sz!=0?inf:0);
    for(int i=0;i<sz;i++){
        add(x[i].fi);add(x[i].se);
        cc[i]=cost;
    }
    res=min(res,cc[sz-1]);
    l.clear();r.clear();sl=sr=0;
    if(k==2){
        for(int i=sz-1;i>=1;i--){
            add(x[i].fi);add(x[i].se);
            res=min(res,cost+cc[i-1]);
        }
    }
    cout << ans+res << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
/*
2 5
B 0 A 4
B 1 B 3
A 5 B 7
B 2 A 6
B 1 A 7
*/
