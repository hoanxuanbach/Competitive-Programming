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
#pragma GCC optimize("Ofast,unroll-loops")
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
const int mod=998244353;
const int maxn=100005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=20;
const int maxa=100000;
const int root=3;
const int base=101;

int n,a[maxn],b[maxn],rk[maxn],ca[maxn],cb[maxn];

void solve(){
    cin >> n;
    for(int i=1;i<=n;i++) cin >> a[i],ca[a[i]]++;
    for(int i=1;i<=n;i++) cin >> b[i],cb[b[i]]++;
    for(int i=maxa;i>=1;i--) ca[i]+=ca[i+1],cb[i]+=cb[i+1];
    for(int i=1;i<=n;i++) rk[i]=ca[a[i]+1]+cb[b[i]+1];
    for(int i=1;i<=maxa;i++) ca[i]-=ca[i+1],cb[i]-=cb[i+1];
    int q;cin >> q;
    while(q--){
        int id,i;cin >> id >> i;
        char c;
        if(id==3){
            int res=0;
            for(int j=1;j<=n;j++) res+=rk[j]<rk[i];
            cout << res+1 << '\n';
        }
        else if(id==1){
            cin >> c;
            if(c=='+'){
                for(int j=1;j<=n;j++) rk[j]+=a[j]==a[i];
                ca[a[i]]--;
                a[i]++;
                ca[a[i]]++;
                rk[i]-=ca[a[i]];
            }
            else{
                rk[i]+=ca[a[i]];
                ca[a[i]]--;
                a[i]--;
                ca[a[i]]++;
                for(int j=1;j<=n;j++) rk[j]-=a[j]==a[i];
            }
        }
        else if(id==2){
            cin >> c;
            if(c=='+'){
                for(int j=1;j<=n;j++) rk[j]+=b[j]==b[i];
                cb[b[i]]--;
                b[i]++;
                cb[b[i]]++;
                rk[i]-=cb[b[i]];
            }
            else{
                rk[i]+=cb[b[i]];
                cb[b[i]]--;
                b[i]--;
                cb[b[i]]++;
                for(int j=1;j<=n;j++) rk[j]-=b[j]==b[i];
            }
        }
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();

}
