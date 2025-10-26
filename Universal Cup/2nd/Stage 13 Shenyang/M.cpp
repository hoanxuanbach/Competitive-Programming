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
const int maxn=200005;
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

int f(int k){
    int res=(power(4,k)+mod-4)%mod*power(3,mod-2)%mod;
    return res;
}

void solve(){
    int k;
    string s,t;
    cin >> s >> t >> k;
    reverse(s.begin(),s.end());
    reverse(t.begin(),t.end());
    if((int)s.size()<(int)t.size()) swap(s,t);
    for(int i=0;i<(int)t.size();i++) s[i]=char(((s[i]-'0')^(t[i]-'0'))+'0');
    while(!s.empty() && s.back()=='0') s.pop_back();
    if(s.empty()){
        cout << f(k) << '\n';
        return;
    }
    if((int)s.size()&1) s+='0';
    int p=0;
    while(s[p]=='0' && s[p+1]=='0') p+=2;
    if(k>p/2+1){
        cout << -1 << '\n';
        return;
    }
    int res=f(k);
    for(int i=(int)s.size()-2;i>=0;i-=2){
        int d=(s[i+1]-'0')<<1|(s[i]-'0'),mul=f(i/2+1);
        if(d>=2) d^=1;
        res=(res+(mul+1)*d)%mod;
    }
    cout << res << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}
