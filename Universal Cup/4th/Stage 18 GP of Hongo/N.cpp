#include <bits/stdc++.h>
#define BIT(x,i) ((x) >> (i) & 1)
#define MASK(x) (1LL << (x))
#define CNT(x) __builtin_popcountll(x)
#define double long double

using namespace std;
const int N = 1010;
const int MAX = 18;
const double EPS = 1e-5;

int n;
pair<int, int>a[N];
vector<pair<double, int>> vt[N + 1];

void solve() {
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i].first, a[i].second = i;
    sort (a + 1, a + n + 1);

    int sz = min(n, MAX);
    for (int i = 1; i + sz - 1 <= n; ++i) {
        for (int j = 0; j <= sz; ++j) vt[j].clear();

        for (int mask = 0; mask < MASK(sz); ++mask) {
            double sum = 0;
            for (int j = 0; j < sz; ++j) {
                if (BIT(mask, j)) sum += (double)1.0 / a[i + j].first;
            }
            vt[CNT(mask)].push_back(make_pair(sum, mask));
        }

        for (int j = 1; j <= sz; ++j) {
            sort (vt[j].begin(), vt[j].end());
            for (int k = 1; k < (int)vt[j].size(); ++k) {
                if (abs(vt[j][k].first - vt[j][k - 1].first) <= EPS) {
                    vector<int> x, y;
                    int mask1 = vt[j][k-1].second, mask2 = vt[j][k].second;
                    for (int idx = 0; idx < sz; ++idx) {
                        if (BIT(mask1, idx)) x.push_back(a[i + idx].second);
                        if (BIT(mask2, idx)) y.push_back(a[i + idx].second);
                    }
                    sort (x.begin(), x.end());
                    sort (y.begin(), y.end());
                    cout << "Yes\n";
                    cout << (int)x.size() << '\n';
                    for (int pos : x) cout << pos << " ";
                    cout << '\n';
                    for (int pos : y) cout << pos << " ";
                    cout << '\n';
                    return;
                }
            }
        }
    }

    cout << "No\n";
}

int main(){
#ifdef LOCAL
    freopen("main.inp", "r", stdin);
    freopen("main.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int num_test = 1; //cin >> num_test;
    while (num_test--) {
        solve();
    }
}