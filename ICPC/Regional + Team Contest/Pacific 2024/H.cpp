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

int n, res;
int ap1, ap0, go0, go1;

vector<int> vec;

void solve() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        string s; cin >> s;
        int cnt1 = count(all(s), '1');
        int cnt0 = isz(s) - cnt1;
        if (cnt0) ap0 = true;
        if (cnt1) ap1 = true;
        if (cnt0 < cnt1) {
            go1 = true;
            res += cnt0;
            vec.emplace_back(cnt1 - cnt0);
        }
        else {
            go0 = true;
            res += cnt1;
            vec.emplace_back(cnt0 - cnt1);
        }
    }
    if ((ap0 and !go0) or (ap1 and !go1)) {
        res += *min_element(all(vec));
    }
    cout << res << endl;
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
    int t = 1; //cin >> t;
    while(t--) solve();

#ifdef CDuongg
   auto end = chrono::high_resolution_clock::now();
   cout << "\n"; for(int i = 1; i <= 100; ++i) cout << '=';
   cout << "\nExecution time: " << chrono::duration_cast<chrono::milliseconds> (end - start).count() << "[ms]" << endl;
   cout << "Check array size pls sir" << endl;
#endif

}
