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
//#define int long long
#define ld long double
#define pii pair<long long,long long>
#define piii pair<pii,int>
#define mpp make_pair
#define fi first
#define se second
//const int inf=1e18;
const int mod=1e9+7;
const int maxn=200005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=500005;
const int maxl=20;
const int maxa=250000;
const int root=3;
/*
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
const int iroot=power(3,mod-2);
*/
const int base=101;
map<int,long long> mp[maxn];

void solve(){
    int n;cin >> n;
    vector<int> a(n+1),c(n+1),h(n+1),deg(n+1,0);
    vector<vector<int>> child(n+1);

    for(int i=1;i<=n;i++){
        cin >> a[i] >> h[i] >> c[i];
        child[a[i]].push_back(i);deg[a[i]]++;
    }

    queue<int> q;
    for(int i=1;i<=n;i++) if(deg[i]==0) q.push(i);
    while(!q.empty()){
        int u=q.front();q.pop();
        deg[a[u]]--;
        if(deg[a[u]]==0) q.push(a[u]);
    }
    auto unions = [&](int u,int v){
        if((int)mp[u].size()<(int)mp[v].size()) swap(mp[u],mp[v]);
        for(auto [x,val]:mp[v]) mp[u][x]+=val;
    };
    function<void(int)> dfs = [&](int u){
        for(int v:child[u]) dfs(v),unions(u,v);
        mp[u][0]+=c[u];
        int del=c[u];
        auto it=mp[u].upper_bound(h[u]);
        while(it!=mp[u].begin()){
            it--;
            if(it->se<=del) del-=it->se,it=mp[u].erase(it);
            else{mp[u][it->fi]-=del;break;}
        }
        mp[u][h[u]+1]+=c[u];
    };
    long long total=0;
    for(int i=1;i<=n;i++){
        if(deg[i]){
            int u=i;
            long long sum=0;
            vector<pii> cc,nw;
            do{
                cc.push_back({h[u],u});sum+=c[u];
                for(int v:child[u]) if(!deg[v]) dfs(v),unions(i,v);
                u=a[u];
            }while(u!=i);
            sort(cc.begin(),cc.end());
            for(auto [x,u]:cc) deg[u]=0;
            for(auto [x,u]:cc){
                if(nw.empty() || nw.back().fi!=x) nw.push_back({x,c[u]});
                else nw.back().se+=c[u];
            }
            cc.clear();
            for(auto [x,val]:mp[i]) cc.push_back({x,val});
            int pos=0;
            long long cur=0,res=sum+mp[i][0];
            for(auto [x,val]:nw){
                while(pos<(int)cc.size() && cc[pos].fi<=x) cur+=cc[pos++].se;
                res=min(res,cur+sum-val);
            }
            total+=res;
        }
    }
    cout << total << '\n';
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}

