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

/*
6:
1  2 4  5 7  8
9 10 3 11 6 12

7:
 1 3  4 6  7 9 10
11 2 12 5 13 8 14
*/

const int N = 1e5 + 5;

int n, a[N], b[N];

void Hollwo_Pelw(){
	cin >> n;
	int p = 2 * n;

	for (int i = n; i >= 1; i -= 2) {
		b[i] = p --;
	}

	if (n % 2 == 0) {
		b[1] = p --;
	}

	for (int i = n; i >= 3; i -= 2) {
		a[i] = p --;
		a[i - 1] = p --;
		b[i - 1] = p --;
	}

	if (n % 2 == 0) {
		a[2] = p --;
		a[1] = p --;
	} else {
		a[1] = p --;
	}

	for (int i = 1; i <= n; i++) {
		cout << a[i] << " \n"[i == n];
	}

	for (int i = 1; i <= n; i++) {
		cout << b[i] << " \n"[i == n];
	}
}