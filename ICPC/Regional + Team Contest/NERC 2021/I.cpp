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
#define pii pair<int,int>
const int inf=1e9;
const int mod=998244353;
const int mod2=1e9+7;
const int maxn=1006;
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
const long double b=0.9;
long double wt[maxn],w[2];
int n,m;
long double rnd(long double l,long double r){
    uniform_real_distribution<long double> pp(l,r);
    return pp(rng);
}
void solve(){
    cin >> n >> m;
    for(int i=0;i<n;i++) wt[i]=1;
    for(int i=1;i<=m;i++){
        string s;cin >> s;w[0]=w[1]=0;
        for(int j=0;j<n;j++) w[s[j]-'0']+=wt[j];
        if(rnd(0,w[0]+w[1])<=w[0]) cout << 0 << endl;
        else cout << 1 << endl;
        char c;cin >> c;
        for(int j=0;j<n;j++){
            if(c!=s[j]) wt[j]*=b;
        }
    }
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int t=1;//cin >> t;
    while(t--) solve();
}
