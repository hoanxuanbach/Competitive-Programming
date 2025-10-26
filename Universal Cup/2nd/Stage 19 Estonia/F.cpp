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

struct matrix{
    int v[3][3],n,m;
    matrix(int n=0,int m=0):n(n),m(m){
        memset(v,0,sizeof(v));
    }
    void init(int x,int y,int z,int t){
        v[0][1]=-z;
        v[0][2]=y;
        v[1][0]=z;
        v[1][2]=-x;
        v[2][0]=-y;
        v[2][1]=x;
        if(t) for(int i=0;i<3;i++) for(int j=0;j<3;j++) v[i][j]=-v[i][j];
    }
    friend matrix operator*(matrix a,matrix b){
        matrix res(a.n,b.m);
        for(int i=0;i<a.n;i++) for(int j=0;j<b.m;j++){
            for(int k=0;k<a.m;k++) res.v[i][j]=(res.v[i][j]+a.v[i][k]*b.v[k][j])%mod;
        }
        return res;
    }
};

struct path{
    int N;
    matrix M;
    vector<matrix> tree;
    void init(int x=0,int y=0,int z=0,int nn=0){
        N=nn;M=matrix(1,3);
        M.v[0][0]=x;M.v[0][1]=y;M.v[0][2]=z;
        tree.resize(4*N);
    }
    void change(int x,int y,int z){
        M.v[0][0]=x;M.v[0][1]=y;M.v[0][2]=z;
    }
    matrix get(){
        if(tree.empty()) return M;
        return M*tree[1];
    }
    void update(int l,int r,int id,int p,matrix x){
        if(l==r){
            tree[id]=x;
            return;
        }
        int mid=(l+r)>>1;
        if(p<=mid) update(l,mid,id<<1,p,x);
        else update(mid+1,r,id<<1|1,p,x);
        tree[id]=tree[id<<1]*tree[id<<1|1];
    }

}P[maxn];

int n,q,a[maxn][3];
vector<int> edge[maxn];

int child[maxn],son[maxn];
int par[maxn],head[maxn],col[maxn];
int L[maxn],pos;

void pre_dfs(int u){
    child[u]=1;
    for(int v:edge[u]){
        pre_dfs(v);
        child[u]+=child[v];
        if(child[son[u]]<child[v]) son[u]=v;
    }
}

void dfs(int u,int p,int t){
    L[u]=++pos;
    if(t) head[u]=head[p];
    else head[u]=u;

    if(son[u]) dfs(son[u],u,1);
    for(int v:edge[u]) if(v!=son[u]) dfs(v,u,0);
}

void update(int v){
    while(head[v]>1){
        v=head[v];
        matrix cur=P[v].get();
        matrix nxt(3,3);
        nxt.init(cur.v[0][0],cur.v[0][1],cur.v[0][2],col[v]);
        int p=par[v];v=head[p];
        //cout << v << ' ' << p << ' ' << P[v].N << endl;
        P[v].update(1,P[v].N,1,P[v].N-(L[p]-L[v]),nxt);
    }
}

void solve(){
    /*
    matrix cur(1,3);
    cur.v[0][0]=0;cur.v[0][1]=2;cur.v[0][2]=1;
    matrix mul(3,3);
    mul.init(1,1,1,0);
    cur=cur*mul;
    cout << cur.v[0][0] << ' ' << cur.v[0][1] << ' ' << cur.v[0][2] << '\n';

    mul=matrix(3,3);
    mul.init(1,0,1,1);
    cur=cur*mul;

    cout << cur.v[0][0] << ' ' << cur.v[0][1] << ' ' << cur.v[0][2] << '\n';
    */
    cin >> n >> q;
    vector<int> leaf;
    for(int i=1;i<=n;i++){
        char c;cin >> c;
        if(c=='x'){
            int l,r;cin >> l >> r;
            edge[i].push_back(l);
            edge[i].push_back(r);
            par[l]=par[r]=i;
            col[l]=1;col[r]=0;
        }
        else{
            cin >> a[i][0] >> a[i][1] >> a[i][2];
            leaf.push_back(i);
        }
    }
    pre_dfs(1);
    dfs(1,0,0);
    for(int v:leaf){
        P[head[v]].init(a[v][0],a[v][1],a[v][2],L[v]-L[head[v]]);
    }
    for(int v:leaf){
        //cout << '*' << v << endl;
        update(v);
    }
    matrix res=P[1].get();
    //cout << res.v[0][0] << ' ' << res.v[0][1] << ' ' << res.v[0][2] << '\n';
    for(int i=1;i<=q;i++){
        int v,x,y,z;
        cin >> v >> x >> y >> z;
        P[head[v]].change(x,y,z);
        update(v);
        matrix res=P[1].get();
        cout << res.v[0][0] << ' ' << res.v[0][1] << ' ' << res.v[0][2] << '\n';
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
