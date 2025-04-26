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
- insert(x)
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
#define fi first
#define se second
const int inf=1e18;
const int mod=998244353;
const int mod2=1e9+7;
const int maxn=200005;
const int bl=650;
const int maxs=650;
const int maxm=200005;
const int maxq=500005;
const int maxl=20;
const int maxa=1000000;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
struct line{
    int a=0,b=1,c=0;
    line(){}
    line(int x1,int y1,int x2,int y2){
        a=y2-y1;b=x1-x2;c=x2*y1-x1*y2;
        int g=__gcd(__gcd(a,b),c);
        a/=g;b/=g;c/=g;
        if(a<0 || (a==0 && (b<0 || (b==0 && c<0)))){a=-a;b=-b;c=-c;}
    }
    friend bool operator<(const line &l1,const line &l2){
        if(l1.a!=l2.a) return l1.a<l2.a;
        else if(l1.b!=l2.b) return l1.b<l2.b;
        else return l1.c<l2.c;
    }
};
map<line,map<pii,int>> mp;
void add(int x1,int y1,int x2,int y2){
    if(x1>x2 || (x1==x2 && y1>y2)){swap(x1,x2);swap(y1,y2);}
    line l=line(x1,y1,x2,y2);
    mp[l][{x1,y1}]++;mp[l][{x2,y2}]--;
}
long double dist(int x1,int y1,int x2,int y2){
    return sqrtl((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}
void solve(){
    int n;cin >> n;
    for(int i=1;i<=n;i++){
        int x1,y1,x2,y2,x3,y3;cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
        add(x1,y1,x2,y2);add(x1,y1,x3,y3);add(x2,y2,x3,y3);
    }
    long double ans=0;
    for(auto x:mp){
        int pre=0;
        pii p={-inf,-inf};
        for(auto a:x.se){
            if(p.fi!=-inf && pre%2==1) ans+=dist(p.fi,p.se,a.fi.fi,a.fi.se);
            p=a.fi;pre+=a.se;
        }
    }
    cout << setprecision(10) << fixed << ans << '\n';
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
