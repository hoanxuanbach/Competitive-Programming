#include <bits/stdc++.h>

using namespace std;
const int N = 2e5 + 7;
const int mod = 998244353;
const long long INF = 1e18 + 7;

void add(int &x, const int &y) {
    x += y;
    if (x >= mod) x -= mod;
}

void sub(int &x, const int &y) {
    x -= y;
    if (x < 0) x += mod;
}

void safe_mul(long long &x, const long long &y) {
    if (INF / x < y) {
        x = INF;
        return;
    }
    x *= y;
}

int prod(int x, int y) {
    return 1LL * x * y % mod;
}

int power(int x, int y) {
    if (y == 0) return 1;
    if (y == 1) return x;
    int res = 1;
    while (y) {
        if (y & 1) res = prod(res, x);
        x = prod(x, x);
        y >>= 1;
    }
    return res;
}

int n, m, a[N], b[N];

void solve() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i] >> b[i];
    }

    map<int, long long> cnt;
    for (int i = 1; i <= n; ++i) {
        cnt[b[i]] += a[i];
    }
    vector<pair<int, long long>> vec;
    for (auto [w, c] : cnt) {
        vec.push_back({w, c});
    }
    sort(vec.begin(), vec.end());
    
    int res = 0;
    while(vec.size()) {
        int w = vec.back().first;
        long long c = vec.back().second;
        vec.pop_back();
        
        long long tmp1 = c / m;
        long long tmp2 = (m - c % m) % m;
        add(res, prod(power(2, w), tmp1 % mod));
        if (tmp2) add(res, power(2, w));

        while (vec.size() && tmp2 > 0) {
            int nw = vec.back().first;
            long long nc = vec.back().second;
            int diff = min(60, w - nw);
            safe_mul(tmp2, (1LL << diff));
            
            if (nc > tmp2) {
                vec.back().second -= tmp2;
                tmp2 = 0;
                break;
            }
            tmp2 -= nc;
            vec.pop_back();
            w = nw;
        }
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