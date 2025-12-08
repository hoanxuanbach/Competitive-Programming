#include<bits/stdc++.h>
#define pii pair<int,int>
#define fi first
#define se second

using namespace std;
const int N = 2e5 + 7;
const int INF = 1e9 + 7;

int n, k;
int a[5][N];
int type[N];
int sum[N];

bool check(int mid) {
    memset(sum, 0, sizeof(sum));

    for (int i = 0; i < 4; ++i) {
        for (int j = 1; j <= n; ++j) {
            sum[j] = sum[j] + a[i][j];
        }
    }

    vector<pii> vt0, vt1;
    for (int i = 1; i <= n; ++i) {
        if (type[i] == 0) {
            vt0.push_back({sum[i], -i});
        } else {
            vt1.push_back({sum[i], -i});
        }
    }
    sort (vt0.rbegin(), vt0.rend());
    sort (vt1.rbegin(), vt1.rend());

    int cnt0 = (int)vt0.size();
    int cnt1 = (int)vt1.size();

    // cout << mid << "\n";
    for (int i = 0; i < cnt1; ++i) {
        if (i < mid) {
            sum[-vt1[i].se] += n - mid + i + 1;
            // cout << -vt1[i].se << "+" << n - mid + i + 1 << " ";
        } else {
            sum[-vt1[i].se] += n - mid - (i - mid);
            // cout << -vt1[i].se << "+" << n - mid - (i - mid) << " ";
        }
    }

    for (int i = 0; i < cnt0; ++i) {
        if (i < k - mid) {
            sum[-vt0[i].se] += n - cnt1 - i;
            // cout << -vt0[i].se << "+" << n - cnt1 - i << " ";
        } else {
            sum[-vt0[i].se] += i - (k - mid) + 1;
            // cout << -vt0[i].se << "+" << i - (k - mid) + 1 << " ";
        }
    }
    // cout << "\n";

    // for (int i = 1; i <= n; ++i) {
    //     cout << sum[i] << " ";
    // }

    vector<pair<int, int>> all;
    for (int i = 1; i <= n; ++i) {
        all.push_back({sum[i], -i});
    }
    sort(all.rbegin(), all.rend());
    int cnt = 0;
    for (int i = 0; i < k; ++i) {
        if (type[-all[i].se] == 1) {
            cnt++;
        }
    }
    return cnt >= mid;
}

void solve() {
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        cin >> type[i];
        for (int j = 0; j < 4; ++j) {
            cin >> a[j][i];
        }
    }
    int cnt = 0;
    for (int i = 1; i <= n; ++i) {
        if (type[i] == 1) cnt++;
    }

    // check(3);
    // return;

    int l = 1, r = min(k, cnt), res = 0;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (check(mid)) {
            res = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }

    cout << res;
}

signed main(){
#ifdef LOCAL
    freopen("main.inp", "r", stdin);
    freopen("main.out", "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int num_test = 1;
    // cin >> num_test;
    while(num_test--) solve();
}