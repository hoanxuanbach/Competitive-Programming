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

const int N = 1005;

int n, k, adj[N][N];

void fill(int u, int v, int c) {
	adj[u][v] = adj[v][u] = (c - 1) % k + 1;
}

void Hollwo_Pelw(){
	cin >> n >> k;

	if (k > n / 2) {
		cout << "NO\n";
		return ;
	}

	for (int i = 1; i <= n / 2; i++) {
		int lu = i * 2 - 1, ru = i * 2;
		
		fill(lu, ru, i);

		for (int j = i + 1; j <= n / 2; j++) {

			int lv = j * 2 - 1, rv = j * 2;

			fill(lu, lv, i);
			fill(ru, rv, i);

			fill(lu, rv, j);
			fill(ru, lv, j);
		}
	}


	if (n % 2 == 1) {
		for (int i = 1; i <= n - 1; i++) {
			fill(i, n, i);
		}
	}

	cout << "YES\n";
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j < i; j++) {
			cout << adj[i][j] << " \n"[j == i - 1];
		}
	}
}