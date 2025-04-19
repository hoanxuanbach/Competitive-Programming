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
- insert(x)
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
#define fi first
#define se second
const int inf=1e18;
const int mod=100000000069;
const int maxn=250005;
const int bl=650;
const int maxs=405;
const int maxm=250005;
const int maxq=500005;
const int maxl=20;
const int maxa=250000;
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

void solve(){
    int n,a,b,c;
    string s;cin >> n >> s >> a >> b >> c;s="#"+s;
    vector<int> h(n+1,0),p(n+1,1),nxt(n+1);
    vector<vector<int>> dp(n+2,vector<int>(n+2,inf));
    for(int i=1;i<=n;i++){
        p[i]=p[i-1]*base%mod;
        h[i]=(h[i-1]*base+s[i])%mod;
        dp[i][i]=a;
    }
    auto get_hash = [&](int l,int r){
        return (h[r]-(__int128)h[l-1]*p[r-l+1]%mod+mod)%mod;
    };
    for(int len=1;len<=n;len++){
        map<int,vector<int>> mp;
        for(int l=1;l<=n-len+1;l++){
            int r=l+len-1;
            dp[l][r]=min(dp[l][r],min(dp[l][r-1],dp[l+1][r])+a);
            mp[get_hash(l,r)].push_back(l);
        }
        for(auto &[_,v]:mp){
            int cur=0;
            for(int l:v){
                while(cur<(int)v.size() && v[cur]<l+len) cur++;
                if(cur==(int)v.size()) nxt[l]=-1;
                else nxt[l]=v[cur];
            }
        }
        for(int l=1;l<=n-len+1;l++){
            int cur=nxt[l],cnt=1;
            while(cur!=-1){
                int r=cur+len-1;cnt++;
                dp[l][r]=min(dp[l][r],dp[l][l+len-1]+a*(r-l+1-len*cnt)+b+c*cnt);
                cur=nxt[cur];
            }
        }
    }
    cout << dp[1][n] << '\n';
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
