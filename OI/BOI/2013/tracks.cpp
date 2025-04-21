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
const int inf=1e9;
const int mod=998244353;
const int maxn=4005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=20;
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
const int base=101;
int dx[]={1,-1,0,0},
    dy[]={0,0,1,-1};

int n,m;
int d[maxn][maxn],dist[maxn][maxn];

void solve(){
    cin >> n >> m;
    char f;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            char c;cin >> c;
            if(i==1 && j==1) f=c;
            dist[i][j]=inf;
            d[i][j]=(c=='.'?-1:(c==f?0:1));
        }
    }
    deque<pii> dq;
    dq.push_back({1,1});dist[1][1]=1;
    int ans=0;
    while(!dq.empty()){
        int x=dq.front().fi,y=dq.front().se;dq.pop_front();
        int dd=dist[x][y];
        ans=max(ans,dd);
        for(int t=0;t<4;t++){
            int xt=x+dx[t],yt=y+dy[t];
            if(xt<=0 || yt<=0 || xt>n || yt>m || d[xt][yt]==-1) continue;
            int nxt=(d[xt][yt]==(dd&1));
            if(dist[xt][yt]>dd+nxt){
                dist[xt][yt]=dd+nxt;
                if(nxt) dq.push_back({xt,yt});
                else dq.push_front({xt,yt});
            }
        }
    }
    cout << ans << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
