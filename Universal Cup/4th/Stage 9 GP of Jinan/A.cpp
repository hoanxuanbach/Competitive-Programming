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

#define ll unsigned long long

void Hollwo_Pelw(){
	ll a, b;

	cin >> a >> b;

	if (b == 1) {
		cout << 0 << '\n';
		return ;
	}

	if (a == 0) {
		if (b == 0) cout << 1 << '\n';
		else {
			cout << "broken message\n";
		}
		return ;
	}

	if (a == 1) {
		// b != 1
		cout << "broken message\n";
		return ;
	}

	if (a % 2 != b % 2) {
		cout << "broken message\n";
		return ;
	}

	if (a % 2 == 0) {
		ll A = 1;
		for (int i = 0; i <= 64; i++) {
			if (A == b) {
				cout << i << '\n';
				return ;
			}
			A *= a;
		}

		cout << "broken message\n";
		return ;
	}


	ll val = 1, res = 0;

	for (ll pa = a, k = 0; k < 64; k++, pa = pa * pa) {

		int pos = __builtin_ctzll(pa - 1);

		if ((val >> pos & 1) == (b >> pos & 1)) {
			continue ;
		}

		val *= pa;
		res |= 1ll << k;

	}

	// verify

	if (val == b) {
		cout << res << '\n';
	} else {
		cout << "broken message\n";
	}

}