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
#define ull __int128
#define ld long double
#define pii pair<ull,ull>
#define piii pair<pii,int>
const int maxn=2005;

vector<ull> ci[maxn],ca[maxn],cg[maxn];

void FST(vector<ull> &a, bool inv) {
    int n=(int)a.size();
	for (int step = 1; step < n; step *= 2) {
		for (int i = 0; i < n; i += 2 * step) for(int j=i;j<i+step;j++) {
			ull &u = a[j], &v = a[j + step];
			tie(u, v) = pii(u + v, u - v);
		}
	}
	if (inv) for (ull& x : a) x /= n;
}
vector<ull> mul(vector<ull> a, vector<ull> b) {
    int n=(int)a.size();
	FST(a, 0); FST(b, 0);
	for(int i=0;i<n;i++) a[i] *= b[i];
	FST(a, 1);
	return a;
}

void solve(){
    int uib,uab,ugb,uig,uag,ugg;
    cin >> uib >> uab >> ugb >> uig >> uag >> ugg;
    for(int i=0;i<=2000;i++){
        ci[i].assign(2048,0ULL);
        ca[i].assign(2048,0ULL);
        cg[i].assign(2048,0ULL);
    }
    for(int i=0;i<=uib;i++) for(int j=0;j<=uig;j++) ci[abs(i-j)][i^j]++;
    for(int i=0;i<=uab;i++) for(int j=0;j<=uag;j++) ca[abs(i-j)][i^j]++;
    for(int i=0;i<=ugb;i++) for(int j=0;j<=ugg;j++) cg[abs(i-j)][i^j]++;
    for(int i=1;i<=2000;i++){
        for(int j=0;j<2048;j++){
            ci[i][j]+=ci[i-1][j];
            ca[i][j]+=ca[i-1][j];
            cg[i][j]+=cg[i-1][j];
        }
    }
    for(int i=0;i<=2000;i++){
        ci[i]=mul(ci[i],ca[i]);
        ci[i]=mul(ci[i],cg[i]);
    }

    unsigned long long res=0;
    for(int i=2000;i>=0;i--){
        for(int j=0;j<2048;j++){
            if(i) ci[i][j]-=ci[i-1][j];
            res+=ci[i][j]*(i^j);
        }
    }
    cout << res << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    for(int t=1;t<=test;t++){
        cout << "Case #" << t << ": ";
        solve();
    }
}
