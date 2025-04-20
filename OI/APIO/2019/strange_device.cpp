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
#include<bits/stdc++.h>
using namespace std;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_real_distribution<> pp(0.0,1.0);
#define int long long
#define ld long double
#define pii pair<int,int>
#define piii pair<int,pii>
#define fi first
#define se second
const int inf=1e18;
const int mod=998244353;
const int mod2=1e9+7;
const int maxn=200005;
const int maxq=500005;
const int maxl=20;
const int maxa=1000005;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
map<int,int> mp;
void solve(){
    int n,a,b;cin >> n >> a >> b;
    a=a/__gcd(a,b+1);
    if(a>inf/b){
        int ans=0;
        for(int i=1;i<=n;i++){
            int l,r;cin >> l >> r;
            ans+=(r-l+1);
        }
        cout << ans << '\n';
        return;
    }
    a*=b;
    for(int i=1;i<=n;i++){
        int l,r;cin >> l >> r;
        if((r-l+1)>=a){
            cout << a << '\n';
            return;
        }
        l%=a;r%=a;
        if(l<=r){mp[l]++;mp[r+1]--;}
        else{mp[0]++;mp[r+1]--;mp[l]++;mp[a]--;}
    }
    int ans=0,cur=0,pre=-1;
    for(auto x:mp){
        if(cur) ans+=(x.first-pre);
        cur+=x.second;pre=x.first;
    }
    cout << ans << '\n';
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
