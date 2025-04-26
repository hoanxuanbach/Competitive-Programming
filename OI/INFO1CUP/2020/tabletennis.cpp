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
const int mod=998244353;
const int maxn=200005;
const int maxa=1000005;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
int n,k,a[maxn];
map<int,bool> mp;
bool cal(int i,int j){
    if(mp[a[i]+a[j]]) return false;
    mp[a[i]+a[j]]=true;
    int cnt=i-1+n+k-j;
    vector<int> ans;ans.push_back(a[i]);ans.push_back(a[j]);
    int lt=i+1,rt=j-1,sum=a[i]+a[j];
    while(lt<rt){
        if((int)ans.size()==n) break;
        while(rt>lt && a[rt]+a[lt]>sum){
            rt--;cnt++;
            if(cnt>k) return false;
        }
        if(rt==lt) break;
        if(a[rt]+a[lt]==sum){ans.push_back(a[lt]);ans.push_back(a[rt]);lt++;rt--;}
        else{lt++;cnt++;}
        if(cnt>k) return false;
    }
    if((int)ans.size()==n){
        sort(ans.begin(),ans.end());
        for(int v:ans) cout << v << ' ';
        return true;
    }
    return false;
}
void solve(){
    cin >> n >> k;
    for(int i=1;i<=n+k;i++) cin >> a[i];
    for(int i=1;i<=k+1;i++){
        for(int j=n+k;j>=max(i+1,n+i-1);j--){
            if(cal(i,j)) return;
        }
    }
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int t=1;//cin >> t;
    while(t--) solve();
}
