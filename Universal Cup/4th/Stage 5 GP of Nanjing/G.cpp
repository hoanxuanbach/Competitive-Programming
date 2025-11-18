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

#define int long long

const int N = 2e5 + 5;

int n, v[N], l[N], sumv[N], suml[N];

void Hollwo_Pelw(){
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> v[i];
	}
	for (int i = 1; i <= n; i++) {
		cin >> l[i];
	}

	sort(v + 1, v + n + 1);
	reverse(v + 1, v + n + 1);
	sort(l + 1, l + n + 1);


	for (int i = 1; i <= n; i++) {
		sumv[i] = sumv[i - 1] + v[i];
		suml[i] = suml[i - 1] + l[i];
	}

	
	int q; cin >> q;
	for (int t; q --; ) {
		cin >> t;

		int tl = 1, tr = n, k = 0;

		while (tl <= tr) {
			int mid = (tl + tr) >> 1;

			if (l[mid] * t <= v[mid]) {
				k = mid;
				tl = mid + 1;
			} else {
				tr = mid - 1;
			}
		}

		cout << sumv[k] - suml[k] * t << ' ';
	}
	cout << '\n';
}
