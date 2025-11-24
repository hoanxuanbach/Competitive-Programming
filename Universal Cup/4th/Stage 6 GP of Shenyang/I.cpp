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

int cnt[500], solve[500][20];

void Hollwo_Pelw(){
	int n;
	cin >> n;
	for (int a, b, c; n --; ) {
		cin >> a >> b >> c;
		if (solve[a][b]) {
			cout << 0 << '\n';
			continue;
		}
		
		solve[a][b] = 1;

		if (c < 240) {
			cout << b << '\n';
			cnt[a] ++;
		} else if (cnt[a] < 3) {
			cout << b << '\n';
			cnt[a] ++;
		} else {
			cout << 0 << '\n';
		}
	}
}