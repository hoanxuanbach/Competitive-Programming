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

const int N = 10;

int n, x[N], y[N], costA[1 << 8], costB[1 << 8];

inline int dist(int i, int j) {
	return abs(x[i] - x[j]) + abs(y[i] - y[j]);
}

void Hollwo_Pelw(){
	cin >> n;
	for (int i = 0; i < n + 2; i++) {
		cin >> x[i] >> y[i];
	}

	int A = n, B = n + 1;

	vector<int> vec(n);
	iota(vec.begin(), vec.end(), 0);

	fill(costA, costA + (1 << n), 1e9);
	fill(costB, costB + (1 << n), 1e9);

	do {
		{
			int last = A, mask = 0, c = 0, val = 0;
			for (int i : vec) {
				mask |= 1 << i;
				val += dist(last, i) * c;
				++ c;
				last = i;

				costA[mask] = min(costA[mask], c * dist(i, A) + val);
			}
		}

		{
			int last = B, mask = 0, c = 0, val = 0;
			for (int i : vec) {
				mask |= 1 << i;
				val += dist(last, i) * c;
				++ c;
				last = i;

				costB[mask] = min(costB[mask], c * dist(i, B) + val);
			}
		}

	} while(next_permutation(vec.begin(), vec.end()));

	costA[0] = costB[0] = 0;

	int res = 1e9;

	for (int mask = 0; mask < 1 << n; mask++) {
		res = min(res, costA[mask] + costB[((1 << n) - 1) ^ mask]);
	}

	cout << res << '\n';
}
