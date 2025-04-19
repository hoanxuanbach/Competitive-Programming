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
const int maxn=2005;
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

int nxt[maxn],d[maxn],cnt[maxn],dd[maxn];
int n,m,k,dp[maxn][maxn][2];

void solve(){
    cin >> n >> m >> k;
    vector<pii> p;
    for(int i=1;i<=n;i++){
        int s,t;cin >> s >> t;
        p.push_back({s,i});
        p.push_back({t,-i});
    }
    sort(p.begin(),p.end());
    int total=p[0].fi+m-p.back().fi;
    for(int i=0;i<(int)p.size()-1;i++){
        int u=p[i].se,v=p[i+1].se,w=p[i+1].fi-p[i].fi;
        if(u>0 && v>0) cnt[u]+=w;
        else if(u<0 && v<0) cnt[-v]+=w;
        else if(u>0 && v<0){
            if(u!=-v) nxt[u]=-v,d[u]=w;
            else cnt[u]+=w;
        }
        else total+=w;
    }
    for(int i=1;i<=n;i++) if(nxt[i]) dd[nxt[i]]=1;
    vector<int> ord;
    ord.push_back(0);
    for(int i=1;i<=n;i++){
        if(!dd[i]){
            int u=i;
            do{
                ord.push_back(u);
                u=nxt[u];
            }while(u);
        }
    }
    for(int i=1;i<=n;i++){
        int u=ord[i-1],v=ord[i];
        for(int j=0;j<=min(i,k);j++){
            for(int t=0;t<=min(j,1LL);t++){
                for(int p=0;p<=min(j-t,1LL);p++){
                    dp[i][j][t]=max(dp[i][j][t],dp[i-1][j-t][p]+t*cnt[v]+d[u]*t*p);
                }
            }
        }
    }
    cout << max(dp[n][k][0],dp[n][k][1])+total << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
