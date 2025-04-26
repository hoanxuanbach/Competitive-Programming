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
#define piii pair<pii,int>
#define mpp make_pair
#define fi first
#define se second
const int inf=1e18;
const int mod=998244353;
const int maxn=150005;
const int bl=685;
const int maxs=400;
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

struct line{
    int a,b,p;
    bool operator<(line l){return a<l.a;}
    bool operator<(int k){return p<k;}
};
struct cvht{
    vector<line> x;
    int div(int a,int b){
        return a/b-((a^b)<0 && a%b);
    }
    bool isect(line &l,line y){
        if(l.a==y.a) l.p=(l.b>y.b)?inf:-inf;
        else l.p=div(y.b-l.b,l.a-y.a);
        return l.p>=y.p;
    }
    void add(line l){
        if(!x.empty()) isect(x.back(),l);
        while((int)x.size()>=2 && x[(int)x.size()-2].p>=x.back().p){
            x.pop_back();
            isect(x.back(),l);
        }
        x.push_back(l);
    }
    int query(int v){
        auto l=*lower_bound(x.begin(),x.end(),v);
        return l.a*v+l.b;
    }
}cht[maxs];
int add[maxs],num[maxn],sz,total;

pii p[maxn];
vector<int> com;

void update(int pos){
    for(int i=0;i<pos/bl;i++){
        add[i]++;
        total=max(total,cht[i].query(add[i]));
    }
    int l=(pos/bl)*bl;
    cht[pos/bl].x.clear();
    for(int i=l;i<=pos;i++) num[i]++;
    for(int i=l;i<min(sz,(pos/bl+1)*bl);i++){
        num[i]+=add[pos/bl];
        cht[pos/bl].add({com[i],com[i]*num[i],inf});
        total=max(total,com[i]*num[i]);
    }
    add[pos/bl]=0;
}

void solve(){
    int n,ans=0;cin >> n;
    for(int i=0;i<n;i++){
        cin >> p[i].fi >> p[i].se;
        com.push_back(p[i].se);
    }
    sort(p,p+n);
    sort(com.begin(),com.end());
    com.erase(unique(com.begin(),com.end()),com.end());
    sz=(int)com.size();
    for(int i=0;i<sz;i++) cht[i/bl].add({com[i],0,inf});
    for(int i=0;i<n;i++){
        ans=max(ans,total+p[i].fi*(n-i));
        int pos=lower_bound(com.begin(),com.end(),p[i].se)-com.begin();
        update(pos);
    }
    cout << ans << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}

