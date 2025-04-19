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
#pragma GCC target("avx2,popcnt,lzcnt,abm,bmi,bmi2,fma")
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
const int S=3;

int q,L;
struct query{
    int t,x,a;
}qq[maxn];

int sz;
vector<int> com;
int get_pos(int x){
    return lower_bound(com.begin(),com.end(),x)-com.begin()+1;
}

int C[8*maxn],D[8*maxn],tree[8*maxn][2][2][S];


void getnew(int id,int c,int d){
    for(int i=0;i<2;i++) for(int j=0;j<2;j++) for(int k=0;k<S;k++) if(tree[id][i][j][k]!=-inf) tree[id][i][j][k]+=i*c-j*d+k*(c-d);
    C[id]+=c;D[id]+=d;
}
void pushdown(int id){
    if(!C[id] && !D[id]) return;
    getnew(id<<1,C[id],D[id]);
    getnew(id<<1|1,C[id],D[id]);
    C[id]=D[id]=0;
}

void merge(int id){
    for(int i=0;i<2;i++) for(int j=0;j<2;j++) for(int k=0;k<S;k++){
        tree[id][i][j][k]=max(tree[id<<1][i][j][k],tree[id<<1|1][i][j][k]);
    }
    for(int li=0;li<2;li++) for(int lj=0;lj<2;lj++) for(int rj=0;rj<2;rj++){
        for(int lk=0;lk<S;lk++) for(int rk=0;rk<S;rk++) tree[id][li][rj][min(S-1,lk+rk+lj)]=max(tree[id][li][rj][min(S-1,lk+rk+lj)],tree[id<<1][li][lj][lk]+tree[id<<1|1][lj][rj][rk]);
    }
}

void update(int l,int r,int id,int tl,int tr,int c,int d){
    if(tr<l || r<tl) return;
    if(tl<=l && r<=tr){
        getnew(id,c,d);
        return;
    }
    pushdown(id);
    int mid=(l+r)>>1;
    update(l,mid,id<<1,tl,tr,c,d);update(mid+1,r,id<<1|1,tl,tr,c,d);
    merge(id);
}

void build(int l,int r,int id){
    if(l==r){
        int d=com[r]-com[l-1];
        for(int i=0;i<2;i++) for(int j=0;j<2;j++) for(int k=0;k<S;k++){
            tree[id][i][j][k]=-inf;
            if(i+j+k<=d) tree[id][i][j][k]=0;
        }
        return;
    }
    int mid=(l+r)>>1;
    build(l,mid,id<<1);build(mid+1,r,id<<1|1);
    merge(id);
}

void solve(){
    cin >> q >> L;
    for(int i=1;i<=q;i++){
        int t,x,a;cin >> t >> x >> a;
        qq[i]={t,x,a};
        if(t==1){
            com.push_back(x);
            com.push_back(x+1);
        }
        else{
            com.push_back(x-L);
            com.push_back(x+L+1);
        }
    }
    com.push_back(INT_MIN);
    sort(com.begin(),com.end());
    com.erase(unique(com.begin(),com.end()),com.end());
    sz=(int)com.size();com.push_back(INT_MAX);
    build(1,sz,1);

    int sum=0;
    for(int i=1;i<=q;i++){
        auto [t,x,a]=qq[i];
        if(t==1){
            sum+=a;
            int l=get_pos(x),r=get_pos(x+1);
            update(1,sz,1,l,r-1,a,0);
            update(1,sz,1,r,sz,a,a);
        }
        else{
            int l=get_pos(x-L),r=get_pos(x+L+1);
            update(1,sz,1,l,r-1,-a,0);
            update(1,sz,1,r,sz,-a,-a);
        }
        int res=0;
        for(int j=0;j<S;j++) res=max(res,tree[1][0][0][j]);
        cout << sum-res << '\n';
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
