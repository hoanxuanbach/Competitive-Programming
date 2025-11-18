#include <bits/stdc++.h>

using namespace std;
const int R = 10;
const int C = 11;

int dp[R][C][R][C][2];
int vis[R][C][R][C][2];
const int dx[] = {2, 2, -2, -2, 1, -1, 1, -1};
const int dy[] = {1, -1, 1, -1, 2, 2, -2, -2};
const int bx[] = {1, 1, -1, -1, 0, 0, 0, 0};
const int by[] = {0, 0, 0, 0, 1, 1, -1, -1};

struct State {
	int x1, y1, x2, y2, turn;
};

bool inside(int x, int y) {
	return 1 <= x && x < R && 1 <= y && y < C;
}

void init() {
	memset(dp, -1, sizeof(dp));
	memset(vis, 0, sizeof(vis));
}

int calc(int x1, int y1, int x2, int y2, int turn) {
	int &res = dp[x1][y1][x2][y2][turn];
	if (res != -1) return res;
	vis[x1][y1][x2][y2][turn] = 1;
	vector<State> states;

	if (turn == 0) {
		for (int i = 0; i < 8; ++i) {
			int nx = x1 + dx[i];
			int ny = y1 + dy[i];
			if (!inside(nx, ny)) continue;
			int blocked_x = x1 + bx[i];
			int blocked_y = y1 + by[i];
			if (blocked_x == x2 && blocked_y == y2) continue;
			
			if (nx == x2 && ny == y2) {
				vis[x1][y1][x2][y2][turn] = 2;
				return res = 1;
			}

			states.push_back({nx, ny, x2, y2, 1 ^ turn});
		}
	} else {
		for (int i = 1; i < R; ++i) {
			for (int j = 1; j < C; ++j) {
				if (i != x2 && j != y2) continue;
				if (i == x2 && j == y2) continue;

				if (i == x1 && j == y1) {
					vis[x1][y1][x2][y2][turn] = 2;
					return res = 1;
				}

				states.push_back({x1, y1, i, j, 1 ^ turn});
			}
		}
	}

	for (State state : states) {
		int nx1 = state.x1;
		int ny1 = state.y1;
		int nx2 = state.x2;
		int ny2 = state.y2;
		int nturn = state.turn;
		if (vis[nx1][ny1][nx2][ny2][nturn] == 1) {
			res = 2;
			continue;
		} else {
			int tmp = calc(nx1, ny1, nx2, ny2, nturn);
			if (tmp == 2) {
				res = 2;
			} else if (res == -1 || res == (1 ^ tmp)) {
				res = (1 ^ tmp);
			} else {
				res = 2;
			}
		}
	}

	vis[x1][y1][x2][y2][turn] = 2;
	return res;
}

void solve() {
	int x1, y1, x2, y2;
	cin >> x1 >> y1 >> x2 >> y2;
	if (calc(x1, y1, x2, y2, 0) == 0) {
		cout << "YES\n";
	} else {
		cout << "NO\n";
	}
}

int main() {
#ifdef LOCAL
	freopen("main.inp", "r", stdin);
	freopen("main.out", "w", stdout);
#endif
	ios::sync_with_stdio(0);
	cin.tie(0);
	init();
	int test = 1;
	cin >> test;
	while (test--)
		solve();
	return 0;
}