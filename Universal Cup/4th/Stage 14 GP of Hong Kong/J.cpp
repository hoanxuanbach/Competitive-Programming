#include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/trie_policy.hpp>
// #include <ext/rope>

using namespace std;
// using namespace __gnu_cxx;
// using namespace __gnu_pbds;

void Hollwo_Pelw();

signed main(){
#ifndef hollwo_pelw_local
    if (fopen(".inp", "r"))
        assert(freopen(".inp", "r", stdin)), assert(freopen(".out", "w", stdout));
#else
    using namespace chrono;
    auto start = steady_clock::now();
#endif
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int testcases = 1;
    cin >> testcases;
    for (int test = 1; test <= testcases; test++){
        // cout << "Case #" << test << ": ";
        Hollwo_Pelw();
    }
#ifdef hollwo_pelw_local
    auto end = steady_clock::now();
    cout << "\nExecution time : " << duration_cast<milliseconds> (end - start).count() << "[ms]" << endl;
#endif
}

#define int long long

int n, l[3], mark[3];
vector<int> p[3];

void Hollwo_Pelw(){
    cin >> n;
    for (int i = 0; i < 3; i++) {
        cin >> l[i];
        mark[i] = 0;
        p[i].clear();
    }

    int cur = 0, maxpen = 0;

    for (int i = 0; i < n; i++) {
        int x, c;
        cin >> x >> c;
        p[-- x].push_back(c);
        cur += c;
    }

    cin >> maxpen;

    multiset<int> st;

    vector<int> ord;

    while ((int) ord.size() < n) {
        for (int i = 0; i < 3; i++) {
            if (!mark[i] && cur <= l[i]) {

                for (int x : p[i]) {
                    st.insert(x);
                }

                mark[i] = 1;
            }
        }

        if (st.empty()) {
            cout << "NO\n";
            return ;
        }

        int v = *st.rbegin();

        st.erase(st.find(v));
        cur -= v;
        ord.push_back(v);
    }

    reverse(ord.begin(), ord.end());

    int curpen = 0, totpen = 0;
    for (int i : ord) {
        curpen += i;
        totpen += curpen;
        if (totpen >= maxpen) {
            cout << "NO\n";
            return ;
        }
    }

    cout << "YES\n";
}