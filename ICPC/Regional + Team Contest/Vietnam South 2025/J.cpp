#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>
#define int long long

using namespace std;
vector<string> moves = {"Rock", "Paper", "Scissors"};

void solve() {
    string s, t;
    cin >> s >> t;
    for (int i = 0; i < 3; ++i) {
        if (s == moves[i] && moves[(i + 2) % 3] == t) {
            cout << "Player 1";
            return;
        }

        if (t == moves[i] && moves[(i + 2) % 3] == s) {
            cout << "Player 2";
            return;
        }
    }
    cout << "Draw";
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
#ifdef LOCAL
    freopen("main.inp", "r", stdin);
    freopen("main.out", "w", stdout);
#endif
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}