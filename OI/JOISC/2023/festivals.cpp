// Judges with GCC >= 12 only needs Ofast
// #pragma GCC optimintze("O3,no-stack-protector,fast-math,unroll-loops,tree-vectorize")
// MLE optimintzation
// #pragma GCC optimintze("conserve-stack")
// Old judges
// #pragma GCC target("sse4.2,popcnt,lzcnt,abm,mmx,fma,bmint,bmint2")
// New judges. Test with assert(__builtin_cpu_supports("avx2"));
// #pragma GCC target("avx2,popcnt,lzcnt,abm,bmint,bmint2,fma,tune=native")
// Atcoder
#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,popcnt,lzcnt,abm,bmi,bmi2,fma")
#include<bits/stdc++.h>
using namespace std;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_real_distribution<> pp(0.0,1.0);
#define ll long long
#define ld long double
#define pii pair<int,int>
#define piii pair<int,pii>
#define fi first
#define se second
const int inf=1e9;
int mod;
const int mod2=1e9+7;
const int maxn=35;
const int bl=650;
const int maxs=650;
const int maxm=200005;
const int maxq=500005;
const int maxl=20;
const int maxa=1000005;


struct mint {
	ll v; explicit operator ll() const { return v; }
	mint() { v = 0; }
	mint(ll _v) {
		v = (-mod < _v && _v < mod) ? _v : _v % mod;
		if (v < 0) v += mod;
	}
	friend bool operator==(const mint& a, const mint& b) {
		return a.v == b.v; }
	friend bool operator!=(const mint& a, const mint& b) {
		return !(a == b); }
	friend bool operator<(const mint& a, const mint& b) {
		return a.v < b.v; }

	mint& operator+=(const mint& m) {
		if ((v += m.v) >= mod) v -= mod;
		return *this; }
	mint& operator-=(const mint& m) {
		if ((v -= m.v) < 0) v += mod;
		return *this; }
	mint& operator*=(const mint& m) {
		v = v*m.v%mod; return *this; }
	mint& operator/=(const mint& m) { return (*this) *= inv(m); }
	friend mint pow(mint a, ll p) {
		mint ans = 1; assert(p >= 0);
		for (; p; p /= 2, a *= a) if (p&1) ans *= a;
		return ans;
	}
	friend mint inv(const mint& a) { assert(a.v != 0);
		return pow(a,mod-2); }

	mint operator-() const { return mint(-v); }
	mint& operator++() { return *this += 1; }
	mint& operator--() { return *this -= 1; }
    mint operator++(int) { v++; if (v == mod) v = 0; return mint(v); }
    mint operator--(int) { v--; if (v < 0) v = mod-1; return mint(v); }
	friend mint operator+(mint a, const mint& b) { return a += b; }
	friend mint operator-(mint a, const mint& b) { return a -= b; }
	friend mint operator*(mint a, const mint& b) { return a *= b; }
	friend mint operator/(mint a, const mint& b) { return a /= b; }
    friend ostream& operator<<(ostream& os, const mint& m) {
        os << m.v; return os;
    }
    friend istream& operator>>(istream& is, mint& m) {
        ll x; is >> x;
        m.v = x;
        return is;
    }
};

void solve(){
    int n;cin >> n >> mod;
    vector<mint> fac(2*n+2,1),dfac(2*n+2,1),f(n+1,0),g(n+1,0),inv(2*n+2,1);
    for(int i=2;i<=2*n+1;i++){
        fac[i]=fac[i-1]*i;
        inv[i]=mod-(mod/i)*inv[mod%i];
        dfac[i]=dfac[i-1]*inv[i];
    }
    mint s;s=g[0]=f[0]=1;
    for(int i=1;i<=n;i++){
        mint x=0,y=0;
        for(int j=i;j>=1;j--) x+=fac[i*2-j-1]*dfac[(i-j)*2]*(g[i-j]+f[i-j]*(j-1)),y+=x;
        g[i]=x;f[i]=y*inv[2*i+1];
    }
    for(int i=1;i<=2*n;i+=2) s*=i%mod;
    cout << s-g[n] << '\n';
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
