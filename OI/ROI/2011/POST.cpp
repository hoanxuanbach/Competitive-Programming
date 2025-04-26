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
const int inf=1e9;
const int mod=998244353;
const int maxn=200005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=20;
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

int n,d[maxn];
vector<int> t[maxn],v[maxn];

ld A[4*maxn],B[4*maxn];
ld lt[4*maxn],rt[4*maxn];

void getnew(int id,ld a,ld b){
    A[id]=A[id]*a;
    B[id]=B[id]*a+b;
    lt[id]=lt[id]*a+b;
    rt[id]=rt[id]*a+b;
}

void pushdown(int id){
    getnew(id<<1,A[id],B[id]);
    getnew(id<<1|1,A[id],B[id]);
    A[id]=1;B[id]=0;
}

int query0(int l,int r,int id,int tl,int tr,ld val){
    //cout << "query0 " << l << ' ' << r << ' ' << id << ' ' << tl << ' ' << tr << ' ' << val << ' ' << lt[id] << ' ' << rt[id] << '\n';
    if(tl==tr) return tl;
    if(tr<=l || r<=tl) return r;
    if(tl<=l && r<=tr && rt[id]<val) return r;
    if(l+1==r) return l;
    pushdown(id);
    int mid=(l+r)>>1;
    int x=query0(l,mid,id<<1,tl,tr,val);
    if(x==mid && x<tr) return query0(mid,r,id<<1|1,tl,tr,val);
    else return x;
}

int query1(int l,int r,int id,int tl,int tr,ld val){
    //cout << "query1 " << l << ' ' << r << ' ' << id << ' ' << tl << ' ' << tr << ' ' << val << ' ' << lt[id] << ' ' << rt[id] << '\n';
    if(tl==tr) return tl;
    if(tr<=l || r<=tl) return r;
    if(tl<=l && r<=tr && rt[id]>val) return r;
    if(l+1==r) return l;
    pushdown(id);
    int mid=(l+r)>>1;
    int x=query1(l,mid,id<<1,tl,tr,val);
    if(x==mid && x<tr) return query1(mid,r,id<<1|1,tl,tr,val);
    else return x;
}

void update(int l,int r,int id,int tl,int tr,ld a,ld b){
    //cout << "update " << l << ' ' << r << ' ' << id << ' ' << tl << ' ' << tr << ' ' << a << ' ' << b << '\n';
    if(tr<=l || r<=tl) return;
    if(tl<=l && r<=tr){
        getnew(id,a,b);
        return;
    }
    pushdown(id);
    int mid=(l+r)>>1;
    update(l,mid,id<<1,tl,tr,a,b);update(mid,r,id<<1|1,tl,tr,a,b);
    lt[id]=lt[id<<1];rt[id]=rt[id<<1|1];
}

ld get(int l,int r,int id,int p){
    if(l+1==r) return B[id];
    pushdown(id);
    int mid=(l+r)>>1;
    if(p<mid) return get(l,mid,id<<1,p);
    else return get(mid,r,id<<1|1,p);
}
void solve(){
    cin >> n;
    for(int i=0;i<n;i++){
        int sz;cin >> d[i] >> sz;
        t[i].assign(sz+1,0);v[i].resize(sz);
        for(int j=1;j<sz;j++) cin >> t[i][j];
        for(int j=0;j<sz;j++) cin >> v[i][j];
        t[i][sz]=inf;

        d[i+n]=d[i];
        t[i+n]=t[i];
        v[i+n]=v[i];
    }

    ld X1=0;

    for(int i=1;i<=8*n;i++) A[i]=1;
    for(int i=0;i<2*n;i++){
        int L=max(i-n+1,0LL);
        int M=i+1,R=i+1;
        ld cur=d[i],X2=X1+cur;
        //cout << i << ' ' << cur << ' ' << X1 << ' ' << X2 << '\n';
        for(int j=0;j<(int)t[i].size()-1;j++){
            ld T1=t[i][j],T2=t[i][j+1],V=v[i][j];
            ld Maxd=(T2-T1)*V;

            int pos1=query0(0,2*n,1,M,R,X2-Maxd);
            int pos2=query1(0,2*n,1,L,M,T2-cur/V);
            int pos3=query1(0,2*n,1,L,pos2,T2);
            //cout << L << ' ' << M << ' ' << R << ' ' << i << ' ' << j << ' ' << pos1 << ' ' << pos2 << ' ' << pos3 << '\n';
            update(0,2*n,1,pos1,R,-1.0/V,T1+X2/V);
            update(0,2*n,1,M,pos1,1,Maxd);
            update(0,2*n,1,pos2,M,1,(X2-X1)/V);
            update(0,2*n,1,pos3,pos2,-V,X1+T2*V);

            M=pos3;
            if(Maxd<cur) R=pos1;
            else R=pos2;
        }
        X1=X2;
    }
    int p=0;
    for(int i=1;i<n;i++) if(get(0,2*n,1,i)<get(0,2*n,1,p)) p=i;
    cout << p+1 << setprecision(10) << fixed << ' ' << get(0,2*n,1,p) << '\n';
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();

}
