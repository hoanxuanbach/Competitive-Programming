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

struct line{
    int a,b,p;
    bool operator<(line l){return a>l.a;}
    bool operator<(int k){return p<k;}
};
struct cvht{
    vector<line> x;
    int div(int a,int b){
        return a/b-((a^b)<0 && a%b);
    }
    bool isect(line &l,line y){
        if(l.a==y.a) l.p=(l.b<y.b)?inf:-inf;
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
}cht;

int X,n,m,W,T;
int dp[maxn],c[maxn],s[maxn];
pii d[maxn];

void solve(){
    cin >> X >> n >> m >> W >> T;
    for(int i=1;i<=n;i++) cin >> s[i];
    s[++n]=X--;
    for(int i=1;i<=m;i++) cin >> d[i].fi >> d[i].se,c[i]=-1;
    sort(s+1,s+n+1);sort(d+1,d+m+1);
    for(int i=1;i<=n;i++){
        int pos=upper_bound(d+1,d+m+1,mpp(s[i]%T,inf))-d-1;
        if(c[pos]==-1) c[pos]=s[i]/T;
    }
    int pre=0;
    cht.add({0,0,inf});
    for(int i=1;i<=m;i++){
        pre+=d[i].se;
        dp[i]=dp[i-1]+((X-d[i].fi)/T+1)*W;
        if(c[i]!=-1) dp[i]=min(dp[i],pre+cht.query(c[i]*W)+i*c[i]*W);
        cht.add({-i,dp[i]-pre,inf});
    }
    cout << dp[m]+W*(X/T+1) << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
