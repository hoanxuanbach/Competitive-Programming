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
///const int inf=1e18;
const int mod=1e9+7;
const int maxn=500005;
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
int n,lt[maxn],rt[maxn],c[maxn],sl[maxn],sr[maxn];
vector<int> a[maxn];
int p[maxn];
void solve(){
    cin >> n;
    for(int i=1;i<n;i++) cin >> c[i];
    for(int i=1;i<=n;i++){
        int sz;cin >> sz;a[i].resize(sz);
        for(int j=0;j<sz;j++) cin >> a[i][j];
    }
    for(int i=1;i<n;i++){
        for(int x:a[i]) p[x]=i;
        sl[i]=p[c[i]];
    }
    for(int i=1;i<=n;i++) p[i]=n+1;
    for(int i=n;i>=2;i--){
        for(int x:a[i]) p[x]=i;
        sr[i-1]=p[c[i-1]];
    }
    function<void(int,int)> dnc = [&](int l,int r){
        if(l==r){lt[l]=rt[l]=l;return;}
        int mid=(l+r)>>1;
        dnc(l,mid);dnc(mid+1,r);
        int cl=mid,cr=mid;
        for(int i=mid;i>=l;i--){
            if(rt[i]==mid){
                cl=min(cl,lt[i]);
                while(true){
                    if(cr<r && sl[cr]>=cl) cr++;
                    else if(cl>l && sr[cl-1]<=cr) cl--;
                    else break;
                }
                lt[i]=cl,rt[i]=cr;
            }
        }
        cl=mid+1,cr=mid+1;
        for(int i=mid+1;i<=r;i++){
            if(lt[i]==mid+1){
                cr=max(cr,rt[i]);
                while(true){
                    if(cr<r && sl[cr]>=cl) cr++;
                    else if(cl>l && sr[cl-1]<=cr) cl--;
                    else break;
                }
                lt[i]=cl,rt[i]=cr;
            }
        }
    };
    dnc(1,n);
    int q;cin >> q;
    for(int i=1;i<=q;i++){
        int x,y;cin >> x >> y;
        cout << (lt[x]<=y && y<=rt[x]?"YES":"NO") << '\n';
    }
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
