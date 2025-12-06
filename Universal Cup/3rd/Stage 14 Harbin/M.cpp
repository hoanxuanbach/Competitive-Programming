#include <bits/stdc++.h>
#define pii pair<int, int>
#define fi first
#define se second
#define CNT(mask) __builtin_popcount(mask)

using namespace std;
const int N = 2e5 + 5;

void solve() {
	int n;
	cin >> n;
	vector<int> divs;
	for (int i = 1; i * i <= n; i++) {
		if (n % i == 0) {
			divs.push_back(i);
			if (i * i != n) divs.push_back(n / i);
		}
	}
	sort (divs.begin(), divs.end());
	
	long long res = 0;
	for (int i = 1; i < (int)divs.size(); i++) {
		res += 1LL * (n / divs[i - 1]) * (divs[i] - divs[i - 1]);
	}
	cout << res + 1 << '\n';
}

signed main() {
#ifdef LOCAL
    freopen("main.inp", "r", stdin);
    freopen("main.out", "w", stdout);
#endif
    cin.tie(0), cout.tie(0)->sync_with_stdio(0);
    int testcases = 1;
    cin >> testcases;
    for (int test = 1; test <= testcases; test++) {
        solve();
    }
}