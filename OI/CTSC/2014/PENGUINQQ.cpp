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
- insert(x)
- find_by_order(k): return iterator to the k-th smallest element
- order_of_key(x): the number of elements that are strictly smaller
*/
#include<bits/stdc++.h>
using namespace std;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_real_distribution<> pp(0.0,1.0);
const long long mod=100000000069;
const int maxn=30005;
const int maxs=205;
const int base=1009;
int n,l,k,sp[maxn][maxs],ans,mp[305];
long long ss[maxn],p[maxs],f[maxn];
void solve(){
    for(int i=0;i<26;i++){
        mp[char('a'+i)]=i;
        mp[char('A'+i)]=26+i;
    }
    for(int i=0;i<10;i++) mp[char('0'+i)]=52+i;
    mp['@']=62;mp['_']=63;
    cin >> n >> l >> k;
    p[0]=1;
    for(int i=1;i<=l;i++) p[i]=p[i-1]*base%mod;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=l;j++){
            char c;cin >> c;sp[i][j]=mp[c];
            ss[i]=(ss[i]*base+sp[i][j])%mod;
        }
    }
    for(int i=1;i<=l;i++){
        for(int j=1;j<=n;j++) f[j]=(ss[j]-p[l-i]*sp[j][i]%mod+mod)%mod;
        sort(f+1,f+n+1);
        int cnt=0;
        for(int j=1;j<=n;j++){
            if(f[j]==f[j-1]) cnt++;
            else cnt=1;
            ans+=cnt-1;
        }
    }
    cout << ans << '\n';
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
