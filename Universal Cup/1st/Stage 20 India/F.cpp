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

const int N = 101;

int n, a[N], b[N];

void Hollwo_Pelw(){
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> b[i];
	}
	if (b[1] != 1) {
		cout << "NO\n";
		return ;
	}
	for (int i = 2; i <= n; i++) {
		if (b[i] != b[i - 1] + 1 && b[i] != b[i - 1]) {
			cout << "NO\n";
			return ;
		}
	}

	cout << "YES\n";
	for (int i = 1, j = 1, c = 1; i <= n; i = j) {
		while (j <= n && b[j] == b[i]) {
			j ++;
		}
		for (int k = j; k -- > i; ) {
			a[k] = c ++;
		}
	}
	for (int i = 1; i <= n; i++) {
		cout << a[i] << " \n"[i == n];
	}
}