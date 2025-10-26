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

int n, x, y;

void Hollwo_Pelw(){
	cin >> n >> x >> y;
	int lx = 1, ly = 1, rx = n, ry = n, len = n - 1;

	vector<array<int, 4>> res;

	while (lx < x && ly < y) {
		res.push_back({lx, ly, +len, +len});
		len --, lx ++, ly ++;
	}

	while (rx > x && ry > y) {
		res.push_back({rx, ry, -len, -len});
		len --, rx --, ry --;
	}

	while (lx < x && ry > y) {
		res.push_back({lx, ry, +len, -len});
		len --, lx ++, ry --;
	}

	while (rx > x && ly < y) {
		res.push_back({rx, ly, -len, +len});
		len --, rx --, ly ++;
	}

	assert(len == 0);

	cout << "Yes\n";
	cout << res.size() << "\n";
	for (auto a : res) {
		cout << a[0] << ' ' << a[1] << ' ' << a[2] << ' ' << a[3] << '\n';
	}
}