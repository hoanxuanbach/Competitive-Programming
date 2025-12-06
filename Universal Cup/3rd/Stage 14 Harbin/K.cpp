#include <bits/stdc++.h>
#define pii pair<int, int>
#define fi first
#define se second
#define CNT(mask) __builtin_popcount(mask)
#define int long long

using namespace std;
const int N = 2e5 + 7;

struct Crop {
	int w, l, r;
	bool operator < (const Crop& other) const {
		return w > other.w;
	}
}crops[N];

int n, cnt[N], rem[N], f[N];
int m;

void solve() {
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) {
		cin >> crops[i].w >> crops[i].l >> crops[i].r;
	}
	sort(crops + 1, crops + n + 1);

	int sum = 0;
	for (int i = 1; i <= n; ++i) {
		cnt[i] = crops[i].l;
		sum += cnt[i];
	}
	for (int i = 1; i <= n; ++i) {
		int tmp = min(crops[i].r - crops[i].l, m - sum);
		cnt[i] += tmp;
		sum += tmp;
	}

	int sta = 0;
	for (int i = 1; i <= n; ++i) {
		sta += cnt[i] * crops[i].w;
	}

	int res = sta;

	for (int i = 1; i <= n; ++i) {
		rem[i] = crops[i].r - cnt[i];
		f[i] = rem[i] * crops[i].w;
		rem[i] += rem[i - 1];
		f[i] += f[i - 1];
	}

	for (int i = 1; i <= n; ++i) {
		int total = cnt[i];
		int k = upper_bound(rem + 1, rem + n + 1, total) - rem;
		if (k > i) k = i;
		--k;

		int tmp = sta - cnt[i] * crops[i].w;
		tmp += f[k];
		tmp += (total - rem[k]) * crops[k + 1].w;
		res = max(res, tmp);
	}

	sum = 0;
	int tmp = 0;
	for (int i = 2; i <= n; ++i) {
		sum += crops[i].l;
		tmp += crops[i].l * crops[i].w;
	}
	tmp += (m - sum) * crops[1].w;
	res = max(res, tmp);

	cout << res << '\n';
}

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
