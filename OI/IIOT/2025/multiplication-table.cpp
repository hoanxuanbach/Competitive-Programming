#include <bits/stdc++.h>
using namespace std;
int da[1000005], db[1000005], n, m;
vector<vector<long long int>> a;
vector<pair<long long int, pair<int, int>>> v;
void check(long long int x, long long int y) {
    if (x < 0 || y < 0) return;
    //cout << "19361936 " << x << " " << y << '\n';
    for (auto w : v) {
        if ((x + w.second.first) * (y + w.second.second) != w.first) {
            return;
        }
    }
    cout << "YES";
    exit(0);
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n >> m;
    a = vector<vector<long long int>>(n + 1, vector<long long int>(m + 1));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            string s;
            cin >> s;
            long long int c = -1;
            if (s != "?") {
                c = 0;
                for (char w : s) c = c * 10 + w - '0';
            }
            a[i][j] = c;
            if (a[i][j] != -1) {
                v.push_back({a[i][j], {i, j}});
                da[i]++; db[j]++;
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        if (da[i] >= 2) {
            long long int h = 0;
            for (int j = 1; j <= m; j++) {
                if (a[i][j] != -1) {
                    if (h == 0) {
                        h = j;
                    }
                    else {
                        if (a[i][j] - a[i][h] <= 0) {
                            cout << "NO";
                            return 0;
                        }
                        if ((a[i][j] - a[i][h]) % (j - h) != 0) {
                            cout << "NO";
                            return 0;
                        }
                        long long int x = (a[i][j] - a[i][h]) / (j - h);
                        if (a[i][j] % x != 0) {
                            cout << "NO";
                            return 0;
                        }
                        long long int y = a[i][j] / x;
                        check(x - i, y - j);
                        cout << "NO";
                        return 0;
                    }
                }
            }
        }
    }
    for (int j = 1; j <= m; j++) {
        if (db[j] >= 2) {
            long long int h = 0;
            for (int i = 1; i <= n; i++) {
                if (a[i][j] != -1) {
                    if (h == 0) {
                        h = i;
                    }
                    else {
                        if (a[i][j] - a[h][j] <= 0) {
                            cout << "NO";
                            return 0;
                        }
                        if ((a[i][j] - a[h][j]) % (i - h) != 0) {
                            cout << "NO";
                            return 0;
                        }
                        long long int x = (a[i][j] - a[h][j]) / (i - h);
                        if (a[i][j] % x != 0) {
                            cout << "NO";
                            return 0;
                        }
                        long long int y = a[i][j] / x;
                        check(y - i, x - j);
                        cout << "NO";
                        return 0;
                    }
                }
            }
        }
    }
    if (v.size() == 0) {
        cout << "YES";
        return 0;
    }
    long long int h = v[0].first, k = sqrt(h);
    for (int i = 1; i <= k; i++) {
        if (h % i == 0) {
            int j = h / i;
            check(i - v[0].second.first, j - v[0].second.second);
            check(j - v[0].second.first, i - v[0].second.second);
        }
    }
    cout << "NO";
}
