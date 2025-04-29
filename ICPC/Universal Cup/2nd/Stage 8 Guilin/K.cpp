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
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;
#define ld long double
#define pii pair<int,int>
#define piii pair<pii,int>
#define mpp make_pair
#define fi first
#define se second
const int mod=998244353;
const int maxn=370005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=20;
const int maxa=1000000;
const int root=3;
const int base=101;

bool check[maxn];
vector<int> P[maxn];
int n,m,fac[185];

int h(vector<int> &p){
    int res=0;
    ordered_set x;
    for(int i=0;i<n;i++){
        res=(res+1LL*x.order_of_key(p[i])*fac[i]%mod)%mod;
        x.insert(p[i]);
    }
    return res;
}

void solve(){
    cin >> n >> m;
    vector<vector<int>> a(m,vector<int>(n,0));
    for(int i=0;i<m;i++) for(int j=0;j<n;j++) cin >> a[i][j],a[i][j]--;
    fac[0]=1;
    for(int i=1;i<=n;i++) fac[i]=1LL*fac[i-1]*i%mod;
    if(n<=9){
        vector<int> p(n);
        iota(p.begin(),p.end(),0);
        do{P[h(p)]=p;}while(next_permutation(p.begin(),p.end()));
        for(int i=m-1;i>=0;i--){
            vector<int> nw;
            for(int t=0;t<fac[n];t++){
                if(!check[t]) continue;
                vector<int> res=P[t];
                for(int j=0;j<n;j++) res[j]=a[i][res[j]];
                nw.push_back(h(res));
            }
            for(int x:nw) check[x]=1;
            check[h(a[i])]=1;
        }
        int ans=0;
        for(int i=0;i<fac[n];i++) ans+=check[i];
        cout << ans << '\n';
    }
    else{
        set<int> s;
        for(int mask=1;mask<(1<<m);mask++){
            vector<int> res(n,0);
            iota(res.begin(),res.end(),0);
            for(int i=m-1;i>=0;i--){
                if(!((mask>>i)&1)) continue;
                for(int j=0;j<n;j++) res[j]=a[i][res[j]];
            }
            s.insert(h(res));
        }
        cout << (int)s.size() << '\n';
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
