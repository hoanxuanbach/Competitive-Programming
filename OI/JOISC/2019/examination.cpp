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
#define piii pair<pii,pii>
#define mpp make_pair
#define fi first
#define se second
//const int inf=1e18;
const int mod=1e9+7;
const int maxn=100005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=500005;
const int maxl=20;
const int maxa=250000;
const int root=3;
/*
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
const int iroot=power(3,mod-2);
*/
const int base=101;

int n,q,bit[2*maxn],ans[maxn];

int sz;

vector<piii> p;

bool cmp(piii a,piii b){
    return a.fi.se<b.fi.se;
}
void update(int x,int val){
    for(int i=x;i<=sz;i+=(i&(-i))) bit[i]+=val;
}
int query(int x){
    int res=0;
    for(int i=x;i>=1;i-=(i&(-i))) res+=bit[i];
    return res;
}
void dnc(int l,int r){
    if(l>=r-1) return;
    int mid=(l+r)>>1;
    dnc(l,mid);dnc(mid,r);
    int cur=r-1;
    for(int i=mid-1;i>=l;i--){
        while(cur>=mid && p[cur].fi.se>=p[i].fi.se){
            if(p[cur].se.se==q+1) update(sz-p[cur].se.fi,1);
            cur--;
        }
        ans[p[i].se.se]+=query(sz-p[i].se.fi);
    }
    for(int i=cur+1;i<r;i++) if(p[i].se.se==q+1) update(sz-p[i].se.fi,-1);
    sort(p.begin()+l,p.begin()+r,cmp);
}
void solve(){
    cin >> n >> q;
    vector<int> com;
    for(int i=1;i<=n;i++){
        int s,t;cin >> s >> t;
        p.push_back({{s,t},{s+t,q+1}});
        com.push_back(s+t);
    }
    for(int i=1;i<=q;i++){
        int x,y,z;cin >> x >> y >> z;
        p.push_back({{x,y},{z,i}});
        com.push_back(z);
    }
    sort(com.begin(),com.end());
    com.erase(unique(com.begin(),com.end()),com.end());
    sz=(int)com.size();
    for(auto &x:p) x.se.fi=lower_bound(com.begin(),com.end(),x.se.fi)-com.begin();
    sort(p.begin(),p.end());
    dnc(0,(int)p.size());
    for(int i=1;i<=q;i++) cout << ans[i] << '\n';
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
