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

map<int, int> mp;
int n, k, fmx[2], fmn[2];

void Hollwo_Pelw(){
	cin >> n >> k;
	mp.clear();

	for (int r = 0; r < 2; r++) {
		fmx[r] = 0;
		fmn[r] = n + 1;
	}

	for (int i = 1, r, c; i <= k; i++) {
		cin >> r >> c;
		-- r;
		mp[c] |= 1 << r;

		fmx[r] = max(fmx[r], c);
		fmn[r] = min(fmn[r], c);
	}

	if (fmx[0] == 0 || fmx[1] == 0) {
		// all in one row
		// cout << Mint(2) * Mint(2) * Mint(4).pow(k) << '\n';
		cout << Mint(4).pow(k + 1) << '\n';
		return ;
	}

	Mint ans = 0;

	for (int smn = 0; smn < 4; smn ++) {
		for (int smx = 0; smx < 4; smx ++) {

			auto check = [&](int p, int r) -> bool {
				if (smn & (1 << r)) {
					if (fmn[r] > p) {
						return 0;
					}
				}
				if (smx & (1 << r)) {
					if (fmx[r] < p) {
						return 0;
					}
				}
				return 1;
			};

			Mint res = 1;

			for (auto [p, v] : mp) {

				if (v == 1) {
					res *= check(p, 1) ? 4 : 2;
				} else if (v == 2) {
					res *= check(p, 0) ? 4 : 2;
				} else {
					res *= 4;
				}

			}

			ans += res;
		}
	}
	cout << ans << '\n';
}