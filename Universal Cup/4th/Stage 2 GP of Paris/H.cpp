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

const int N = 1e6 + 5;
const int inf = 1e18;

int n, k, d, a[N], h[N];

bool check(int maxd) {
	maxd = min(maxd, n);

	// cout << "CHECK " << maxd << '\n';
    // x*k - h[rx] <= (y-1)*k - h[ly-1] 

    int mn = inf;
	for (int i = 1; i <= n; i++) {
		int l = max(1ll, i - maxd);
		int r = min(n  , i + maxd);

        mn=min(mn,(i-1)*k - h[l-1]);
        if(i*k - h[r] > mn) return 0;
	}
	return 1;
}

void Hollwo_Pelw(){
	cin >> n >> d;

	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		h[i] = a[i] + h[i - 1];
	}
	k = h[n] / n;

	int l = 0, r = n;
	while (l < r) {
		int mid = (l + r) / 2;
		if (check(mid * d)) {
			r = mid;
		} else {
			l = mid + 1;
		}
	}
	cout << l << '\n';
}

/*

0 1 0 3

*/