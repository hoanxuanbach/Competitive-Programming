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

const int dx[] = {0, 1, 0, -1};
const int dy[] = {1, 0, -1, 0};

int n, k;

vector<string> res;

bool check(vector<string> a) {
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cnt += i + 1 < n && a[i][j] != a[i + 1][j];
			cnt += j + 1 < n && a[i][j] != a[i][j + 1];
		}
	}
	return cnt == k;
}

void print(const vector<string> &a) {
	cout << "Possible\n";
	for (string s : a) {
		cout << s << '\n';
	}
}

void Hollwo_Pelw(){
	cin >> n >> k;
	if (k == 1 || k == 2 * n * (n - 1) - 1) {
		cout << "Impossible\n";
		return ;
	}

	res = vector<string>(n, string(n, 'R'));

	if (n <= 3) {
		for (int mask = 0; mask < 1 << (n * n); mask++) {
			auto cur = vector<string>(n, string(n, 'R'));

			for (int i = 0; i < n * n; i++)
				if (mask >> i & 1) cur[i / n][i % n] = 'B';

			if (check(cur)) return print(cur);
		}
	} else {
		vector<pair<int, int>> vec[5];
		for (int i = 0; i < n; i++) {
			for (int j = i & 1; j < n; j += 2) {
				int cnt = 0;
				for (int d = 0; d < 4; d++) {

					int x = i + dx[d], y = j + dy[d];

					if (0 <= x && x < n && 0 <= y && y < n) {
						cnt ++;
					}

				}

				vec[cnt].push_back({i, j});
			}
		}

		vector<int> c(5);

		for (c[2] = 0; c[2] <= vec[2].size(); c[2] ++) {
			for (c[3] = 0; c[3] <= vec[3].size(); c[3] ++) {

				int left = k - c[2] * 2 - c[3] * 3;

				if (left < 0 || left % 4 != 0) continue ;

				c[4] = left / 4;

				if (c[4] > vec[4].size()) continue ;


				for (int i = 2; i <= 4; i++) {

					for (auto [x, y] : vec[i]) {
						if (!c[i] --) break ; 
						res[x][y] = 'B';
					}

				}

				return print(res);
			}
		}
	}
}