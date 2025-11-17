#include <bits/stdc++.h>
#define pii pair<int, int>
#define fi first
#define se second

using namespace std;
const int N = 1e5 + 7;
const int MAX = 1e6 + 7;

const int dxs[] = {0, 0, 1, -1, -1, 1, 1, -1};
const int dys[] = {1, -1, 0, 0, -1, 1, -1, 1};

int n, m;
vector<vector<char>> ch;
int q;
int a[N];
int res[N];
int idx[MAX + 5];

bool inside(int i, int j) {
	return 1 <= i && i <= n && 1 <= j && j <= m;
}

void calc(int x, int y, int dx, int dy) {
	int sum = 0;
	int l1 = 0, l2 = 0, ls = 0;
	int sx = x, sy = y;
	int last = 0;
	while(inside(x, y)) {
		if ('1' <= ch[x][y] && ch[x][y] <= '9') {
			int nl2 = l2 * 10 + ch[x][y] - '0';
			if (nl2 >= MAX) return;
			if (ls == 0) {
				sum = sum - l2 + nl2;
			} else {
				sum = sum - l1 * l2;
				sum = sum + l1 * nl2;
			}
			if (sum >= MAX) return;
			l2 = nl2;
			if (x == sx && y == sy) {
				if (dx == 0 && dy == 1) res[idx[sum]]++;
			} else res[idx[sum]]++;
			last = 1;
		} else {
			if (last == 0) {
				return;
			}
			if (ch[x][y] == '+') {
				l1 = sum;
				l2 = 0;
				ls = 0;
			} else {
				if (ls == 0) {
					sum -= l2;
					l1 = l2;
					l2 = 0;
				} else {
					sum -= l1 * l2;
					l1 *= l2;
					l2 = 0;
				}
				ls = 1;
			}
			last = 0;
		}
		x += dx;
		y += dy;
	}
}

void solve() {
	cin >> n >> m >> q;
	ch.assign(n + 1, vector<char>(m + 1));
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			cin >> ch[i][j];
		}
	}

	for (int i = 1; i <= q; ++i) {
		cin >> a[i];
		idx[a[i]] = i;
	}

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			for (int k = 0; k < 8; ++k) {
				calc(i, j, dxs[k], dys[k]);
			}
		}
	}

	for (int i = 1; i <= q; ++i) {
		cout << res[i] << "\n";
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