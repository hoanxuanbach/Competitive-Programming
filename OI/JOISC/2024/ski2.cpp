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
const int maxn=305;
const int B=650;
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
const int base=101;

int H,N,K,X[3*maxn],C[3*maxn];
int dp[3*maxn][maxn][maxn];

int f(int i,int mx,int cnt){
    if(i>=H && !cnt) return 0;
    if(dp[i][mx][cnt]!=-1) return dp[i][mx][cnt];
    int cc=X[i+1]+cnt;
    dp[i][mx][cnt]=inf;
    if(cc<=mx) dp[i][mx][cnt]=f(i+1,mx,0);
    else{
        for(int d=mx;d<=cc;d++) if(C[i]!=inf || (d==mx)) dp[i][mx][cnt]=min(dp[i][mx][cnt],f(i+1,d,cc-d)+C[i]*(d-mx)+K*(cc-d));
    }
    //cout << i << ' ' << mx << ' ' << cnt << ' ' << dp[i][mx][cnt] << '\n';
    return dp[i][mx][cnt];
}

void solve(){
    cin >> N >> K;
    map<int,pii> mp;
    for(int i=1;i<=N;i++){
        int h,c;cin >> h >> c;h++;
        if(mp.find(h)==mp.end()) mp[h]={1,c};
        else{
            pii x=mp[h];x.fi++;
            x.se=min(x.se,c);
            mp[h]=x;
        }
    }
    int del=0,Max=0,pre=0;
    for(auto x:mp){
        pair<int,pii> it=x;
        //cout << it.fi << ' ' << it.se.fi << ' ' << it.se.se << '\n';
        it.fi-=del;
        if(it.fi>Max+pre){
            del+=it.fi-Max-pre;
            it.fi=Max+pre;
        }
        H=max(H,it.fi+1);
        X[it.fi+1]=it.se.fi;
        C[it.fi+1]=it.se.se;
        Max=max(Max,it.fi-pre);
        pre+=it.se.fi;
    }
    int S=Max+pre;
    //cout << H << ' ' << S << '\n';
    for(int i=0;i<=S;i++) if(!C[i]) C[i]=inf;
    for(int i=1;i<=S;i++){
        C[i]=min(C[i],C[i-1]);
        //cout << X[i] << ' ' << C[i] << '\n';
    }
    memset(dp,-1,sizeof(dp));
    cout << f(0,1,0) << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
