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
#define piii pair<int,pii>
#define mpp make_pair
#define fi first
#define se second
const int inf=1e9;
const int mod=998244353;
const int maxn=1000005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=20;
const int maxa=1000000;
const int root=3;
const int base=101;

int n,a[maxn],A;
int lmax[maxn],lmin[maxn],rmax[maxn],rmin[maxn],sum[maxn];

pii f(pii x,pii y){
    if(1LL*x.fi*y.se<1LL*x.se*y.fi) return x;
    else return y;
}

pii cal(int k){
    for(int i=0;i<k;i++) sum[i]=0;
    //for(int i=0;i<n-1;i++) Max[i]=0,Min[i]=inf;
    sum[0]+=A;
    for(int i=0;i<(n-1);i++){
        sum[(i+1)%k]+=a[i];
        lmax[i]=rmax[i]=0;
        lmin[i]=rmin[i]=inf;
    }
    pii res={0,inf};
    for(int i=0;i<k;i++){
        res.fi=max(res.fi,sum[i]);
        res.se=min(res.se,sum[i]);
    }
    for(int i=0;i<n-1;i++){
        if(i%k==0){
            int cMin=inf,cMax=0;
            for(int j=k-3;j>=0;j--){
                cMin=min(cMin,sum[j+2]);
                cMax=max(cMax,sum[j+2]);
                rmin[i+j]=cMin;
                rmax[i+j]=cMax;
            }
            for(int j=0;j<k-1;j++){
                sum[j]+=a[i+j]-A;
                sum[j+1]+=A-a[i+j];
                lmax[i+j]=max(lmax[i+j],sum[j]);
                if(j) lmax[i+j]=max(lmax[i+j],lmax[i+j-1]);
                lmin[i+j]=min(lmin[i+j],sum[j]);
                if(j) lmin[i+j]=min(lmin[i+j],lmin[i+j-1]);
                pii cur={max({lmax[i+j],rmax[i+j],sum[j+1]}),min({lmin[i+j],rmin[i+j],sum[j+1]})};
                res=f(res,cur);
            }
            if(i+k-1<n-1){
                sum[k-1]+=a[i+k-1]-A;
                sum[0]+=A-a[i+k-1];
                pii cur={0,inf};
                for(int j=0;j<k;j++){
                    cur.fi=max(cur.fi,sum[j]);
                    cur.se=min(cur.se,sum[j]);
                }
                res=f(res,cur);
            }
        }
    }
    return res;
}

void solve(){
    cin >> n >> A;
    for(int i=0;i<n-1;i++) cin >> a[i];
    pii res={1000,1};
    for(int i=2;i<=n;i++){
        if(n%i==0) res=f(res,cal(i));
    }
    int g=__gcd(res.fi,res.se);
    cout << res.fi/g << ' ' << res.se/g << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}
