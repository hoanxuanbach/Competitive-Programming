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
const int maxn=2000005;
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

int fac[maxn],dfac[maxn],p2[maxn];
int C(int k,int n){
    if(k>n) return 0;
    return fac[n]*dfac[k]%mod*dfac[n-k]%mod;
}
void combi(int n){
    fac[0]=p2[0]=1;
    int inv2=(mod+1)/2;
    for(int i=1;i<=n;i++){
        fac[i]=fac[i-1]*i%mod;
        p2[i]=p2[i-1]*inv2%mod;
    }
    dfac[n]=power(fac[n],mod-2);
    for(int i=n;i>=1;i--) dfac[i-1]=dfac[i]*i%mod;
}
int euler(int k,int n){
    if(k==0) return (n==0);
    return C(k-1,n-1);
}

void solve(){
    int n,k,t;cin >> n >> k >> t;
    if(n<=(__int128)k*(k-1)/2 || n>(__int128)k*(k+3)/2){
        cout << 0 << '\n';
        return;
    }
    int K=k;
    combi(k);
    int d=0;
    if(n<k*(k+1)/2) d=1,n-=k*(k-1)/2;
    else n-=k*(k+1)/2,k++;
    t=__gcd(t,k);k=k/t;
    if(n%k!=0){
        cout << 0 << '\n';
        return;
    }
    n/=k;
    //cout << n << ' ' << t << ' ' << k << '\n';
    vector<int> num(2);
    num[0]=t-n;num[1]=n;
    int res=0;
    for(int p=1;p<=t;p++){
        vector<int> c(2);
        c[d]=(p+1)/2;c[d^1]=p/2;
        int total=euler(c[0],num[0])*euler(c[1],num[1])%mod;
        //cout << d << ' ' << p << ' ' << total << '\n';
        int lst=d^(p&1)^1,pos=c[1]-lst;
        //cout << ls
        total=total*p2[pos*k]%mod;
        if(lst>d) total=total*p2[k-1]%mod;
        res=(res+total)%mod;
    }
    res=res*fac[K]%mod;
    cout << res << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
