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
const int maxn=100005;
const int B=650;
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
const int base=101;

void print(int a,int b){
    int g=__gcd(a,b);a/=g;b/=g;
    cout << a << '/' << b << '\n';
}

int n,m,lazy[4*maxn];
struct node{
    int total=0;
    int c[2],cc[2][2];
    node(int val=0){
        memset(c,0,sizeof(c));
        memset(cc,0,sizeof(cc));
        c[val]++;cc[val][val]++;
    }
    friend node operator+(node a,node b){
        node res;
        res.total=a.total+b.total+a.cc[0][1]*b.c[1]+a.c[0]*b.cc[1][1]+a.cc[1][1]*b.c[0]+a.c[1]*b.cc[1][0];
        for(int i=0;i<=1;i++){
            res.c[i]=a.c[i]+b.c[i];
            for(int j=0;j<=1;j++) res.cc[i][j]=a.cc[i][j]+b.cc[i][j]+a.c[i]*b.c[j];
        }
        return res;
    };
    void print(){
        cout << total << ' ' << c[0] <<  ' ' << c[1] << endl;
        for(int i=0;i<=1;i++) for(int j=0;j<=1;j++) cout << cc[i][j] << ' ';
        cout << endl;
    }
}tree[4*maxn];

void build(int l,int r,int id){
    lazy[id]=-1;
    if(l==r){
        tree[id]=node(l&1);
        return;
    }
    int mid=(l+r)>>1;
    build(l,mid,id<<1);build(mid+1,r,id<<1|1);
    tree[id]=tree[id<<1]+tree[id<<1|1];
}

void getnew(int id,int sz,int val){
    //cout << "getnew " << id << ' ' << sz << ' ' << val << endl;
    tree[id]=node(val);
    tree[id].c[val]=sz;
    tree[id].cc[val][val]=sz*(sz+1)/2;
    lazy[id]=val;
    //tree[id].print();
}

void pushdown(int l,int r,int id){
    if(lazy[id]==-1) return;
    int mid=(l+r)>>1;
    getnew(id<<1,mid-l+1,lazy[id]);
    getnew(id<<1|1,r-mid,lazy[id]);
    lazy[id]=-1;
}

void update(int l,int r,int id,int tl,int tr,int val){
    if(tr<l || r<tl) return;
    if(tl<=l && r<=tr){
        getnew(id,r-l+1,val);
        //cout << "update " << l << ' ' << r << endl;
        //tree[id].print();
        return;
    }
    pushdown(l,r,id);
    int mid=(l+r)>>1;
    update(l,mid,id<<1,tl,tr,val);update(mid+1,r,id<<1|1,tl,tr,val);
    tree[id]=tree[id<<1]+tree[id<<1|1];
    //cout << "update " << l <<  ' ' << r << endl;
    //tree[id].print();
}

void query(int t){
    int a=tree[1].c[1],b=tree[1].c[0];
    //cout << a << ' ' << b << ' ' << tree[1].total << '\n';
    print(4*tree[1].total+b*(b-1)*(a+1),4*(a+1));
    if(t){
        int N=n/2;
        if(n&1) print(54*N*N*N+55*N*N-29*N,360);
        else print(54*N*N*N+13*N*N+23*N,360);
    }
}

void solve(){
    cin >> n >> m;
    build(1,n,1);query(1);
    for(int i=1;i<=m;i++){
        //cout << "******************************" << endl;
        int l,r,v;cin >> l >> r >> v;
        update(1,n,1,l,r,v);
        query(0);
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
