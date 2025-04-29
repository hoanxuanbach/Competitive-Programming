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
#define ld long double
#define pii pair<int,int>
#define piii pair<pii,int>
#define mpp make_pair
#define fi first
#define se second
const int mod=1000010233;
const int maxn=1000005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=20;
const int maxa=1000000;
const int root=3;
const int base=101;
const int B=30000;

int val[B],kmp[B],rem=1,pw=1;
int s[B],sk[B],pos[B];

void solve(){
    int n,m;cin >> n >> m;

    int hh=0;
    for(int i=1;i<=n;i++){
        char c;cin >> c;
        hh=(1LL*hh*base+c-'a'+1)%mod;
        if(i%B==0 || i==n) val[(i-1)/B+1]=hh,hh=0;
    }

    kmp[0]=-1;kmp[1]=0;
    for(int i=2;i<=(n-1)/B;i++){
        int j=kmp[i-1];
        while(j>=0 && val[j+1]!=val[i]) j=kmp[j];
        kmp[i]=j+1;
    }
    kmp[0]=0;

    int kB=(n-1)%B+1,ans=0;
    for(int i=0;i<B;i++) pw=1LL*pw*base%mod;
    for(int i=0;i<kB;i++) rem=1LL*rem*base%mod;

    int hB=0,hkB=0;
    for(int i=1;i<=m;i++){
        char c;cin >> c;
        hB=(1LL*hB*base+c-'a'+1-1LL*s[i%B]*pw%mod+mod)%mod;
        hkB=(1LL*hkB*base+c-'a'+1-1LL*sk[i%kB]*rem%mod+mod)%mod;
        s[i%B]=sk[i%kB]=c-'a'+1;
        if(i>=kB && hkB==val[(n-1)/B+1] && pos[(i-kB)%B]==(n-1)/B) ans++;
        if(pos[i%B]==(n-1)/B) pos[i%B]=kmp[pos[i%B]];
        while(pos[i%B] && val[pos[i%B]+1]!=hB) pos[i%B]=kmp[pos[i%B]];
        if(pos[i%B]+1<=(n-1)/B && val[pos[i%B]+1]==hB) pos[i%B]++;
    }
    cout << ans << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
