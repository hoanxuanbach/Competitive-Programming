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

const int N = 1e5 + 5;

int n, res[N], a[N], v[N];

void Hollwo_Pelw(){
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> v[i];
	}

	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}

	for (int i = n; i >= 1; i--) {
		int x = i, is_max = 0, is_min = 0;

		vector<int> trace;

		while (x && v[i] != a[x]) {
			if (a[x] < v[i]) {
				is_max = 1;
			} else {
				is_min = 1;
			}
			trace.push_back(x);
			x >>= 1;
		}

		if (x > 1) {
			if (a[x] < a[x >> 1]) {
				is_max = 1;
			}
			if (a[x] > a[x >> 1]) {
				is_min = 1;
			}
		}
		if ((is_max && is_min) || !x) {
			cout << "Impossible\n";
			return ;
		}

		res[i] = is_max ? 1 : 0;

		trace.push_back(x);
		while ((int)trace.size() > 1) {
			int x = trace[trace.size() - 1];
			int y = trace[trace.size() - 2];
			swap(a[x], a[y]);
			trace.pop_back();
		}
	}

	for (int i = 1; i <= n; i++) {
		cout << res[i];
	}
	cout << '\n';
}

/*
1
2 3
4 5 6 7



*/