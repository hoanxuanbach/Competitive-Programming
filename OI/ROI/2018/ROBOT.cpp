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
#define piii pair<pii,int>
#define mpp make_pair
#define fi first
#define se second
const int mod=998244353;
const int maxn=400005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=20;
const int maxa=1000000;
const int root=3;
const int base=101;

int n,sub,a[maxn],p[maxn];

namespace BIT{
    int bit[maxn];
    void init(){
        for(int i=1;i<=n;i++) bit[i]=0;
    }
    void update(int x){
        for(int i=x;i<=n;i+=(i&(-i))) bit[i]++;
    }
    int query(int x){
        int res=0;
        for(int i=x;i>=1;i-=(i&(-i))) res+=bit[i];
        return res;
    }
}

vector<int> get_sub1(){
    BIT::init();
    vector<int> res(n),com;
    for(int i=0;i<n;i++) com.push_back(a[i]-i);
    sort(com.begin(),com.end());
    com.erase(unique(com.begin(),com.end()),com.end());
    for(int i=0;i<n;i++){
        int p=lower_bound(com.begin(),com.end(),a[i]-i)-com.begin();
        res[i]=BIT::query(p);
        BIT::update(p+1);
    }
    return res;
}

vector<int> get_sub2(){
    vector<int> res(n,0);
    vector<pii> com;
    for(int i=0;i<n;i++) com.push_back({a[i]+i,i});
    sort(com.begin(),com.end());
    int cnt=0;
    for(int i=0;i<n;i++){
        if(i && com[i].fi!=com[i-1].fi) cnt++;
        p[com[i].se]=cnt;
    }
    BIT::init();
    for(int i=0;i<(n+1)/2;i++){
        res[i]+=BIT::query(p[i]);
        BIT::update(p[i]+1);
    }



    BIT::init();com.clear();
    for(int i=0;i<n;i++) com.push_back({a[i]-i,i});
    sort(com.begin(),com.end());
    cnt=0;
    for(int i=0;i<n;i++){
        if(i && com[i].fi!=com[i-1].fi) cnt++;
        p[com[i].se]=cnt;
    }
    for(int i=n-1;i>=0;i--){
        res[i]+=BIT::query(p[i]);
        BIT::update(p[i]+1);
        if(i&1) res[i/2]-=BIT::query(p[i/2]);
    }

    BIT::init();com.clear();
    for(int i=0;i<n;i++) com.push_back({a[i],i});
    sort(com.begin(),com.end());
    cnt=0;
    for(int i=0;i<n;i++){
        if(i && com[i].fi!=com[i-1].fi) cnt++;
        p[com[i].se]=cnt;
    }
    for(int i=n-1;i>=0;i--){
        BIT::update(p[i]+1);
        if(i&1){
            int pos=lower_bound(com.begin(),com.end(),mpp(a[i/2]+i/2,0))-com.begin();
            res[i/2]+=BIT::query((pos==n?n:p[com[pos].se]));
        }
    }
    return res;
}

vector<int> get_sub22(){
    BIT::init();
    vector<int> res(n,0);
    vector<pii> com;
    for(int i=0;i<n;i++) com.push_back({a[i]+i,i});
    sort(com.begin(),com.end());
    int cnt=0;
    for(int i=0;i<n;i++){
        if(i && com[i].fi!=com[i-1].fi) cnt++;
        p[com[i].se]=cnt;
    }
    BIT::init();
    for(int i=0;i<n;i++){
        res[i]+=BIT::query(p[i]);
        BIT::update(p[i]+1);
    }
    BIT::init();
    for(int i=n-1;i>=0;i--){
        res[i]+=BIT::query(p[i]);
        BIT::update(p[i]+1);
    }
    return res;
}

void solve(){
    cin >> n >> sub;
    for(int i=0;i<n;i++) cin >> a[i];
    if(sub==1){
        vector<int> x1=get_sub1();
        reverse(a,a+n);
        vector<int> x2=get_sub1();
        for(int i=0;i<n;i++) cout << x1[i]+x2[n-i-1]+1 << '\n';
    }
    else{
        vector<int> x=get_sub2();
        reverse(a,a+n);
        vector<int> x2=get_sub2();
        for(int i=n/2;i<n;i++) x[i]=x2[n-i-1];

        vector<int> x3=get_sub22();
        for(int i=0;i<n;i++) x[i]=max(x[i],x3[n-i-1]);
        reverse(a,a+n);
        x3=get_sub22();
        for(int i=0;i<n;i++) x[i]=max(x[i],x3[i]);
        for(int i=0;i<n;i++) cout << x[i]+1 << '\n';
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
