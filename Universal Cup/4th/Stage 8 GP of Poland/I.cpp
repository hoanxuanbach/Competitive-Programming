#include<bits/stdc++.h>
using namespace std;
const int N = 8;
const int M = 10;

string ans[N][M];

void solve() {
    map<string, int> teams;
    teams["UW"] = 11;
    teams["UJ"] = 9;
    teams["UWR"] = 8;
    teams["MAP"] = 7;
    teams["PW"] = 6;
    teams["AGH"] = 5;
    teams["PG"] = 4;
    teams["NLU"] = 3;
    teams["PUT"] = 3;
    teams["PO"] = teams["PWR"] = teams["SGGW"] = teams["UMCS"] = teams["UR"] = teams["ZUT"] = 2;
    teams["DTP"] = teams["GOO"] = teams["HUA"] = teams["KUL"] = teams["PL"] = teams["PM"] = teams["PS"] = teams["UAM"] = teams["UG"] = teams["UMK"] = teams["UO"] = teams["WAT"] = 1;

    string x;
    cin >> x;
    ans[0][0] = x, teams[x]--;
    if (teams[x] == 0) teams.erase(x);

    for (int i = 0; i < N; ++i) {
        vector<pair<int, string>> vt;
        for (auto &it : teams) {
            bool check = true;
            if (i > 0) {
                for (int j = 0; j < M; ++j) {
                    if (ans[i-1][j] == it.first) {
                        check = false;
                        break;
                    }
                }
            }
            if (check) vt.push_back({it.second, it.first});
        }
        sort(vt.rbegin(), vt.rend());
        for (int j = (i == 0 ? 1 : 0); j < M; ++j) {
            if (j == 0) {
                ans[i][j] = vt[0].second;
                vt[0].first--;
                if (vt[0].first == 0) vt.erase(vt.begin());
            } else {
                if (ans[i][j-1] == vt[0].second) {
                    ans[i][j] = vt[1].second;
                    vt[1].first--;
                    if (vt[1].first == 0) vt.erase(vt.begin() + 1);
                } else {
                    ans[i][j] = vt[0].second;
                    vt[0].first--;
                    if (vt[0].first == 0) vt.erase(vt.begin());
                }
            }

            teams[ans[i][j]]--;
            if (teams[ans[i][j]] == 0) teams.erase(ans[i][j]);
        }
    }

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            cout << ans[i][j] << " ";
        }
        cout << "\n";
    }
}

signed main(){
#ifdef LOCAL
    freopen("main.inp", "r", stdin);
    freopen("main.out", "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int num_test = 1;
    // cin >> num_test;
    while(num_test--) solve();
}