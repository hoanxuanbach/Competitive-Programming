#include <bits/stdc++.h>

using namespace std;
const int N = 2e3 + 7;
const int M = 5e3 + 7;
const double INF = 1e18;

int n, m;
int a[N], b[N], c[N], d[N], e[N], p[N];
double dp[N][M][2][2];

void solve() {
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i] >> b[i] >> c[i] >> d[i] >> e[i] >> p[i];
	}

	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j <= m; ++j) {
			for (int x = 0; x <= 1; ++x) {
				for (int y = 0; y <= 1; ++y) {
					dp[i][j][x][y] = -INF;
				}
			}
		}
	}
	for (int i = 0; i <= m; ++i) {
		for (int x = 0; x <= 1; ++x) {
			for (int y = 0; y <= 1; ++y) {
				dp[n+1][i][x][y] = 0;
			}
		}
	}

	for (int i = n; i >= 1; --i) {
		double pi = 1.0 * p[i] / 100;
		for (int j = 0; j <= m; ++j) {
			for (int x = 0; x <= 1; ++x) {
				for (int y = 0; y <= 1; ++y) {
					// cafe
					if (j + b[i] <= m) {
						int nj = j + b[i];
						dp[i][j][x][y] = max(dp[i][j][x][y], (dp[i+1][nj][max(x, 1)][y] + 1.0 * a[i]) * pi + (dp[i+1][nj][x][max(y, 1)] + 1.0 * a[i]) * (1 - pi));
					}

					// restaurant
					if (x == 0 || y == 0) {
						int nj = j + d[i];
						if (nj <= m) {
							dp[i][j][x][y] = max(dp[i][j][x][y], (dp[i+1][nj][max(x, 1)][y] + c[i]) * pi + (dp[i+1][nj][x][max(y, 1)] + c[i]) * (1 - pi));
						}
					} else {
						int nj = j + d[i] + e[i];
						if (nj <= m) {
							dp[i][j][x][y] = max(dp[i][j][x][y], dp[i + 1][nj][0][0] + 1.0 * c[i]);
						}
					}
				}
			}
		}
	}

	double res = -INF;
	for (int i = 0; i <= m; ++i) {
		res = max(res, dp[1][i][0][0]);
	}
	if (res < 0) {
		cout << "-1\n";
	} else {
		cout << fixed << setprecision(10) << res << '\n';
	}
}

int main() {
#ifdef LOCAL
	freopen("main.inp", "r", stdin);
	freopen("main.out", "w", stdout);
#endif
	ios::sync_with_stdio(0);
	cin.tie(0);
	int test = 1;
	// cin >> test;
	while (test--)
		solve();
	return 0;
}