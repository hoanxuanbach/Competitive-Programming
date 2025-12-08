#include<bits/stdc++.h>
using namespace std;
const int N = 3e5 + 7;

int a[N], pref[N], suff[N];

void solve() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        pref[i] = max(pref[i - 1], a[i]);
    }
    suff[n] = a[n];
    for (int i = n - 1; i >= 1; --i) {
        suff[i] = max(suff[i + 1], a[i]);
    }

    int ans = 1e9 + 7;
    for (int i = 1; i < n; ++i) {
        ans = min(ans, abs(pref[i] - suff[i + 1]));
    }

    cout << ans << '\n';
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
