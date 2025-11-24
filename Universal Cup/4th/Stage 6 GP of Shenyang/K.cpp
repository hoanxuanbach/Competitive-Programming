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
const int N = 1e5 + 5;

int n, s, px[N], py[N], qx[N], qy[N];

void Hollwo_Pelw(){
	cin >> n >> s;
	int sumx = 0, sumy = 0;
	for (int i = 1; i <= n; i++) {
		cin >> px[i] >> py[i];
		cin >> qx[i] >> qy[i];

		sumx += qx[i] - px[i];
		sumy += qy[i] - py[i];
	}

	sumx += 2 * px[s];
	sumy += 2 * py[s];
	
	for (int i = 1; i <= n; i++) {
		if (sumx == qx[i] * 2 && sumy == qy[i] * 2) {
			cout << i << '\n';
			return ;
		}
	}
}