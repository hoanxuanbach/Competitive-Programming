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
#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_real_distribution<> pp(0.0,1.0);
//#define int long long
#define double long double
#define pii pair<int,int>
#define piii pair<int,pii>
#define mpp make_pair
#define fi first
#define se second
const int inf=1e18;
const int mod=998244353;
const int maxn=200005;
const int B=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=25;
const int maxa=1000000;
const int root=3;
const int base=101;

struct matrix{
    int n,m;
    double x[5][5];
    matrix(int n=-1,int m=-1):n(n),m(m){
        for(int i=0;i<n;i++) for(int j=0;j<m;j++) x[i][j]=0;
    }
    friend matrix operator*(matrix a,matrix b){
        matrix res(a.n,b.m);
        for(int i=0;i<a.n;i++) for(int j=0;j<b.m;j++){
            res.x[i][j]=0;
            for(int k=0;k<a.m;k++) res.x[i][j]+=a.x[i][k]*b.x[k][j];
        }
        return res;
    }
}tree[4*maxn];

int n,m,c[maxn];
char S;
double p[maxn][2];

void merge(int id){
    for(int i=0;i<4;i++) for(int j=0;j<4;j++){
        tree[id].x[i][j]=0;
        for(int k=0;k<4;k++) tree[id].x[i][j]+=tree[id<<1].x[i][k]*tree[id<<1|1].x[k][j];
    }
}

void f(int x,int id){
    tree[id]=matrix(4,4);
    for(int i=0;i<=1;i++){
        tree[id].x[i][1]+=p[x][i];
        tree[id].x[i][0]+=1-p[x][i];
        tree[id].x[i+2][3]+=p[x][i];
        tree[id].x[i+2][2]+=1-p[x][i];
    }
    for(int i=0;i<=3;i++) tree[id].x[i][3]+=tree[id].x[i][1];
    if(c[x]!=-1){
        for(int i=0;i<=3;i++) tree[id].x[i][(c[x]^1)]=tree[id].x[i][(c[x]^1)+2]=0;
    }
}

void build(int l,int r,int id){
    tree[id]=matrix(4,4);
    if(l==r){
        f(l,id);
        return;
    }
    int mid=(l+r)>>1;
    build(l,mid,id<<1);build(mid+1,r,id<<1|1);
    merge(id);
}
void update(int l,int r,int id,int p){
    if(l==r){
        f(l,id);
        return;
    }
    int mid=(l+r)>>1;
    if(p<=mid) update(l,mid,id<<1,p);
    else update(mid+1,r,id<<1|1,p);
    merge(id);
}

void solve(){
    cin >> n >> m >> S;
    cin >> p[1][1];
    for(int i=2;i<=n;i++) cin >> p[i][1] >> p[i][0];
    for(int i=1;i<=n;i++) c[i]=-1;
    /*
    auto cal = [&](){
        vector<double> d(2,0),ans(2,0);
        d[1]=1.0;
        for(int i=1;i<=n;i++){
            vector<double> nd(2,0),nans(2,0);
            for(int j=0;j<=1;j++){
                nd[1]+=d[j]*p[i][j];
                nd[0]+=d[j]*(1-p[i][j]);
                nans[1]+=ans[j]*p[i][j];
                nans[0]+=ans[j]*(1-p[i][j]);
            }
            swap(d,nd);swap(ans,nans);
            if(c[i]!=-1){
                d[c[i]^1]=0;
                ans[c[i]^1]=0;
            }
            ans[1]+=d[1];
            //cout << '*' << d[0] << ' ' << d[1] << ' ' << ans[0] << ' ' << ans[1] << '\n';
        }
        //cout << ans[0]+ans[1] << ' ' << d[0]+d[1] << '\n';
        cout << setprecision(10) << fixed << (ans[0]+ans[1])/(d[0]+d[1]) << '\n';
    };
    */
    build(1,n,1);
    for(int i=1;i<=m;i++){
        int pos;string s;
        cin >> s >> pos;
        if(s=="del") c[pos]=-1;
        else cin >> c[pos];
        update(1,n,1,pos);
        cout << setprecision(10) << fixed << (tree[1].x[1][2]+tree[1].x[1][3])/(tree[1].x[1][0]+tree[1].x[1][1]) << '\n';
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
