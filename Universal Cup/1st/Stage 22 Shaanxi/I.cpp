#include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/trie_policy.hpp>
// #include <ext/rope>

using namespace std;
// using namespace __gnu_cxx;
// using namespace __gnu_pbds;

void Hollwo_Pelw(int testcount);

signed main(){
#ifndef hollwo_pelw_local
	if (fopen(".inp", "r"))
		assert(freopen(".inp", "r", stdin)), assert(freopen(".out", "w", stdout));
#else
	using namespace chrono;
	auto start = steady_clock::now();
#endif
	cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
	int testcases = 1;
	cin >> testcases;
	for (int test = 1; test <= testcases; test++){
		// cout << "Case #" << test << ": ";
		Hollwo_Pelw(test);
	}
#ifdef hollwo_pelw_local
	auto end = steady_clock::now();
	cout << "\nExecution time : " << duration_cast<milliseconds> (end - start).count() << "[ms]" << endl;
#endif
}

template<class T> struct mod_int {
	static constexpr int mod() { return T::mod; }

	int v;
	mod_int(long long _v = 0) : v(norm(_v)) {}

	inline int norm(long long a) { return a < 0 ? a % mod() + mod() : a % mod(); }
	mod_int neg() const { return v == 0 ? 0 : mod() - v; }

	template <typename U> explicit operator U() const { return v; }
	mod_int operator - () const { return neg(); }
	mod_int operator + () const { return mod_int(*this); }
	mod_int& operator -- () { if (v == 0) v = mod(); -- v; return *this; }
	friend mod_int operator -- (mod_int& a, signed) { mod_int r = a; --a; return r; }
	mod_int& operator ++ () { ++ v; if (v == mod()) v = 0; return *this; }
	friend mod_int operator ++ (mod_int& a, signed) { mod_int r = a; ++a; return r; }
	
#define defop(type, op) \
	friend inline type operator op (type a, const type &b) { return a op##= b; } \
	type& operator op##= (const type &oth)

	defop(mod_int, +) { if ((v += oth.v) >= mod()) v -= mod(); return *this; }
	defop(mod_int, -) { if ((v -= oth.v) < 0) v += mod(); return *this; }
	defop(mod_int, *) { return *this = norm(1ll * v * oth.v); }
	defop(mod_int, /) { return *this *= oth.inv(); }

	inline mod_int pow(long long b) const {
		mod_int a = *this, r = 1;
		for (; b; b >>= 1, a *= a)
			if (b & 1) r *= a;
		return r;
	}
	inline mod_int inv() const { return pow(mod() - 2); }

#undef defop

#define compare(op) friend bool operator op \
(const mod_int& lhs, const mod_int& rhs) { return lhs.v op rhs.v; }
	compare(==) compare(!=) compare(<) compare(<=) compare(>) compare(>=)
#undef compare

	friend std::ostream& operator << (std::ostream& out, const mod_int& n) { return out << int(n); }
	friend std::istream& operator >> (std::istream& inp, mod_int& n) { long long x; inp >> x; n = mod_int(x); return inp; }
};

struct modular { static constexpr int mod = static_cast<int>(998244353); };

// struct modular { static int mod; }; int modular::mod = 1;

using Mint = mod_int<modular>;

const long long inf = 1e18;

array<int, 4> pr = {2, 3, 5, 7}, maxp = {65, 40, 30, 25}, add[10];

Mint dp[65][40][30][25];
int vis[65][40][30][25];
long long val[65][40][30][25];

struct state {
	array<int, 4> a;

	inline state update(int d) {
		state x;
		for (int i = 0; i < 4; i++) {
			x.a[i] = a[i] + add[d][i];
		}
		return x;
	}
};

struct __init__ {
	__init__() {

		for (int i = 1; i <= 10; i++) {

			for (int j = 0, x = i; j < 4; j++) {
				add[i - 1][j] = 0;
				while (x > 1 && x % pr[j] ==  0) {
					x /= pr[j];
					add[i - 1][j] ++;
				}
			}

		}

		val[0][0][0][0] = 1;
		for (int i = 0; i < 65; i++) {	
			for (int j = 0; j < 40; j++) {
				for (int k = 0; k < 30; k++) {
					for (int l = 0; l < 25; l++) {
						long long v = val[i][j][k][l];

						if (v == 0) { // inf 
							continue;
						}

						val[i + 1][j][k][l] = (v * 2 > inf ? 0 : v * 2);
						val[i][j + 1][k][l] = (v * 3 > inf ? 0 : v * 3);
						val[i][j][k + 1][l] = (v * 5 > inf ? 0 : v * 5);
						val[i][j][k][l + 1] = (v * 7 > inf ? 0 : v * 7);
					}
				}
			}
		}

	}
} __init__;

long long n, limit;

#define g(st) st.a[0]][st.a[1]][st.a[2]][st.a[3]

Mint solve(state st, int tc) {
	if (vis[g(st)] > tc) {
		return dp[g(st)];
	}

	long long v = val[g(st)];

	// cout << "SOLVE " << st.a[0] << ' ' << st.a[1] << ' ' << st.a[2] << ' ' << st.a[3] << " " << val[g(st)] * n << '\n';

	if (v == 0 || (__int128) v * n > (__int128) limit) {
		return 0;
	}

	array<int, 10> cnt = {};
	int dcnt = 0;

	__int128 V=(__int128)v*n;
	while (V) {
		cnt[V % 10] ++, dcnt ++;
		V /= 10;
	}

	Mint sum = dcnt;
	for (int i = 1; i < 10; i++) if (cnt[i]) {
		sum += cnt[i] * solve(st.update(i), tc);
	}


	vis[g(st)] = tc + 1;
	return dp[g(st)] = sum / (dcnt - cnt[0]);
}

void Hollwo_Pelw([[maybe_unused]] int testcount){
	cin >> n >> limit;

	state st;
	st.a = {0, 0, 0, 0};

	cout << solve(st, testcount) << '\n';
}