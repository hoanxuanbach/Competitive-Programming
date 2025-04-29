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

int nxt[25][205][205];

int f(int x,int sum,int d){
    if(nxt[x][sum][d]!=-1) return nxt[x][sum][d];
    int pd=d;
    if(x){
        for(int i=0;i<10;i++){
            d=f(x-1,sum+i,d);
            if(i==9) break;
            if(d<sum+i+1) d++;
            else d=0;
        }
    }
    return nxt[x][sum][pd]=d;
}

void solve(){
    int n;cin >> n;
    int sum=0,d=0,d10=1;
    for(int i=1;i<=18;i++) d10*=10;
    for(int i=18;i>=0;i--){
        int x=(n/d10)%10;
        for(int j=0;j<x;j++){
            d=f(i,sum,d),sum++;
            if(d<sum) d++;
            else d=0;
        }
        d10/=10;
    }
    cout << (d?"Algosia":"Bajtek") << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    memset(nxt,-1,sizeof(nxt));
    int test=1;cin >> test;
    while(test--) solve();
}
