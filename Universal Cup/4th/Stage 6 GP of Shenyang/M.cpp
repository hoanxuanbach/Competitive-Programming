#include <bits/stdc++.h>

using namespace std;
void solve();

signed main() {
#ifdef LOCAL
	freopen("main.inp", "r", stdin);
	freopen("main.out", "w", stdout);
#endif
	cin.tie(0), cout.tie(0)->sync_with_stdio(0);
	int testcases = 1;
	// cin >> testcases;
	for (int test = 1; test <= testcases; test++) {
		solve();
	}
}

const int N = 9;

double a[N], b[N];
double p[N][N];
double q[N], swin[N], swin2[N], champ[N];

void solve() {
	for (int i = 1; i <= 8; ++i) {
		cin >> a[i] >> b[i];
	}

	vector<int> teams(8);
	for (int i = 0; i < 8; ++i)
		teams[i] = i + 1;

	double ans = 0.0;

	do {
		for (int i = 0; i < 8; ++i) {
			champ[i] = swin[i] = swin2[i] = 0;
			for (int j = 0; j < 8; ++j) {
				p[i][j] = 0;
			}
		}
		for (int i = 0; i < 8; ++i) {
			for (int j = 0; j < 8; ++j) {
				if (i == j) {
					continue;
				}
				int ti = teams[i];
				int tj = teams[j];
				double si, sj;
				if (i < j) {
					si = a[ti];
					sj = b[tj];
				}
				else {
					si = b[ti];
					sj = a[tj];
				}
				p[i][j] = si / (si + sj);
			}
		}

		q[0] = p[0][1];
		q[1] = p[1][0];
		q[2] = p[2][3];
		q[3] = p[3][2];
		q[4] = p[4][5];
		q[5] = p[5][4];
		q[6] = p[6][7];
		q[7] = p[7][6];

		for (int i = 0; i < 4; ++i) {
			if (i <= 1) {
				for (int j = 2; j <= 3; ++j) {
					swin[i] += q[i] * q[j] * p[i][j];
				}
			}
			else {
				for (int j = 0; j <= 1; ++j) {
					swin[i] += q[i] * q[j] * p[i][j];
				}
			}
		}

		for (int i = 4; i < 8; ++i) {
			if (i <= 5) {
				for (int j = 6; j <= 7; ++j) {
					swin2[i] += q[i] * q[j] * p[i][j];
				}
			}
			else {
				for (int j = 4; j <= 5; ++j) {
					swin2[i] += q[i] * q[j] * p[i][j];
				}
			}
		}

		for (int i = 0; i < 4; ++i) {
			for (int j = 4; j < 8; ++j) {
				double meet = swin[i] * swin2[j];
				champ[i] += meet * p[i][j];
				champ[j] += meet * p[j][i];
			}
		}

		int pos1 = -1;
		for (int i = 0; i < 8; ++i) {
			if (teams[i] == 1) {
				pos1 = i;
				break;
			}
		}

		if (pos1 != -1) {
			ans = max(ans, champ[pos1]);
		}

	} while (next_permutation(teams.begin(), teams.end()));

	cout << fixed << setprecision(10) << ans << '\n';
}