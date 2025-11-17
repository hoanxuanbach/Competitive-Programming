#include <bits/stdc++.h>
#define pii pair<int, int>
#define fi first
#define se second

using namespace std;

void solve() {
	string s;
	cin >> s;
	int x, y;
	cin >> x >> y;
	string sx, sy;
	int cur = 0;
	do {
		++cur;
		if (cur == x) {
			sx = s;
		}
		if (cur == y) {
			sy = s;
		}
	} while (next_permutation(s.begin(), s.end()));
	int cnta = 0, cntb = 0;
	for (int i = 0; i < sx.size(); ++i) {
		if (sx[i] == sy[i]) {
			++cnta;
		}
	}
	cntb = (int)sx.length() - cnta;

	cout << cnta << "A" << cntb << "B" << endl;
}

int main() {
#ifdef LOCAL
	freopen("main.inp", "r", stdin);
	freopen("main.out", "w", stdout);
#endif
	ios::sync_with_stdio(0);
	cin.tie(0);
	int test = 1;
	cin >> test;
	while (test--)
		solve();
	return 0;
}