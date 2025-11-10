#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>
#define BIT(x, i) (((x) >> (i)) & 1)

using namespace std;
const int N = 202;
const int INF = 1e9;

struct State {
    int a, b, n, p;
    State(int _a = 0, int _b = 0, int _n = 0, int _p = 0) {
        a = _a;
        b = _b;
        n = _n;
        p = _p;
    }
    bool operator < (const State &oth) const {
        return a > oth.a || b > oth.b || n < oth.n || p > oth.p;
    }
};

bool minimize(int &a, int b) {
    if (a <= b) {
        return false;
    }
    a = b;
    return true;
}

int a, b, n, p;
int dp[N][N][22][2];
State trace[N][N][22][2];

void init() {
    memset(dp, 0x3f, sizeof(dp));
    dp[0][0][21][0] = 0;
    priority_queue<pair<int, State>, vector<pair<int, State>>, greater<pair<int, State>>> pq;
    pq.push({0, State(0, 0, 21, 0)});
    while (!pq.empty()) {
        auto [cost, state] = pq.top();
        pq.pop();
        int a = state.a, b = state.b, n = state.n, p = state.p;
        // cout << a << " " << b << " " << n << " " << p << " " << cost << '\n';
        if (cost != dp[a][b][n][p]) continue;
        
        if (n >= 7) {
            for (int i = 3; i <= 8; ++i) {
                int na = a + (p == 0) * i;
                int nb = b + (p == 1) * i;
                if (na >= 200 || nb >= 200) continue;
                int nn = n - 1;
                for (int j = 0; j < 2; ++j) {
                    if (minimize(dp[na][nb][nn][j], cost + 2 + (j != p))) {
                        trace[na][nb][nn][j] = state;
                        pq.push({dp[na][nb][nn][j], State(na, nb, nn, j)});
                    }
                }
            }

            int na = a + (p == 0);
            int nb = b + (p == 1);
            int nn = n - 1;
            if (na <= 200 && nb <= 200 && minimize(dp[na][nb][nn][1^p], cost + 2)) {
                trace[na][nb][nn][1^p] = state;
                pq.push({dp[na][nb][nn][1^p], State(na, nb, nn, 1^p)});
            }
        } else if (n > 0) {
            int i = 7 - n + 1;
            int na = a + (p == 0) * i;
            int nb = b + (p == 1) * i;
            int nn = n - 1;
            for (int j = 0; j < 2; ++j) {
                if (nn == 0 && j != p) continue;
                if (na <= 200 && nb <= 200 && minimize(dp[na][nb][nn][j], cost + 1 + (j != p))) {
                    trace[na][nb][nn][j] = state;
                    pq.push({dp[na][nb][nn][j], State(na, nb, nn, j)});
                }
            }
        }

        if (n > 0 && minimize(dp[a][b][n][1^p], cost + 1)) {
            trace[a][b][n][1^p] = state;
            pq.push({dp[a][b][n][1^p], State(a, b, n, 1^p)});
        }
    }
}

void solve() {
    cin >> a >> b >> n >> p;
    if (dp[a][b][n][p] >= INF) {
        cout << "NA\n";
        return;
    }

    State cur(a, b, n, p);
    string res = "";
    while (cur.a != 0 || cur.b != 0 || cur.n != 21 || cur.p != 0) {
        State prv = trace[cur.a][cur.b][cur.n][cur.p];

        if (abs(cur.a - prv.a) + abs(cur.b - prv.b) == 0) {
            res += '/';
            cur = prv;
            continue;
        }
        
        if (abs(cur.a - prv.a) + abs(cur.b - prv.b) == 1 || prv.n <= 6) {
            if (prv.p != cur.p) {
                res += '/';
            }
            res += '0' + abs(cur.a - prv.a) + abs(cur.b - prv.b);
            cur = prv;
            continue;
        }

        int tmp = abs(cur.a - prv.a) + abs(cur.b - prv.b);
        if (prv.p != cur.p) {
            res += '/';
        }
        res += '0' + (tmp - 1);
        res += '1';
        cur = prv;
    }
    if ((int)res.length() > 100) {
        cout << "NA\n";
        return;
    }
    reverse(res.begin(), res.end());
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
    init();
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}