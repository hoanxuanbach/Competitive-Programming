#include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/trie_policy.hpp>
// #include <ext/rope>

using namespace std;
// using namespace __gnu_cxx;
// using namespace __gnu_pbds;

void Hollwo_Pelw();

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
		Hollwo_Pelw();
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

const int N = 1e5 + 5;

template<class Mint, int MAXN>
struct combinatoric {
	Mint ifac[MAXN], fac[MAXN];
 
	combinatoric() {
		fac[0] = 1;
		for (int i = 1; i < MAXN; i++)
			fac[i] = fac[i - 1] * i;
		ifac[MAXN - 1] = fac[MAXN - 1].inv();
		for (int i = MAXN - 1; i; i--)
			ifac[i - 1] = ifac[i] * i;
	}
 
	Mint C(int n, int k) {
		return k > n || k < 0 ? 0 : fac[n] * ifac[n - k] * ifac[k];
	}
 
	Mint P(int n, int k) {
		return k > n || k < 0 ? 0 : fac[n] * ifac[n - k];
	}
};
 
combinatoric<Mint, N> comb;

inline Mint ways(int n, int m) {
	return comb.C(n + m - 2, n - 1);
}

vector<pair<int, int>> pos[N];
int n, m;

Mint solve_small(vector<pair<int, int>> &a) {
	sort(a.begin(), a.end());
	
	int sz = a.size();

	vector<Mint> dp(sz);

	for (int i = 0; i < sz; i++) {
		auto [cx, cy] = a[i];

		dp[i] = ways(cx + 1, cy + 1);
		
		for (int j = 0; j < i; j++) {
			auto [lx, ly] = a[j];

			if (lx <= cx && ly <= cy) {
				dp[i] -= dp[j] * ways(cx - lx + 1, cy - ly + 1);
			}

		}

		// cout << cx << ' ' << cy << ' ' << dp[i] << '\n';

	}

	Mint res = ways(n, m);

	for (int i = 0; i < sz; i++) {
		auto [x, y] = a[i];
		res -= dp[i] * ways(n - x, m - y);
	}

	// cout << res << "\n";

	return ways(n, m) - res;
}

Mint solve_large(vector<pair<int, int>> &a) {
	vector<vector<int>> vis(n, vector<int>(m));

	for (auto [i, j] : a) {
		vis[i][j] = 1;
	}

	vector<vector<Mint>> dp(n + 1, vector<Mint>(m + 1, 0));

	dp[1][0] = 1;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) if (!vis[i][j]) {
			dp[i + 1][j + 1] = dp[i + 1][j] + dp[i][j + 1];
		}
	}

	// cout << dp[n][m] << '\n';
	// for (int i = 1; i <= n; i++) {
	// 	for (int j = 1; j <= m; j++) {
	// 		cout << dp[i][j] << " \n"[j == m];
	// 	}
	// }

	return ways(n, m) - dp[n][m];
}

void Hollwo_Pelw(){
	cin >> n >> m;

	for (int i = 1; i <= n * m; i++)
		pos[i].clear();

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			int c; cin >> c;
			pos[c].push_back({i, j});
		}
	}

	Mint res = 0;
	for (int i = 1; i <= n * m; i++) {
		// cout << "solve " << i << '\n';
		if (1ll * pos[i].size() * pos[i].size() <= n * m) {
			res += solve_small(pos[i]);
		} else {
			res += solve_large(pos[i]);
		}

	}

	cout << res << '\n';
}