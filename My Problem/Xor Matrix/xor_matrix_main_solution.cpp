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
const int maxn=200005;
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
 
int n;
 
void solve(){
    cin >> n;
    int cnt1=0,cnt2=0,cnt4=0,cnt6=0,cnt8=0,cnt12=0;
    for(int i=1;i<=n;i++){
        int a;cin >> a;
        if(a==2) cnt1++;
        else if(a==3) cnt2++;
        else if(a==4) cnt1+=2;
        else if(a==5) cnt4++;
        else if(a==6) cnt1++,cnt2++;
        else if(a==7) cnt6++;
        else if(a==8) cnt1+=3;
        else if(a==9) cnt8++;
        else if(a==10) cnt1++,cnt4++;
        else if(a==11) cnt2+=2;
        else if(a==12) cnt1+=2,cnt2++;
        else if(a==13) cnt12++;
    }
    string res;
    for(int i=0;i<cnt8;i++) res+="1000";
    for(int i=0;i<cnt4;i++) res+="100";
    for(int i=0;i<cnt2;i++) res+="10";
    for(int i=0;i<cnt12;i++) res+="1100";
    for(int i=0;i<cnt6;i++) res+="110";
    for(int i=0;i<cnt1;i++) res+="1";
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
