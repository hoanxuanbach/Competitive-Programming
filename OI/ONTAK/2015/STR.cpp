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

const int Max = 1e17;

int n,t1,t2,c1,c2,c;
int a[maxn];

int check(int x){
    deque<pii> d1,d2,d3;
    int res=x*c;
    for(int i=1;i<=n;i++){
        while(!d3.empty() && d3[0].fi<=i-t2){
            d2.push_back(d3[0]);
            d3.pop_front();
        }
        while(!d2.empty() && d2[0].fi<=i-t1){
            d1.push_back(d2[0]);
            d2.pop_front();
        }
        int cur=a[i];
        int dx=min(x,cur);
        x-=dx;cur-=dx;
        while(cur){
            if(!d1.empty()){
                pii cc=d1.back();
                int dd=min(cc.se,cur);
                cur-=dd;cc.se-=dd;res+=dd*c1;
                if(!cc.se) d1.pop_back();
                else d1.back()=cc;
            }
            else if(!d2.empty()){
                pii cc=d2.back();
                int dd=min(cc.se,cur);
                cur-=dd;cc.se-=dd;res+=dd*c2;
                if(!cc.se) d2.pop_back();
                else d2.back()=cc;
            }
            else return inf;
        }
        d3.push_back({i,a[i]});
    }
    return res;
}

void solve(){
    cin >> n >> t1 >> t2 >> c1 >> c2 >> c;
    if(t1<t2) swap(t1,t2),swap(c1,c2);
    if(c1>c2) c1=c2;

    int sum=0;
    for(int i=1;i<=n;i++) cin >> a[i],sum+=a[i];
    int l=0,r=sum,res=inf;
    while(l<=r){
        int mid=(l+r)>>1;
        int lt=check(mid),rt=check(mid+1);
        res=min({res,lt,rt});
        if(lt>Max || lt>rt) l=mid+1;
        else r=mid-1;
    }
    cout << res << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
