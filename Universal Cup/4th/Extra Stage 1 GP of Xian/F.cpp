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

#define int long long

const int N = 5e5 + 5, inf = 1e18;

int n, t[N], a[N], dir[N], res[N], cur[N];

vector<int> update[N];
// time = dist / vc, vc, id
set<tuple<int, int, int>> st;

void Hollwo_Pelw(){
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> t[i];
		update[t[i]].push_back(i);
	}

	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}

	for (int i = 1; i <= n; i++) {
		if (a[i] == a[t[i]]) {
			dir[i] = 0;
			res[i] = 0;
		} else if (a[i] < a[t[i]]) {
			dir[i] = 1;
			res[i] = -1;
		} else {
			dir[i] = -1;
			res[i] = -1;
		}
	}

	for (int i = 1; i <= n; i++) {
		int vc = abs(dir[i] - dir[t[i]]), dis = abs(a[i] - a[t[i]]);

		cur[i] = vc;
		st.insert({(vc == 0 ? inf : dis * 2 / vc), vc, i});
	}

	while (!st.empty()) {
		auto [d, vc, id] = *st.begin();
		st.erase(st.begin());

		if (res[id] != -1 || vc != abs(dir[id] - dir[t[id]])) {
			continue; // out date
		}

		// meet after d(s)
		res[id] = d;
		dir[id] = 0;

		// cout << id << " " << d << '\n';

		for (auto v : update[id]) {
			int fdis = 2 * abs(a[v] - a[id]) - res[id] * cur[v];
			cur[v] = abs(dir[v] - dir[id]);

			if (cur[v]) st.insert({fdis / cur[v] + res[id], cur[v], v});
		}
	}

	for (int i = 1; i <= n; i++) {
		cout << res[i] << " \n"[i == n];
	}
}