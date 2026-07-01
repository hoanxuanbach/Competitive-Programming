#include <bits/stdc++.h>

using namespace std;

int n, cnt[10];
string s;

bool check(int mid) {
    memset(cnt, 0, sizeof(cnt));
    for (int i = 0; i < n; ++i) {
        cnt[s[i]-'0']++;
    }

    int x = min(mid, cnt[0]);
    int hv = 0;
    cnt[0] -= x;
    for (int i = 9; i >= 0; --i) {
        if (i == 1) continue;
        int tmp = min(cnt[i], x);
        cnt[i] -= tmp;
        x -= tmp;
        hv += tmp;
    }

    int tmp = min(cnt[1], x);
    cnt[1] -= tmp;
    x -= tmp;
    hv += tmp;

    tmp = x / 2;
    x -= tmp * 2;
    hv += tmp;
    cnt[0] += x - tmp * 2;

    if (hv < mid) {
        cnt[1] -= (mid - hv) * 2;
        if (cnt[1] < 0) return false;
    }

    int cnt1 = 0, cnt2 = 0;
    for (int i = 0; i <= 9; ++i) {
        if (i <= 5) cnt1 += cnt[i];
        else cnt2 += cnt[i];
    }

    int mi = min(cnt1, cnt2);
    tmp = mi + (cnt1 - mi) / 2;

    return tmp >= mid;
}

void solve() {
    cin >> n;
    cin >> s;

    int l = 0, r = n / 4;
    int res = 0;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (check(mid)) {
            res = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }

    cout << res << '\n';
}

signed main() {
#ifdef LOCAL
    freopen("main.inp", "r", stdin);
    // freopen("main.out", "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int num_test = 1;
    cin >> num_test;
    while (num_test--) {
        solve();
    }
}