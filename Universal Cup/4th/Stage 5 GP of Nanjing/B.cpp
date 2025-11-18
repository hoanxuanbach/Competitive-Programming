#include <bits/stdc++.h>
#define pii pair<int, int>
#define fi first
#define se second

using namespace std;
const int N = 2e5 + 7;
const double INF = 1e9;
const double EPS = 1e-9;

int n;
int a[N], b[N], c[N];
int na[N], nb[N];

bool cmp(const pii &a, const pii &b) {
	if (1LL * a.se * b.se < 0) {
		return 1LL * a.fi * b.se > 1LL * b.fi * a.se;
	}
	return 1LL * a.fi * b.se < 1LL * b.fi * a.se;
}

int calc(int sign_a, int sign_b) {
	for (int i = 1; i <= n; ++i) {
		na[i] = a[i] * sign_a;
		nb[i] = b[i] * sign_b;
	}

	vector<pii> gt;
	vector<pii> lt;
	int cnt = 0;
	for (int i = 1; i <= n; ++i) {
		if (na[i] == 0) {
			if (nb[i] < 0) {
				++cnt;
			}
			continue;
		}
		if (nb[i] == 0) {
			if (na[i] < 0) {
				++cnt;
			}
			continue;
		}

		if (na[i] > 0) {
			lt.push_back(make_pair(-1 * nb[i], na[i]));
		} else {
			gt.push_back(make_pair(-1 * nb[i], na[i]));
		}
	}
	lt.push_back(make_pair(INF, 1));

	sort(lt.begin(), lt.end(), cmp);
	sort(gt.begin(), gt.end(), cmp);

	int ans = cnt, cur = 0;
	for (int i = 0; i < (int)lt.size(); ++i) {
		int xa = lt[i].fi, xb = lt[i].se;
		if (1LL * xa * xb <= 0) {
			continue;
		}
		while (cur < (int)gt.size() && cmp(gt[cur], lt[i])) {
			++cur;
		}
		ans = max(ans, cnt + (int)lt.size() - i - 1 + cur);
	}
	return ans;
}

void solve() {
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i] >> b[i] >> c[i];
	}

	int tmp1 = 0, tmp2 = 0, tmp3 = 0, tmp4 = 0;
	for (int i = 1; i <= n; ++i) {
		tmp1 += a[i] < 0;
		tmp2 += a[i] > 0;
		tmp3 += b[i] < 0;
		tmp4 += b[i] > 0;
	}
	int res = max(max(tmp1, tmp2), max(tmp3, tmp4));
	for (int i = -1; i <= 1; i += 2) {
		for (int j = -1; j <= 1; j += 2) {
			res = max(res, calc(i, j));
		}
	}
	cout << res << '\n';
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