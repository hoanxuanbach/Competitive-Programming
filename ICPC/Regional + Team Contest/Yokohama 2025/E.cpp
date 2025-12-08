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

#define int long long

struct fr {
	int p, q;
	fr(int p, int q) : p(p), q(q) {}
	bool operator < (const fr &oth) const {
		return p * oth.q < oth.p * q;
	}

	void norm() {
		int g = __gcd(p, q);
		p /= g, q /= g;
	}
};

void Hollwo_Pelw(){
	vector<int> a(3);
	int k;

	cin >> a[0] >> a[1] >> a[2] >> k;

	fr res(1, 1e9);

	auto check = [&](fr s) -> bool {
		int val = 1;

		for (int i = 0; i < 3; i++) {
			int cnt = a[i] * s.q / s.p;
			if (cnt <= 0) {
				return 0;
			}
		}

		for (int i = 0; i < 3; i++) {
			int cnt = a[i] * s.q / s.p;
			if (cnt > k || val * cnt > k) {
				return 1;
			}
			val *= cnt;
		}

		// cout << "CHECK " << s.p << ' ' << s.q << '\n';
		// for (int i = 0; i < 3; i++) {
		// 	int cnt = a[i] * s.q / s.p;
		// 	cout << cnt << " \n"[i == 2];
		// }
		// cout << val << '\n';

		return val >= k;
	};

	for (int i = 0; i < 3; i++) {

		int l = 1, r = 2e9;

		while (l < r) {
			int mid = (l + r) / 2;

			if (check(fr(a[i], mid))) {
				r = mid;
			} else {
				l = mid + 1;
			}
		}

		res = max(res, fr(a[i], r));

		// cout << r << " \n";
	}

	res.norm();

	check(res);

	cout << res.p << ' ' << res.q << '\n';
}

