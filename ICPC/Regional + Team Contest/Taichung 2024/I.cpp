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
#define pii pair<int,int>
#define piii pair<int,pii>
#define mpp make_pair
#define fi first
#define se second
//const int inf=1e18;
const int mod=998244353;
const int maxn=2000005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=25;
const int maxa=1000000;
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
const int base=131;

const int maxS = 105;
const int S = 126 - 33;


int n,cnt,cur;

int f[maxn];
array<int,3> dp[maxn];
priority_queue<int,vector<int>,greater<int>> pq[maxn];
int par[maxn][21];
map<int,int> nxt[maxn];

int get_new(int u){
    cnt++;
    dp[cnt]={-1,-1,-1};
    par[cnt][0]=u;
    for(int i=1;i<=20;i++) par[cnt][i]=par[par[cnt][i-1]][i-1];
    return cnt;
}

void update(int u){
    while(!pq[u].empty() && !f[pq[u].top()]) pq[u].pop();
    dp[u]={-1,-1,-1};
    if(!pq[u].empty()) dp[u]=max(dp[u],{0,0,pq[u].top()});
    for(auto &[i,v]:nxt[u]) if(dp[v][0]!=-1){
        dp[u]=max(dp[u],{dp[v][0]+1,-i,dp[v][2]});
    }
}

void add(int id,string &s){
    int u=0;
    for(char c:s){
        int a = c-33;
        if(!nxt[u][a]) nxt[u][a]=get_new(u);
        u=nxt[u][a];
    }
    f[id]=u;
    pq[u].push(id);

    while(u){
        update(u);
        u=par[u][0];
    }
    update(0);
}

void del(int id){
    int u=f[id];f[id]=0;
    while(u){
        update(u);
        u=par[u][0];
    }
    update(0);
}
void backspace(int k){
    for(int i=0;i<=20;i++) if(k>>i&1) cur=par[cur][i];
}
void append(string &s){
    for(char c:s){
        int a = c-33;
        if(!nxt[cur][a]) nxt[cur][a]=get_new(cur);
        cur=nxt[cur][a];
    }
}

void solve(){
    cin >> n; 
    dp[0]={-1,-1,-1};
    for(int i=1;i<=n;i++){
        string op,s;int id;
        cin >> op;
        if(op=="add"){
            cin >> id >> s;
            add(id,s);
        }
        else if(op=="delete"){
            int id;cin >> id;
            del(id);
        }
        else if(op=="append"){
            cin >> s;
            append(s);
        }
        else{
            cin >> id;
            backspace(id);
        }
        cout << dp[cur][2] << '\n';
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
