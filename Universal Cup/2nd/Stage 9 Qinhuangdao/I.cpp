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
const int maxn=500005;
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

int n,m,k,a[maxn],d[maxn];

int sz;
vector<int> com;
int get_pos(int x){
    return lower_bound(com.begin(),com.end(),x)-com.begin()+1;
}

int s[4*maxn][2];
void update(int l,int r,int id,int p,int t,int val){
    if(l==r){
        s[id][t]+=val;
        return;
    }
    int mid=(l+r)>>1;
    if(p<=mid) update(l,mid,id<<1,p,t,val);
    else update(mid+1,r,id<<1|1,p,t,val);
    s[id][0]=s[id<<1][0]+s[id<<1|1][0];
    s[id][1]=s[id<<1][1]+s[id<<1|1][1];
}
int query0(int l,int r,int id,int p){
    if(l==r) return com[l-1];
    int mid=(l+r)>>1;
    if(s[id<<1][0]<p) return query0(mid+1,r,id<<1|1,p-s[id<<1][0]);
    else return query0(l,mid,id<<1,p);
}
int query1(int l,int r,int id,int Max0,int p){
    if(l==r) return com[l-1];
    int mid=(l+r)>>1;
    int del=min(Max0,s[id<<1|1][0]);
    if(del+s[id<<1|1][1]<p) return query1(l,mid,id<<1,Max0-del,p-s[id<<1|1][1]-del);
    else return query1(mid+1,r,id<<1|1,Max0,p);
}

void solve(){
    cin >> n >> m >> k;
    for(int i=1;i<=n;i++) cin >> a[i];
    sort(a+1,a+n+1);
    for(int i=1;i<=n;i++){
        d[i]=a[i]/k,a[i]%=k;
        com.push_back(a[i]);
    }
    sort(com.begin(),com.end());
    com.erase(unique(com.begin(),com.end()),com.end());
    sz=(int)com.size();

    int cd=inf,p=n+1,p2=n+1,T=0;
    auto add = [&](int x){
        T+=x;
        int pre=p;
        while(p>1){
            int num=(cd-d[p-1])*(n-p+1);
            if(T>=num) T-=num,cd=d[p-1];
            else break;
            while(p>1 && d[p-1]==cd) update(1,sz,1,get_pos(a[--p]),0,1);
        }
        cd-=T/(n-p+1);T%=(n-p+1);
        if(p<=p2){
            for(int i=p2;i<pre;i++) update(1,sz,1,get_pos(a[i]),1,-1);
            p2=p;
        }
        while(p2>1 && d[p2-1]==cd-1) update(1,sz,1,get_pos(a[--p2]),1,1);
    };
    auto get = [&](int x){
        if(x>n-p2+1) return d[n-x+1]*k+a[n-x+1];
        if(x<=n-p+1-T) return cd*k+query0(1,sz,1,n-p+1-T-x+1);
        else return (cd-1)*k+query1(1,sz,1,T,x-(n-p+1-T));
    };
    for(int i=1;i<=m;i++){
        char c;int x;cin >> c >> x;
        if(c=='C') add(x);
        else cout << get(x) << '\n';
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}