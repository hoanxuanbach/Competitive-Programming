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
const int maxn=5005;
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
int k,q,d,m,n,a[maxn];
unordered_set<int> s[75];
void solve(){
    cin >> n;
    for(int i=0;i<=70;i++) s[i].clear();
    s[0].insert(n);
    vector<int> ans;
    bool ok=false;
    int cur=-1,deg=-1;
    for(int i=0;i<=70;i++){
        for(int v:s[i]){
            for(int j=1;j<=d;j++){
                if(v==a[j]){cur=v;deg=i;ok=true;break;}
                if((v-a[j])%k==0 && i<70) s[i+1].insert((v-a[j])/k);
            }
            if(ok) break;
        }
        if(ok) break;
    }
    if(!ok){
        cout << "IMPOSSIBLE" << endl;
        return;
    }
    ans.push_back(cur);
    while(deg){
        deg--;
        for(int i=1;i<=d;i++){
            if(s[deg].find(cur*k+a[i])!=s[deg].end()){
                ans.push_back(a[i]);
                cur=cur*k+a[i];
                break;
            }
        }
    }
    for(int v:ans) cout << v << ' ';
    cout << endl;
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> k >> q >> d >> m;
    for(int i=1;i<=d;i++) cin >> a[i];
    while(q--) solve();
}