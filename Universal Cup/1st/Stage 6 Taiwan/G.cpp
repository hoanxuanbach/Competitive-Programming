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

void Hollwo_Pelw(){
	string s;
	cin >> s;

	int n = s.size();

	int len = 0, pos = 0;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < i; j++) {

			int clen = 0;
			while (i + clen < n && j + clen < i && s[i + clen] == s[j + clen]) {
				clen ++;
			}

			if (clen > len) {
				len = clen, pos = j;
			} else if (clen == len && pos > j) {
				pos = j;
			}

		}
	}

	cout << s.substr(pos, len) << '\n';
}