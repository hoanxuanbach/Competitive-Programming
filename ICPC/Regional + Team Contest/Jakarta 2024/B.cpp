/*
#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,fma,bmi,bmi2,sse4.2,popcnt,lzcnt")
*/

#include <bits/stdc++.h>
#define taskname ""
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define i64 long long
#define pb push_back
#define ff first
#define ss second
#define isz(x) (int)x.size()
using namespace std;

const int mxN = 2e5 + 5;
const int mod = 1e9 + 7;
const i64 oo = 1e18;

int n;
string s, t;

void compress(string &s) {
    auto check = [&](int idx) {
        return (0 <= idx && idx < n && s[idx] == '0');
    };

    auto go_to_prefix = [&](int l, int r) {
        while (check(l - 1)) {
            swap(s[l - 1], s[r]);
            --l, --r;
        }
    };

    for (int i = 0; i < n;) {
        if (s[i] == '1') {
            int l = i, r = i;
            while (r + 1 < n && s[r + 1] == '1') ++r;
            // int len = -1;
            while ((r - l + 1) % 2 == 1 && r - l + 1 != n) {
                // if (r - l + 1 == len) break;
                // len = r - l + 1;
                // cout << l << " " << r << endl;
                while (check(l - 1) and check(r + 1)) s[--l] = s[++r] = '1';
                if (l == 0 and check(r + 1)) s[++r] = '1';
                else if (r == n - 1 and check(l - 1)) s[--l] = '1';
                while (l - 1 >= 0 and s[l - 1] == '1') --l;
                while (r + 1 < n and s[r + 1] == '1') ++r;
            }
            i = r;
            go_to_prefix(l, r);
        }
        ++i;
    }
}

void solve() {
    cin >> n;
    cin >> s >> t;
    compress(s);
    compress(t);
    cout << (s == t ? "YES" : "NO") << "\n";
}

signed main() {

#ifndef CDuongg
    if(fopen(taskname".inp", "r"))
        assert(freopen(taskname".inp", "r", stdin)), assert(freopen(taskname".out", "w", stdout));
#else
    freopen("bai3.inp", "r", stdin);
    freopen("bai3.out", "w", stdout);
    auto start = chrono::high_resolution_clock::now();
#endif

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1; cin >> t;
    while(t--) solve();

#ifdef CDuongg
   auto end = chrono::high_resolution_clock::now();
   cout << "\n"; for(int i = 1; i <= 100; ++i) cout << '=';
   cout << "\nExecution time: " << chrono::duration_cast<chrono::milliseconds> (end - start).count() << "[ms]" << endl;
#endif

}
