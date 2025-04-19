// Judges with GCC >= 12 only needs Ofast
// #pragma GCC optimize("O3,no-stack-protector,fast-math,unroll-loops,tree-vectorize")
// MLE optimization
// #pragma GCC optimize("conserve-stack")
// Old judges
// #pragma GCC target("sse4.2,popcnt,lzcnt,abm,mmx,fma,bmi,bmi2")
// New judges. Test with assert(__builtin_cpu_supports("avx2"));
// #pragma GCC target("avx2,popcnt,lzcnt,abm,bmi,bmi2,fma,tune=native")
// Atcoder
#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,popcnt,lzcnt,abm,bmi,bmi2,fma")
#include<bits/stdc++.h>
using namespace std;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_real_distribution<> pp(0.0,1.0);
#define ld long double
#define pii pair<int,int>
#define piii pair<int,pii>
#define fi first
#define se second
const int mod=998244353;
const int mod2=1e9+7;
const int maxn=300005;
const int bl=650;
const int maxs=650;
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
int n,m,Min[1030][1030],num[25],cur[maxn],ok[1030][1030];
vector<int> x[1030];
void solve(){
    cin >> n >> m;
    for(int i=1;i<=n;i++){
        for(int j=0;j<m;j++){
            int a;cin >> a;
            cur[i]+=a*(1<<j);
            num[j]+=a;
        }
        x[cur[i]&((1<<(m/2))-1)].push_back(cur[i]>>(m/2));
    }
    for(int i=0;i<(1<<(m/2));i++){
        for(int k:x[i]) ok[i][k]++;
        for(int j=0;j<(1<<(m-m/2));j++){
            Min[i][j]=m+1;
            for(int k:x[i]) Min[i][j]=min(Min[i][j],__builtin_popcount(k&j));
        }
    }
    for(int i=1;i<=n;i++){
        int check=0,ans=0,add=m+1,f1=(cur[i]&((1<<(m/2))-1)),f2=cur[i]>>(m/2);
        for(int j=0;j<m;j++){
            int total=(num[j]-((cur[i]>>j)&1));
            if(total==(n/2)) check^=(1<<j);
            else if(total>(n/2)) ans++;
        }
        for(int j=0;j<(1<<m/2);j++){
            if(j!=f1) add=min(add,__builtin_popcount(check&j)+Min[j][check>>(m/2)]);
            else{
                for(int k=0;k<(1<<(m-m/2));k++){
                    if(ok[j][k] && (k!=f2 || ok[j][k]>=2)) add=min(add,__builtin_popcount(check&j)+__builtin_popcount(k&(check>>(m/2))));
                }
            }
        }
        ans+=__builtin_popcount(check)-add;
        cout << ans << '\n';
    }
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}