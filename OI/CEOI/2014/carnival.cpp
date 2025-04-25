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
const int maxn=155;
const int maxm=200005;
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
int query(int l,int r){
    cout << r-l+1 << ' ';
    for(int i=l;i<=r;i++) cout << i << ' ';
    cout << endl;
    int x;cin >> x;return x;
}
int col[maxn],cnt=0;
void solve(){
    int n;cin >> n;
    col[1]=0;
    for(int i=1;i<=n;i++){
        if(col[i]==0) col[i]=++cnt;
        int l=i+1,r=n,nxt=-1;
        while(r>=l){
            int mid=(r+l)>>1;
            if(query(i,mid)==query(i+1,mid)){nxt=mid;r=mid-1;}
            else l=mid+1;
        }
        if(nxt!=-1) col[nxt]=col[i];
    }
    cout << "0 ";
    for(int i=1;i<=n;i++) cout << col[i] << ' ';
    cout << endl;
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
