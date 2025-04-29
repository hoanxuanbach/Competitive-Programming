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
#define piii pair<pii,int>
#define mpp make_pair
#define fi first
#define se second
const int inf=1e18;
const int mod=998244353;
const int maxn=505;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=20;
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

int n,m,r;
string s[(1<<13)+5];
int dp[maxn][(1<<14)+5];
vector<pii> trans[(1<<13)+5];
vector<piii> d[maxn];

void solve(){
    cin >> n >> m >> r;
    for(int i=1;i<=r;i++){
        int c,x,y,diff;cin >> c >> x >> y >> diff;
        if(c==1 && !diff){
            cout << 0 << '\n';
            return;
        }
        d[c].push_back({{x-1,y-1},diff});
    }
    for(int mask=0;mask<(1<<(n-1));mask++){

        char cur='a';
        for(int i=0;i<n-1;i++){
            s[mask]+=cur;
            if((mask>>i)&1) cur++;
        }
        s[mask]+=cur;

        vector<pii> p;
        for(int i=0,j=0;i<n;i=j){
            while(j<n && s[mask][i]==s[mask][j]) j++;
            p.push_back({i,j-1});
        }
        function<void(int,int,int)> backtrack = [&](int m0,int m1,int x){
            if(x==(int)p.size()){
                trans[mask].push_back({m0,m1});
                return;
            }
            auto [l,r] = p[x];
            if(l==r) backtrack(m0^(1<<l),m1^(1<<l),x+1);
            else{
                backtrack(m0^(1<<l),m1^(1<<r),x+1);
                backtrack(m0^(1<<r),m1^(1<<l),x+1);
            }
        };
        backtrack(0,0,0);
    }

    dp[1][(1<<n)-1]=1;
    for(int i=1;i<=m;i++){
        for(int j=0;j<n;j++) for(int mask=0;mask<(1<<n);mask++)
            if(!((mask>>j)&1)) dp[i][mask]=(dp[i][mask]+dp[i][mask^(1<<j)])%mod;
        if(i==m){
            cout << dp[m][0] << '\n';
            return;
        }
        for(int x=0;x<(1<<(n-1));x++){
            bool check=true;
            for(auto p:d[i+1]) if((s[x][p.fi.fi]==s[x][p.fi.se])==p.se) check=false;
            if(!check) continue;
            for(auto [m0,m1]:trans[x]) dp[i+1][m1]=(dp[i+1][m1]+dp[i][m0])%mod;
        }
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}