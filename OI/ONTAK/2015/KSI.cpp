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
const int mod=1e9+7;
const int maxn=500005;
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

namespace Segtree{
    struct node{
        int a=1,b=0;
        node(int a=1,int b=0):a(a),b(b){}
        friend node operator+(node x,node y){
            node res;
            res.a=x.a*y.a%mod;
            res.b=(x.b*y.a+y.b)%mod;
            return res;
        }
    };
    int num[4*maxn];
    node tree[4*maxn];
    node update(int l,int r,int id,int p){
        if(l==r){
            num[id]++;
            tree[id]=node(num[id]+1,num[id]);
            return node();
        }
        int mid=(l+r)>>1;
        node res;
        if(p<=mid) res=update(l,mid,id<<1,p);
        else res=update(mid+1,r,id<<1|1,p);
        tree[id]=tree[id<<1]+tree[id<<1|1];
        if(p<=mid) return res;
        else return tree[id<<1]+res;
    }
}

int n,a[maxn];
vector<int> com;

void solve(){
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> a[i];
        com.push_back(a[i]);
    }
    sort(com.begin(),com.end());
    com.erase(unique(com.begin(),com.end()),com.end());
    int sz=(int)com.size();
    int total=0,Max=0;
    for(int i=1;i<=n;i++){
        a[i]=lower_bound(com.begin(),com.end(),a[i])-com.begin()+1;
        Segtree::node res=Segtree::update(1,sz,1,a[i]);
        if(Max>a[i]) total=(total+1+res.b)%mod;
        Max=max(Max,a[i]);
    }
    cout << total << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
