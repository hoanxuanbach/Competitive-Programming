#include <bits/stdc++.h>

using namespace std;
const int N = (int)1e5 + 7;

int n, k, nxt[N];
string str, ans;

bool solve(int n, int k, string s) {
    s = ' ' + s;
    nxt[n] = n + 1;
    
    for (int i = n - 1; i >= 1; --i) {
        if (s[i + 1] != '?') {
            nxt[i] = i + 1;
        } else {
            nxt[i] = nxt[i + 1];
        }
    }

    int cnt = 0, len = 0;
    for (int i = 1; i < n; ++i) {
        if (s[i] == '?') {
            continue;
        }
        if (s[i] != s[nxt[i]]) {
            cnt += 1;
            len += (nxt[i] - i - 1) / 2;
        } else {
            len += (nxt[i] - i) / 2;
        }
    }

    if (cnt > k || cnt % 2 != k % 2 || (k - cnt) / 2 > len) {
        return false;
    }

    for (int i = 1; i < n; ++i) {
        if (s[i] != '?') {
            if (nxt[i] == i + 1) {
                continue;
            }
            if (s[i] != s[nxt[i]]) {
                cnt -= 1;
                len -= (nxt[i] - i - 1) / 2;
            } else {
                len -= (nxt[i] - i) / 2;
            }
            continue;
        }

        s[i] = '0';
        int tmp_cnt = cnt;
        if (i > 1 && s[i] != s[i - 1]) {
            ++tmp_cnt;
        }

        int tmp_len = len;
        if (s[i] != s[nxt[i]]) {
            ++tmp_cnt;
            tmp_len += (nxt[i] - i - 1) / 2;
        } else {
            tmp_len += (nxt[i] - i) / 2;
        }

        if (tmp_cnt > k || tmp_cnt % 2 != k % 2 || (k - tmp_cnt) / 2 > tmp_len) {
            s[i] = '1';
        }

        if (i > 1 && s[i] != s[i - 1]) {
            ++cnt;
        }
        if (nxt[i] == i + 1 && s[i] != s[nxt[i]]) {
            ++cnt;
        }
    }

    ans = s.substr(1);
    return true;
}

int main() {
#ifdef LOCAL
    freopen("main.inp", "r", stdin);
    freopen("main.out", "w", stdout);
#endif
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t = 1;
    cin >> t;
    while (t--) {
        cin >> n >> k >> str;
        vector<string> solutions;
        int l0 = 0, r0 = 1;
        if (str[0] != '?') {
            l0 = r0 = str[0] - '0';
        }

        int ln = 0, rn = 1;
        if (str[n - 1] != '?') {
            ln = rn = str[n - 1] - '0';
        }
        
        for (int i = l0; i <= r0; ++i) {
            for (int j = ln; j <= rn; ++j) {
                str[0] = '0' + i;
                str[n - 1] = '0' + j;
                if (solve(n, k, str)) {
                    solutions.push_back(ans);
                }
            }
        }

        if (solutions.empty()) {
            cout << "Impossible\n";
        } else {
            sort (solutions.begin(), solutions.end());
            cout << solutions[0] << '\n';
        }
    }
    return 0;
}
