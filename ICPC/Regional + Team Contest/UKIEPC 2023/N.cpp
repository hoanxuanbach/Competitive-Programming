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

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

i64 rand_range(i64 l, i64 r)
{
    i64 len = r - l + 1;
    return (rng() % len + l);
}

string random_string(int len, char u, char v)
{
    string s;
    for (int i = 0; i < len; ++i)
        s.pb((char)rand_range(u, v));
    return s;
}

int n;
map<double, string> mp;

void solve() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        string tmp; cin >> tmp;
        tmp.pop_back();

        double cur = 0, bruh = 1;
        bool flag = false;
        for (char ch : tmp) {
            if (!flag) {
                if (ch != '.') cur = cur * 10 + (ch - '0');
                else flag = true;
            }
            else bruh /= 10, cur += bruh * (ch - '0');
        }

        if (mp.find(cur) == mp.end()) mp[cur] = random_string(100, 'a', 'z');
        cout << mp[cur] << "\n";
    }
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
#endif

}
