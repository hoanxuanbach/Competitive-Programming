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
const int maxn=1000005;
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
    int a,b,p=inf;
    line(int a=0,int b=0,int p=inf):a(a),b(b),p(p){}
    bool operator<(const line &o)const{return a<o.a;}
    bool operator<(int o)const{return p<o;}
};

struct CHT{
    vector<line> v;
    int div(int a,int b){
        return a/b-((a^b)<0 && (a%b!=0));
    }
    void isect(line &y,line l){
        if(y.a==l.a) y.p=(y.b>=l.b?inf:-inf);
        else y.p=div(l.b-y.b,y.a-l.a);
    }
    void add_line(line l){
        if(!v.empty()) isect(v.back(),l);
        while((int)v.size()>=2 && v.end()[-2].p>=v.back().p){
            v.pop_back();
            isect(v.back(),l);
        }
        v.push_back(l);
    }
    int query(int x){
        auto l=*lower_bound(v.begin(),v.end(),x);
        return l.a*x+l.b;
    }
}cht;

int n,a,b,c,pre[maxn],dp[maxn];

void solve(){
    cin >> n >> a >> b >> c;
    for(int i=1;i<=n;i++){
        cin >> pre[i];
        pre[i]+=pre[i-1];
    }

    /*
    a*(pre[i]-pre[j])^2+b*(pre[i]-pre[j])+c;
    -a*2*pre[j] a*(pre[i]^2)+b*(pre[i])+c a(pre[j]^2)-b*(pre[j])
    */
    cht.add_line(line(0,0,inf));
    for(int i=1;i<=n;i++){
        dp[i]=cht.query(pre[i])+a*pre[i]*pre[i]+b*pre[i]+c;
        cht.add_line(line(-a*2*pre[i],a*pre[i]*pre[i]-b*pre[i]+dp[i],inf));
    }
    cout << dp[n] << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
