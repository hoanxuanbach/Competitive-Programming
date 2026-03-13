#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 7;

int n, a[N], b[N];

void solve() {
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i] >> b[i];

    for (int i = 1; i <= n; ++i) b[i] = b[i] - a[i];
    sort (b + 1, b + n + 1);
    int l = 1, r = n;
    long long ans1 = 0;

    int prv = 0;
    for (int i = 1; i <= n; ++i) {
        int cur = (i % 2 == 1 ? b[r--] : b[l++]);
        ans1 += max(0, cur - prv);
        prv = cur;
    }
    ans1 += max(0, 0 - prv);

    prv = 0;
    l = 1, r = n;
    long long ans2 = 0;
    for (int i = 1; i <= n; ++i) {
        int cur = (i % 2 == 1 ? b[l++] : b[r--]);
        ans2 += max(0, cur - prv);
        prv = cur;
    }
    ans2 += max(0, 0 - prv);

    cout << max(ans1, ans2) << '\n';
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