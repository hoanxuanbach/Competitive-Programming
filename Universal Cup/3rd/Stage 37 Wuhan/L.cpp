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

const int N = 3005;

int n, a[N];

void Hollwo_Pelw(){
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	sort(a + 1, a + n + 1);

	int res = 1;

	for (int i = 1; i <= n; i++) {
		map<int, int> pos;

		// cout << i << " -> " << a[i] << '\n';

		for (int j = i; j <= n; j++) {
			pos[a[j] - a[i]] = j - i;
		}

		for (int j = i; j >= 1; j--) {

			int val = a[i] - a[j];
			if (pos.count(val)) {
				int a = pos[val], b = i - j;
				int cur = min(a, b) * 2 + 1;
				
				if (b < a)  cur ++;

				res = max(res, cur);

				// cout << "val = " << val << '\n';
				// cout << "cur = " << cur << ": " << a << ' ' << b << '\n';
			}

		}
	}

	cout << res << '\n';
}