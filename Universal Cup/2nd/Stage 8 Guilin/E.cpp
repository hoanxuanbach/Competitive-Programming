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

int id[3][3][2];

struct matrix{
    int x[18];
    matrix(){
        memset(x,0,sizeof(x));
    }
    friend matrix operator*(matrix a,matrix b){
        matrix res;
        for(int i=0;i<18;i++) for(int j=0;j<18;j++){
            if(a.x[i]&(1<<j)) res.x[i]|=b.x[j];
        }
        return res;
    }
    void build(int d){
        memset(x,0,sizeof(x));
        for(int i=0;i<3;i++) for(int j=0;j<3;j++) for(int a=0;a<=1;a++) for(int b=0;a+b<=1;b++){
            int k=d-i-j-2*b;
            if(k>=0) x[id[i][j][a]]|=(1<<id[j][k%3][a|b]);
        }
    }
};

matrix tree[4*maxn];
int c[maxn];

void update(int l,int r,int id,int p){
    if(l==r){
        tree[id].build(++c[p]);
        return;
    }
    int mid=(l+r)>>1;
    if(p<=mid) update(l,mid,id<<1,p);
    else update(mid+1,r,id<<1|1,p);
    tree[id]=tree[id<<1]*tree[id<<1|1];
}

void build(int l,int r,int id){
    if(l==r){
        tree[id].build(c[l]);
        return;
    }
    int mid=(l+r)>>1;
    build(l,mid,id<<1);build(mid+1,r,id<<1|1);
    tree[id]=tree[id<<1]*tree[id<<1|1];
}

void solve(){
    int n;cin >> n;
    vector<int> a(n),com;
    for(int i=0;i<n;i++){
        cin >> a[i];
        com.push_back(a[i]);
    }
    sort(com.begin(),com.end());
    com.erase(unique(com.begin(),com.end()),com.end());
    vector<int> cc;
    for(int i=0;i<(int)com.size();i++){
        if(i && com[i]>com[i-1]+1) cc.push_back(com[i]-1);
        cc.push_back(com[i]);
    }
    int sz=(int)cc.size();
    for(int i=1;i<=sz;i++) c[i]=0;
    build(1,sz,1);
    for(int x:a){
        int p=lower_bound(cc.begin(),cc.end(),x)-cc.begin()+1;
        update(1,sz,1,p);
        cout << ((tree[1].x[0]>>1)&1);
    }
    cout << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int cnt=0;
    for(int i=0;i<3;i++) for(int j=0;j<3;j++) for(int k=0;k<2;k++) id[i][j][k]=cnt++;
    int test=1;cin >> test;
    while(test--) solve();
}
