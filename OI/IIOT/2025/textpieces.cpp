#include <bits/stdc++.h>
using namespace std;
int d[20005], c[20005][26], dd[80005], da[80005];
vector<int> g[80005], gg[80005], v[20005][26], vv;
char res[20005];
struct TEXT {
    int b, k;
    string s, t;
} a[20005];
void dfs(int x) {
    dd[x] = 1;
    for (int w : g[x]) {
        if (dd[w]) continue;
        dfs(w);
    }
    vv.push_back(x);
}
void dfs(int x, int h) {
    dd[x] = h;
    for (int w : gg[x]) {
        if (dd[w]) continue;
        dfs(w, h);
    }
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < q; i++) {
        int b, k;
        string s, t;
        cin >> b >> k >> s; t = s;
        reverse(t.begin(), t.end());
        a[i] = {b, k, s, t};
        for (int j = 0; j < k; j++) {
            d[b + j]++;
            v[b + j][s[j] - 'a'].push_back(i << 1);
            v[b + j][t[j] - 'a'].push_back(i << 1 | 1);
            if (t[j] == s[j]) {
                c[b + j][t[j] - 'a']++;
            }
            else {
                //cout << i << " " << j << " " << s[j] << " " << t[j] << '\n';
                c[b + j][s[j] - 'a']++;
                c[b + j][t[j] - 'a']++;
            }
        }
    }
    for (int i = 0; i < q; i++) {
        int b = a[i].b, k = a[i].k;
        string s, t;
        s = a[i].s; t = a[i].t;
        for (int j = 0; j < k; j++) {
            if (c[b + j][s[j] - 'a'] != d[b + j]) {
                //cout << i << " " << d[b + j] << " " << c[b + j][s[j] - 'a'] << '\n';
                g[i << 1].push_back(i << 1 | 1);
            }
            if (c[b + j][t[j] - 'a'] != d[b + j]) {
                //cout << i << '\n';
                g[i << 1 | 1].push_back(i << 1);
            }
        }
    }
    for (int i = 0; i < n; i++) {
        res[i] = '$';
        if (d[i] == 0) continue;
        int x = -1, y = -1;
        for (int j = 0; j < 26; j++) {
            if (c[i][j] != d[i]) continue;
            if (x == -1) {
                x = j;
            }
            else y = j;
        }
        if (y == -1) continue;
        for (int w : v[i][x]) da[w] = 1;
        for (int w : v[i][y]) da[w] = 2;
        for (int w : v[i][x]) {
            g[w].push_back((i + q) << 1);
            if (da[w ^ 1] != 1) g[(i + q) << 1].push_back(w);
        }
        for (int w : v[i][y]) {
            g[w].push_back((i + q) << 1 | 1);
            if (da[w ^ 1] != 2) g[(i + q) << 1 | 1].push_back(w);
        }
        for (int w : v[i][x]) da[w] = 0;
        for (int w : v[i][y]) da[w] = 0;
        //cout << i << " " << x << " " << y << '\n';
    }
    for (int i = 0; i < (q + n) * 2; i++) {
        if (dd[i] == 0) {
            dfs(i);
        }
    }
    for (int i = 0; i < (q + n) * 2; i++) dd[i] = 0;
    for (int i = 0; i < (q + n) * 2; i++) {
        for (int w : g[i]) {
            gg[w].push_back(i);
            //cout << i << " " << w << '\n';
        }
    }
    int z = 0;
    for (int i = vv.size() - 1; i >= 0; i--) {
        if (dd[vv[i]] == 0) {
            z++;
            dfs(vv[i], z);
        }
    }
    for (int i = 0; i < (q + n); i++) {
        if (dd[i << 1] == dd[i << 1 | 1]) {
            cout << "NO";
            return 0;
        }
    }
    for (int i = 0; i < q; i++) {
        if (dd[i << 1] > dd[i << 1 | 1]) {
            for (int j = 0; j < a[i].k; j++) {
                res[a[i].b + j] = a[i].s[j];
            }
        }
        else {
            for (int j = 0; j < a[i].k; j++) {
                res[a[i].b + j] = a[i].t[j];
            }
        }
    }
    cout << "YES" << '\n';
    for (int i = 0; i < n; i++) {
        if (res[i] == '$') res[i] = 'a';
        cout << res[i];
    }
}
