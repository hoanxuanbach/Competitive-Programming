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

int fac[maxn],dfac[maxn],inv[maxn];
int C(int n,int k){
    if(k>n) return 0;
    return fac[n]*dfac[k]%mod*dfac[n-k]%mod;
}
void combi(int n){
    fac[0]=1;
    for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;
    dfac[n]=power(fac[n],mod-2);
    for(int i=n;i>=1;i--){
        dfac[i-1]=dfac[i]*i%mod;
        inv[i]=dfac[i]*fac[i-1]%mod;
    }
}

void fft(vector<int> &a,bool invert){
    int n=(int)a.size();
    for(int i=1,j=0;i<n;i++){
        int bit=n>>1;
        while(j&bit){j^=bit;bit>>=1;}
        j^=bit;
        if(i<j) swap(a[i],a[j]);
    }
    for(int len=2;len<=n;len<<=1){
        int wn=power((invert?iroot:root),(mod-1)/len);
        for(int i=0;i<n;i+=len){
            int w=1;
            for(int j=0;j<len/2;j++){
                int u=a[i+j],v=a[i+j+len/2]*w%mod;
                a[i+j]=(u+v)%mod;
                a[i+j+len/2]=(u-v+mod)%mod;
                w=w*wn%mod;
            }
        }
    }
    if(invert){
        int dd=power(n,mod-2);
        for(int i=0;i<n;i++) a[i]=a[i]*dd%mod;
    }
    return;
}

vector<int> mul(vector<int> a,vector<int> b){
    int n=(int)a.size()+(int)b.size(),sz=1;
    while(sz<n) sz<<=1;
    a.resize(sz);b.resize(sz);
    fft(a,false);fft(b,false);
    for(int i=0;i<sz;i++) a[i]=a[i]*b[i]%mod;
    fft(a,true);
    return a;
}

void solve(){
    int n,m;cin >> n >> m;
    combi(2000000);
    int res=1;
    /*
    for(int k=0;k<=m;k++){
        for(int peak=0;peak<=k;peak++){
            int num=C(k,peak)*C(k,peak-1)%mod*inv[k]%mod;
            res=(res+num*C(n+2*k-2*peak+1,n-2*peak+1))%mod;
            //k!/(k-peak)!/peak!*k!/(k-peak+1)!/(peak-1)!*1/k*(n+2*k-2*peak+1)!/2*k!/(n-2*peak+1)!
            //k!*k!*1/k/(2*k)! * /peak!/(peak-1)!/(n-2*peak+1)! * /(k-peak)!/(k-peak+1)!*(n+2*k-2*peak+1)!
        }
    }
    */
    vector<int> K(m+1,0),Peak(m+1,0);
    for(int i=0;i<=m;i++){
        K[i]=fac[i]*fac[i]%mod*inv[i]%mod*dfac[2*i]%mod;
    }
    for(int i=1;i<=min(m,(n+1)/2);i++){
        Peak[m-i]=dfac[i]*dfac[i-1]%mod*dfac[n-2*i+1]%mod;
    }
    vector<int> ans=mul(K,Peak);
    for(int i=0;i<=m;i++){
        res=(res+ans[m+i]*dfac[i]%mod*dfac[i+1]%mod*fac[n+2*i+1]%mod)%mod;
    }
    cout << res << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}

