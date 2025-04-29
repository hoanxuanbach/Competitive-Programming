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
#define int long long
#define ld long double
#define pii pair<int,int>
#define piii pair<int,pii>
#define mpp make_pair
#define fi first
#define se second
const int inf=1e18;
const int mod=998244353;
const int maxn=200005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=25;
const int maxa=1000000;
const int root=3;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
const int iroot=power(3,mod-2);
const int base=131;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
//typedef pair<int, int> pii;
typedef vector<int> vi;

typedef vector<ll> vl;
void ntt(ll* x, ll* temp, ll* roots, int N, int skip) {
	if (N == 1) return;
	int n2 = N/2;
	ntt(x     , temp, roots, n2, skip*2);
	ntt(x+skip, temp, roots, n2, skip*2);
	rep(i,0,N) temp[i] = x[i*skip];
	rep(i,0,n2) {
		ll s = temp[2*i], t = temp[2*i+1] * roots[skip*i];
		x[skip*i] = (s + t) % mod; x[skip*(i+n2)] = (s - t) % mod;
	}
}
void ntt(vl& x, bool inv = false) {
	ll e = power(root, (mod-1) / sz(x));
	if (inv) e = power(e, mod-2);
	vl roots(sz(x), 1), temp = roots;
	rep(i,1,sz(x)) roots[i] = roots[i-1] * e % mod;
	ntt(&x[0], &temp[0], &roots[0], sz(x), 1);
}
vl mul(vl a, vl b) {
	int s = sz(a) + sz(b) - 1; if (s <= 0) return {};
	int L = s > 1 ? 32 - __builtin_clz(s - 1) : 0, n = 1 << L;
	if (s <= 200) { // (factor 10 optimization for |a|,|b| = 10)
		vl c(s);
		rep(i,0,sz(a)) rep(j,0,sz(b))
			c[i + j] = (c[i + j] + a[i] * b[j]) % mod;
		return c;
	}
	a.resize(n); ntt(a);
	b.resize(n); ntt(b);
	vl c(n); ll d = power(n, mod-2);
	rep(i,0,n) c[i] = a[i] * b[i] % mod * d % mod;
	ntt(c, true); c.resize(s); return c;
}

int n,m,sum;
vector<int> d[maxl];

void solve(){
    cin >> n >> m;
    d[0].assign(5,0);
    for(int i=0;i<5;i++) cin >> d[0][i],sum+=d[0][i];
    sum=power(sum%mod,mod-2);
    for(int i=0;i<5;i++) d[0][i]=d[0][i]*sum%mod;

    vector<int> res(n+1,0);res[n]=1;
    for(int i=1;i<17;i++) d[i]=mul(d[i-1],d[i-1]);

    function<vector<int>(vector<int>,int)> cal = [&](vector<int> x,int t){
        vector<int> add;
        if((int)x.size()>(1<<(t+1))){
            vector<int> rt(x.begin()+(1<<(t+1)),x.end());
            add=mul(rt,d[t]);
            x.resize(1<<(t+1));
        }
        if(t==0){
            vector<int> xx((int)x.size()+2,0);
            for(int i=0;i<(int)x.size();i++) for(int j=0;j<5;j++){
                if(i+j>=2) xx[i+j-2]=(xx[i+j-2]+x[i]*d[0][j])%mod;
            }
            x.swap(xx);
        }
        else x=cal(cal(x,t-1),t-1);
        if((int)x.size()<(int)add.size()) x.swap(add);
        for(int i=0;i<(int)add.size();i++) x[i]=(x[i]+add[i])%mod;
        return x;
    };

    for(int i=0;i<17;i++) if(m&(1<<i)) res=cal(res,i);
    int ans=0;
    for(int i=0;i<(int)res.size();i++) ans=(ans+res[i])%mod;
    cout << (ans+mod)%mod << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
