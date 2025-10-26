#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>

using namespace std;
const long long INF = 7e18;

long long src, dst;

long long nxt(long long x) {
    return x + (long long) (sqrt(2 * x) + 1.5);
}

long long calc(long long x, long long y) {
    long long cnt = (int)sqrt(2 * y) - sqrt(2 * x);
    long long nx = nxt(x);
    long long sta = nx - x;
    long long tmp = x + cnt * (sta + sta + cnt - 1) / 2;
    while (tmp < y) {
        tmp += sta + cnt;
        cnt++;
    }
    return cnt;
}

long long getAns(long long best) {
    long long res = src - best;
    long long diff = nxt(best) - best;
    long long cnt = calc(best, dst);
    res += cnt;
    best += cnt * (diff + diff + cnt - 1) / 2;
    res += best - dst;
    // cout << "RES: " << res << "\n";
    return res;
}


void solve() {
    cin >> src >> dst;
    if (src > dst) {
        cout << src - dst << '\n';
        return;
    }

    int sq = (int)sqrt(2 * src);

    long long cnt = calc(src, dst);
    long long l = 0, r = src, best = src;
    while (l <= r) {
        long long mid = (l + r) / 2;
        if (calc(mid, dst) == cnt) {
            best = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }

    long long res = getAns(best);
    if (best > 0) {
        res = min(res, getAns(best - 1));
    }
    cout << res << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
#ifdef LOCAL
    freopen("main.inp", "r", stdin);
    freopen("main.out", "w", stdout);
#endif
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}