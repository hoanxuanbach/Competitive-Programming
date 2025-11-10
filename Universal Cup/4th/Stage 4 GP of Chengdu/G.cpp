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

void Hollwo_Pelw(){
	int n, k, m;
	cin >> n >> k >> m;

	int kcnt = 1;
	int cnt = n / k - 1;
	int oth = n - cnt - 1;

	// cout << kcnt << ' ' << cnt << ' ' << oth << '\n';

	if (oth < m) {
		kcnt += oth;
		m -= oth;
		oth = 0;
	} else {
		kcnt += m;
		oth -= m;
		m = 0;
	}

	if (cnt < m) {
		kcnt += cnt;
		m -= cnt;
		cnt = 0;
	} else {
		kcnt += m;
		cnt -= m;
		m = 0;
	}

	// cout << kcnt << ' ' << cnt << ' ' << oth << '\n';

	cout << kcnt + cnt / 2 << '\n';
}