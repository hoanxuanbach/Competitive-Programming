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
#define piii pair<int,pii>
#define mpp make_pair
#define fi first
#define se second
const int mod=998244353;
const int maxn=200005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=25;
const int maxa=1000000;
const int root=3;
const int base=131;
const int S = (1<<10);

int n,k,s[S];
string cc;
set<string> cur;

void dfs(int u,int d,int mask,int need){
    if(need>d) return;
    if((1<<u)>mask && need>0) return;
    if(!u && !d) return;
    if(!d){
        auto it=lower_bound(cc.begin(),cc.end(),'1');
        swap(cc[0],cc[it-cc.begin()]);
        cur.insert(cc);
        if((int)cur.size()>k) cur.erase(*cur.rbegin());
        swap(cc[0],cc[it-cc.begin()]);
        return;
    }
    cc+=u+'0';
    dfs(u,d-1,mask,need-((mask>>u)&1));
    cc.pop_back();u++;
    if(u<10) dfs(u,d,mask,need);
}

void solve(){
    cin >> n >> k;
    for(int i=1;i<=n;i++){
        int mask=0;
        for(int j=0;j<6;j++){int v;cin >> v;mask|=(1<<v);}
        for(int j=0;j<S;j++) if(mask&j) s[j]++;
    }
    for(int d=1;;d++){
        cur.clear();
        for(int i=0;i<S;i++){
            if(d>s[i]) dfs(0,d,i,s[i]+1);
        }
        priority_queue<string,vector<string>,greater<string>> pq;
        for(string x:cur) pq.push(x);
        while(!pq.empty()){
            string x=pq.top();pq.pop();
            cout << x << ' ';
            if(!--k) return;
            if(next_permutation(x.begin(),x.end())) pq.push(x);
        }
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
