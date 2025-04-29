/*
#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,fma,bmi,bmi2,sse4.2,popcnt,lzcnt")
*/

#include <bits/stdc++.h>
#define taskname ""
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define i64 long long
#define isz(x) (int)x.size()
using namespace std;

int mex(const vector<int> &a){
    int n = (int)a.size();
    static vector<int> found;
    found.assign(n + 1, false);
    for(auto x: a) if(x <= n) found[x] = true;
    int res = 0;
    while(found[res]) ++ res;
    return res;
}

void solve() {
    vector<int> a(4);
    for (auto &val : a) {
        cin >> val;
        --val;
    }
    cout << mex(a) + 1 << endl;
}

signed main() {

#ifndef CDuongg
    if (fopen(taskname".inp", "r"))
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
#endif

}
