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
const int maxn=262155;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=20;
const int maxa=1000025;
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

int n,a[maxn];
vector<int> pos[maxa];

//Linked-List
int pre[maxn],nxt[maxn];
list<pii> p[maxn];

void solve(){
    int n;cin >> n;
    for(int i=0;i<n;i++){
        cin >> a[i];
        pos[a[i]].push_back(i);
    }
    iota(pre,pre+n+1,0);
    iota(nxt,nxt+n+1,0);
    vector<int> lt;
    int ans=0,cur=n*(n+1)/2;

    auto cal = [&](list<pii> &L){
        int res=0;
        for(auto it=L.begin();it!=L.end();it++){
            int nl=(next(it)!=L.end()?next(it)->fi:it->se);
            res+=it->se*(nl-it->fi)-(nl-it->fi)*(nl-1+it->fi)/2;
        }
        return res;
    };
    auto update = [&](list<pii> &L){
        if((int)L.size()<=1) return;
        cur+=cal(L);
        list<pii> nL;
        auto it=L.begin();
        int Max=-1;
        for(auto [l,r]:L){
            while(next(it)!=L.end() && next(it)->fi<=r) it++;
            if(it->se>Max) nL.push_back({l,Max=it->se});
        }
        swap(L,nL);
        cur-=cal(L);
    };
    for(int v=1;cur;v++){
        ans+=cur;
        vector<int> nlt;
        for(int l:lt){
            update(p[l]);
            if((int)p[l].size()>1) nlt.push_back(l);
        }
        for(int i:pos[v]){
            int l=pre[i],r=nxt[i+1];
            bool add = ((int)p[l].size()<=1);
            pre[i]=nxt[i+1]=-1;
            nxt[l]=r;pre[r]=l;
            p[l].push_back({i,i+1});cur--;
            p[l].splice(p[l].end(),p[i+1]);
            add &= ((int)p[l].size()>1);
            if(add) nlt.push_back(l);
        }
        swap(nlt,lt);
    }
    cout << ans << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
