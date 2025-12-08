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
	// cin >> testcases;
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

int n, l;

void Hollwo_Pelw(){
	cin >> n >> l;
	map<int, int> mp;

	for (int i = 0; i < n; i++) {
		int r, c;
		cin >> r >> c;
		r --;

		mp[c] |= 1 << r;
	}

	if (n % 2 == 1) {
		cout << "no\n";
		return ;
	}

	int last_row = -1, last_col = -1;

	int res = 0;

	for (auto [r, mask_c] : mp) {
		// cout << "PROCESS \n";
		// cout << r << ' ' << mask_c << '\n';
		if (mask_c == 3) {
			if (last_row == -1) {
				continue;
			}
			res ++;
			int diff = (last_row ^ r) & 1;

			last_row = r;
			if (!diff) {
				last_col = 3 ^ last_col;
			}

		} else {
			if (last_row == -1) {
				last_row = r;
				last_col = mask_c;
			} else {

				int diff = (last_row ^ r) & 1;

				// cout << "??? " << r << " " << last_row << "\n";
				// cout << diff << '\n';

				if (diff) {
					if (last_col != mask_c) {
						res ++;
					}
				} else {
					if (last_col == mask_c) {
						res ++;

					}
				}

				last_row = -1;
				last_col = -1;
			}
		}

		// cout << last_row << ' ' << last_col << '\n';
	}

	cout << res << '\n';
}
