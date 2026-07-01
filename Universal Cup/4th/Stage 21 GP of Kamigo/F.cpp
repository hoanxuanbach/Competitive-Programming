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

const int N = 5e5 + 5;

int n, a[N], b[N], g[N];
vector<pair<int, int>> res; 

// A -> increase
// B -> decrease

void Hollwo_Pelw(){
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	for (int i = 1; i <= n; i++) {
		cin >> b[i];
	}

	if (a[1] != 1 || b[1] != 1) {
		cout << -1 << '\n';
		return ;
	}

	int cura = 1, curb = 1, curgroup = 1;

	g[1] = 1;
	res.push_back({1, 1});

	for (int i = 2; i <= n; i++) {
		if (a[i] != cura && a[i] != cura + 1 && b[i] != curb && b[i] != curb + 1) {
			cout << -1 << '\n';
			return ;
		}

		if (a[i] > cura && b[i] > curb) {
			cout << -1 << '\n';
			return ;
		}

		if (a[i] > cura) {
			cura ++;
			res.push_back({cura, g[cura] = 1});
		}
		else if (b[i] > curb) {
			curb ++;
			curgroup = 1;
			g[curgroup] ++;
			res.push_back({curgroup, g[curgroup]});
		}
		else {
			if (g[curgroup] == curb) {
				curgroup ++;
			}
			if (curgroup > cura) {
				cout << -1 << '\n';
				return ;
			}
			g[curgroup] ++;
			res.push_back({curgroup, g[curgroup]});
		}

		// cout << curgroup << ' ' << g[curgroup] << '\n';
	}

	for (int i = 1; i <= n; i++) {
		g[i] += g[i - 1];
	}

	for (auto [x, v] : res) {
		cout << g[x] - v + 1 << ' ';
	}
}