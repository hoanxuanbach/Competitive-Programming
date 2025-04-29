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
#define pii pair<int,int>
const int inf=1e9;
const int mod=998244353;
const int maxn=50005;
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
int a[maxn],b[maxn];
vector<int> lt[maxn],rt[maxn],pos[maxn];
bitset<100005> cur,res;
void solve(){
    int n,Min=inf;cin >> n;
    for(int i=1;i<=n;i++){
        char ch;cin >> ch;
        a[i]=a[i-1]+(ch=='0'?-1:1);
        Min=min(Min,a[i]);
        lt[i].clear();rt[i].clear();pos[i].clear();
    }
    int lst=n+1;
    for(int i=1;i<=n;i++){
        char ch;cin >> ch;
        b[i]=ch-'0';
        if(b[i]==0){
            if(a[i]>0) lst=min(lst,i);
            lt[a[i]-Min].push_back(i);
        }
        else{
            if(a[i]<=0) lst=min(lst,i);
            rt[a[i]-Min+1].push_back(i);
        }
        pos[a[i]-Min+1].push_back(i);
    }
    cur.reset();res.reset();
    for(int i=1;i<=n;i++){
        for(int v:pos[i]) cur[n-v]=1;
        for(int v:lt[i]) res|=(cur<<v);
    }
    cur.reset();
    for(int i=n;i>=1;i--){
        for(int v:pos[i]) cur[n-v]=1;
        for(int v:rt[i]) res|=(cur<<v);
    }
    for(int i=lst;i<=n;i++) res[n+i]=1;
    for(int i=1;i<=n;i++) cout << (res[n+i]^1);
    cout << '\n';
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int t=1;cin >> t;
    while(t--) solve();
}
