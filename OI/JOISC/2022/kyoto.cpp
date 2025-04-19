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
struct frac{
    int x,y;
    frac(int x,int y):x(x),y(y){}
    friend bool operator<(const frac &a,const frac &b){
        return a.x*b.y<a.y*b.x;
    }
};
int n,m,a[2][maxn],ans;
int nxt[2][maxn];
priority_queue<pair<frac,pii>> pq;
void solve(){
    cin >> n >> m;
    for(int i=1;i<=n;i++){
        cin >> a[0][i];
        nxt[0][i]=i+1;
        if(i>=2) pq.push({frac(a[0][i]-a[0][i-1],1),{i-1,i}});
    }
    for(int i=1;i<=m;i++){
        cin >> a[1][i];
        nxt[1][i]=i+1;
        if(i>=2) pq.push({frac(a[1][i]-a[1][i-1],1),{1-i,-i}});
    }
    int cx=n,cy=m;
    while(!pq.empty()){
        auto x=pq.top();pq.pop();
        int d=0;
        if(x.se.fi<0){x.se.fi=-x.se.fi;x.se.se=-x.se.se;d^=1;}
        if(nxt[d][x.se.fi]==0) continue;
        int p=nxt[d][x.se.se];
        nxt[d][x.se.se]=0;nxt[d][x.se.fi]=p;
        if(p!=(n+1)+d*(m-n))pq.push({frac(a[d][p]-a[d][x.se.fi],p-x.se.fi),{(1-2*d)*x.se.fi,(1-2*d)*p}});
        if(d==0 && cx==x.se.se){ans+=a[1][cy]*(cx-x.se.fi);cx=x.se.fi;}
        else if(d==1 && cy==x.se.se){ans+=a[0][cx]*(cy-x.se.fi);cy=x.se.fi;}
    }
    cout << ans << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
