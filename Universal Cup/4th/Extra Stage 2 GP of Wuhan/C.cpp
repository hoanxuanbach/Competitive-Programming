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

vector<vector<int>> flip(vector<vector<int>> s) {
	if (s.empty()) return s;
	int n = s.size(), m = s[0].size();

	vector<vector<int>> res(m, vector<int>(n));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			res[j][i] = s[i][j];
		}
	}

	return res;
}

vector<vector<int>> solve(int n, int m) {
	assert(n % 3 == 0 || m % 3 == 0);

	if (m % 3 == 0) {
		vector<vector<int>> res(n, vector<int>(m, 0));

		if (m == 3) {
			vector<int> p = {0, 1, 2};
			for (int i = 0; i < n; i++) {
				res[i] = p;
				swap(p[i % 2], p[i % 2 + 1]);
			}
			return res;
		}

		if (n <= 2) {
			// m <= 6
			if (m <= 6) {
				// 001122
				// 001122
				for (int i = 0; i < n; i++) {
					for (int j = 0; j < m; j++) {
						res[i][j] = j / (m / 3);
					}
				}
				return res;
			} else {
				return {};
			}
		}
		if (n == 3) {
			return flip(solve(m, n));
		}

		int cnt0 = (n * m / 3) - (m / 3 * n + 1) / 2;

		// n >= 4, m >= 6, m % 3 == 0
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {

				if (j < m / 3) {
					// 01010
					// 10101
					res[i][j] = (i + j) % 2;
				} else {
					if ((i + j) % 2 == 0) {
						res[i][j] = 2;
					} else {
						res[i][j] = cnt0 > 0 ? 0 : 1;
						cnt0 --;
					}
				}
			}
		}

		return res;
	}

	return flip(solve(m, n));
}

void Hollwo_Pelw(){
	int n, m;
	cin >> n >> m;

	auto res = solve(n, m);

	if (res.empty()) {
		cout << "No\n";
	} else {
		cout << "Yes\n";
		for (auto &v : res) {
			for (int &x : v) {
				cout << x;
			}
			cout << '\n';
		}
	}
}
