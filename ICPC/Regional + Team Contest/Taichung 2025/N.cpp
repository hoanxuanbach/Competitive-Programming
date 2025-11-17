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

int n, k, b;

void Hollwo_Pelw(){
	cin >> n >> k >> b;
	if (k % 2 == 1) {
		return cout << "No\n", (void) 0;
	}
	// cout << n << ' ' << k << ' ' << b << " -> ";
	if (k == 0) {
		if (b != 0 || n == 2) {
			return cout << "No\n", (void) 0;
		}
		cout << "Yes\n";
		if (n == 1) {
			cout << "0\n";
			return ;
		}
		cout << n << '\n';
		for (int i = 1; i <= n; i++) {
			cout << i << ' ' << (i == n ? 1 : i + 1) << '\n';
		}
		return ;
	}

	int ex_x = n - b;

	if (ex_x == 2) {
		return cout << "No\n", (void) 0;
	}

	vector<vector<int>> sun(ex_x);

	int p = 1, leaf = -1;

	for (int i = 0; i < ex_x; i++) {
		sun[i].push_back(p ++);
	}

	for (int i = 0; i < ex_x; i++) {
		if (k >= 2 && b >= 1) {
			k -= 2;
			b -= 1;
			leaf = p;
			sun[i].push_back(p ++);
		}
	}

	vector<pair<int, int>> edges;

	for (int i = 0; i < ex_x; i++) {
		if (sun[i].size() > 1) {
			edges.push_back({sun[i][0], sun[i][1]});
		}
	}

	while (k >= 2 && b >= 2) {
		edges.push_back({1, p ++});
		edges.push_back({1, p ++});
		k -= 2;
		b -= 2;
	}

	while (b > 0) {
		edges.push_back({leaf, p ++});
		leaf = p - 1;
		b --;
	}

	assert(p == n + 1);

	if (sun.size() > 1) {
		vector<int> id1, id2;
		for (int i = 0; i < (int) sun.size(); i++) {
			if (sun[i].size() > 1) {
				id1.push_back(sun[i][0]);
			} else {
				id2.push_back(sun[i][0]);
			}
		}

		vector<int> cycle;
		// ordered cycle
		int half1 = id1.size() == 0 ? 0 : 1, half2 = id2.size() / 2;
		for (int i = 0; i < half2; i ++) {
			cycle.push_back(id2[i]);
		}
		for (int i = 0; i < half1; i ++) {
			cycle.push_back(id1[i]);
		}
		for (int i = half2; i < (int) id2.size(); i ++) {
			cycle.push_back(id2[i]);
		}
		for (int i = half1; i < (int) id1.size(); i ++) {
			cycle.push_back(id1[i]);
		}

		if (cycle.size() <= 3) {
			
		} else {
			// can
			// cout << id1.size() << ' ' << id2.size() << '\n';
			for (int i = 0; i < half2; i++) {
				if (k > 0) {
					k -= 2;
					edges.push_back({id2[i], id2[i + half2]});

				}
			}
		}

		for (int i = 0; i < (int) cycle.size(); i++) {
			edges.push_back({cycle[i], cycle[(i + 1) % cycle.size()]});
		}
	}

	if (k > 0 || p > n + 1) {
		cout << "No\n";
		// assert(false);
		return ;
	} else {
		cout << "Yes\n";
		cout << edges.size() << '\n';
		for (auto [x, y] : edges) {
			cout << x << ' ' << y << '\n';
		}
	}
}
