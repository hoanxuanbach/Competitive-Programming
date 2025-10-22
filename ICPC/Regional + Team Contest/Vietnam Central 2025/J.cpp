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

const int N = 105;
const int dx[] = {1, 0, -1, 0};
const int dy[] = {0, 1, 0, -1};

int n, m, sx, sy, vis[N][N][5];

inline bool inboard(int x, int y) {
	return 0 <= x && x < n && 0 <= y && y < m;
}

string s[100];

void Hollwo_Pelw(){
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		cin >> s[i];

		for (int j = 0; j < m; j++) {
			if (s[i][j] == 'S') {
				sx = i, sy = j;
			}
		}
	}

	memset(vis, -1, sizeof vis);

	vis[sx][sy][3] = 0;

	queue<tuple<int, int, int>> q;

	q.emplace(sx, sy, 3);

	while (!q.empty()) {
		auto [x, y, h] = q.front(); q.pop();

		if (s[x][y] == 'D') {
			cout << vis[x][y][h] << '\n';
			return ;
		}

		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i], ny = y + dy[i];

			if (inboard(nx, ny)) {

				int nh = h - (s[nx][ny] == '+' ? 1 : 0);

				if (nh > 0 && vis[nx][ny][nh] == -1) {
					q.emplace(nx, ny, nh);
					vis[nx][ny][nh] = vis[x][y][h] + 1;
				}
			}
		}
	}

	cout << -1 << '\n';
}
