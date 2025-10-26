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
const int mod=1e9+7;
const int maxn=130;
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

const int N = 125;

int inv[maxn],w[maxn][maxn],iw[maxn][maxn];

int r[maxn],ans[maxn];
vector<int> deg[maxn];
vector<int> rid;

void build(){
    inv[1]=1;
    for(int i=2;i<=N;i++) inv[i]=mod-(mod/i)*inv[mod%i]%mod;

    for(int i=1;i<=N;i++){
        w[i][0]=iw[i][0]=1;
        for(int j=1;j<=i;j++){
            w[i][j]=w[i][j-1]*(i-j+1)%mod;
            iw[i][j]=iw[i][j-1]*inv[i-j+1]%mod;
        }
    }
}

void print(int n,vector<int> d){
    while(n>1 && (int)d.size()<n) d.push_back(0);
    for(int &x:d) x++;
    sort(d.begin(),d.end());
    vector<pii> edge;
    for(int i=0;i<(int)d.size();i++){
        for(int j=i+1;j<(int)d.size();j++){
            if(d[j]>1 || i==(int)d.size()-2){
                d[i]--;d[j]--;
                edge.push_back({i,j});
                break;
            }
        }
    }
    cout << n << '\n';
    for(auto x:edge) cout << x.fi+1 << ' ' << x.se+1 << '\n';
}

bitset<mod> f;
vector<pii> h[maxn],g[maxn];
int n;

void dfs_a(int x,int used,int cur){
    f[cur]=1;
    for(int i=x;i<=min(n-2,6LL);i++){
        if(used+i>n-2) return;
        dfs_a(i,used+i,cur*w[n-2][i]%mod);
    }
}
void dfs_b(int x,int used,int cur){
    for(int i:rid) if(f[cur*inv[n]%mod*inv[n-1]%mod*r[i]%mod]){
        g[used].push_back({i,cur});
    }
    for(int i=x;i<=n-2;i++){
        if(used+i>n-2) return;
        dfs_b(i,used+i,cur*iw[n-2][i]%mod);
    }
}

vector<int> dd;
void dfs_ca(int x,int used,int cur){
    for(auto [i,pre]:g[n-2-used]){
        if(cur*n%mod*(n-1)%mod==r[i]*pre%mod && !ans[i]){
            ans[i]=n;
            deg[i]=dd;
            h[n-2-used].push_back({i,pre});
        }
    }
    for(int i=x;i<=min(n-2,6LL);i++){
        if(used+i>n-2) return;
        dd.push_back(i);
        dfs_ca(i,used+i,cur*w[n-2][i]%mod);
        dd.pop_back();
    }
}

void dfs_cb(int x,int used,int cur){
    for(auto [i,pre]:h[used]){
        if(pre==cur){
            for(int d:dd) deg[i].push_back(d);
        }
    }
    for(int i=x;i<=n-2;i++){
        if(used+i>n-2) return;
        dd.push_back(i);
        dfs_cb(i,used+i,cur*iw[n-2][i]%mod);
        dd.pop_back();
    }
}

void solve(){
    build();
    int test;cin >> test;
    for(int i=1;i<=test;i++){
        cin >> r[i];
        if(r[i]==1) ans[i]=1;
        else if(r[i]==2) ans[i]=2;
        else rid.push_back(i);
    }
    for(n=3;n<=N;n++){
        f.reset();
        for(int i=0;i<=n;i++) h[i].clear(),g[i].clear();
        dfs_a(1,0,1);
        dfs_b(7,0,1);
        dfs_ca(1,0,1);
        dfs_cb(7,0,1);
        for(int i=1;i<=test;i++){
            if(ans[i]!=0){
                auto it=find(rid.begin(),rid.end(),i);
                if(it!=rid.end()) rid.erase(it);
            }
        }
        if(rid.empty()) break;
    }

    for(int i=1;i<=test;i++) print(ans[i],deg[i]);
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
